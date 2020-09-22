
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <boost/format.hpp>

#include "squeal/util/meta_grammar.hpp"

using namespace std;
using namespace boost;

namespace //anonymous
{
    using node_ptr = squeal::meta_grammar::node_ptr;

    struct ns_scope
    {
        ns_scope(squeal::meta_grammar::context& p_ctxt, const std::string& p_ns_name)
            : ctxt(p_ctxt), ns_name(p_ns_name)
        {
            ctxt.indent();
            ctxt.out << "namespace " << ns_name << "\n";
            ctxt.indent();
            ctxt.out << "{\n";

            ctxt.ind += 1;
        }

        ~ns_scope()
        {
            ctxt.ind -= 1;

            ctxt.indent();
            ctxt.out << "}\n";
            ctxt.indent();
            ctxt.out << "// namespace " << ns_name << "\n";
        }

        squeal::meta_grammar::context& ctxt;
        string ns_name;
    };

    struct combinator_ns
    {
        combinator_ns(squeal::meta_grammar::context& p_ctxt, const std::string& p_ns)
            : ctxt(p_ctxt), ns(p_ctxt.ns)
        {
            ctxt.ns = p_ns;
        }

        ~combinator_ns()
        {
            ctxt.ns = ns;
        }

        squeal::meta_grammar::context& ctxt;
        string ns;
    };

    void deps(const map<string, node_ptr>& p_defns, map<string,set<string>>& p_deps)
    {
        for (auto itr = p_defns.begin(); itr != p_defns.end(); ++itr)
        {
            set<string> nms;
            itr->second->names(nms);
            p_deps[itr->first] = nms;
        }
    }

    void gather(deque<string>& p_wanted, const map<string, node_ptr>& p_defns, set<string>& p_res)
    {
        while (p_wanted.size() > 0)
        {
            string nm = p_wanted.front();
            p_wanted.pop_front();
            p_res.insert(nm);
            set<string> nms;
            if (p_defns.find(nm) == p_defns.end())
            {
                string s;
                s += "unknown rule name: ";
                s += nm;
                throw std::runtime_error(s);
            }
            p_defns.at(nm)->names(nms);
            for (auto itr = nms.begin(); itr != nms.end(); ++itr)
            {
                if (p_res.count(*itr) > 0)
                {
                    continue;
                }
                p_wanted.push_back(*itr);
                p_res.insert(*itr);
            }
        }
    }

    struct tarjan
    {
        const map<string,set<string>>& E;
        int idx;
        vector<string> S;
        set<string> O;
        map<string,int> Vi;
        map<string,int> Vl;
        vector<set<string>> R;

        tarjan(const map<string,set<string>>& p_E)
            : E(p_E)
        {
            idx = 0;
            for (auto itr = E.begin(); itr != E.end(); ++itr)
            {
                if (Vi.find(itr->first) == Vi.end())
                {
                    strong(itr->first);
                }
            }
        }

        void strong(const string& p_v)
        {
            Vi[p_v] = idx;
            Vl[p_v] = idx;
            idx += 1;
            S.push_back(p_v);
            O.insert(p_v);

            auto jtr = E.find(p_v);
            if (jtr != E.end())
            {
                const set<string>& ws = jtr->second;
                for (auto itr = ws.begin(); itr != ws.end(); ++itr)
                {
                    const string& w = *itr;
                    if (Vi.find(w) == Vi.end())
                    {
                        strong(w);
                        Vl[p_v] = std::min(Vl.at(p_v), Vl.at(w));
                    }
                    else if (O.count(w) > 0)
                    {
                        Vl[p_v] = std::min(Vl.at(p_v), Vi.at(w));
                    }
                }
            }

            if (Vl.at(p_v) == Vi.at(p_v))
            {
                set<string> scc;
                string w;
                do
                {
                    w = S.back();
                    S.pop_back();
                    O.erase(w);
                    scc.insert(w);
                }
                while (w != p_v);
                R.push_back(scc);
            }
        }
    };

    void process(const string& p_txt, map<string, node_ptr>& p_defns, map<string,string>& p_meta)
    {
        tao::pegtl::string_input in(p_txt, "string");
        squeal::meta_grammar::state S;
        bool result = tao::pegtl::parse<squeal::meta_grammar::definition, squeal::meta_grammar::build_ast>(in, S);
        if (!result || S.nodes.size() != 0)
        {
            std::cerr << p_txt << std::endl;
            S.dump(cerr);
            return;
        }
        for (auto itr = S.rules.begin(); itr != S.rules.end(); ++itr)
        {
            p_defns[itr->first] = itr->second;
        }
        for (auto itr = S.meta.begin(); itr != S.meta.end(); ++itr)
        {
            p_meta[itr->first] = itr->second;
        }
    }

    void fwds(std::ostream& p_out, map<string,node_ptr>& p_defns)
    {
        p_out << "namespace squeal" << endl;
        p_out << "{" << endl;
        p_out << "    namespace grammar" << endl;
        p_out << "    {" << endl;
        for (auto itr = p_defns.begin(); itr != p_defns.end(); ++itr)
        {
            string s = squeal::meta_grammar::cpp::esc_name(itr->first);
            p_out << str(format("        struct %s;") % s) << endl;
        }
        p_out << "    }" << endl;
        p_out << "    // namespace grammar" << endl;
        p_out << "}" << endl;
        p_out << "// namespace squeal" << endl;
    }

    string keyword_chars(const string& p_word)
    {
        string s;
        for (size_t i = 0; i < p_word.size(); ++i)
        {
            if (i > 0)
            {
                s += ", ";
            }

            char c = p_word[i];
            switch (c)
            {
                case '-':
                {
                    s += "detail::hypen";
                    break;
                }
                case '_':
                {
                    s += "detail::underscore";
                    break;
                }
                default:
                {
                    s += str(format("detail::%c") % c);
                }
            }
        }
        return s;
    }

    struct incl_guard
    {
        incl_guard(squeal::meta_grammar::context& p_ctxt, const string& p_filename)
            : ctxt(p_ctxt), guard_name(mkGuard(p_filename))
        {
            ctxt.out << "#ifndef " << guard_name << endl;
            ctxt.out << "#define " << guard_name << endl;
        }

        ~incl_guard()
        {
            ctxt.out << "#endif // " << guard_name << endl;
        }

        squeal::meta_grammar::context& ctxt;
        const string guard_name;

        static string mkGuard(const string& p_filename)
        {
            string s(p_filename);
            replace(s.begin(), s.end(), ' ', '_');
            replace(s.begin(), s.end(), '-', '_');
            replace(s.begin(), s.end(), '/', '_');
            replace(s.begin(), s.end(), '.', '_');
            transform(s.begin(), s.end(), s.begin(), ::toupper);
            return s;
        }
    };


    void render_identifier_rule(squeal::meta_grammar::context& p_ctxt, node_ptr p_defn)
    {
        auto ptr = dynamic_pointer_cast<squeal::meta_grammar::defn_node>(p_defn);

        p_ctxt.indent();
        p_ctxt.out << "struct " << squeal::meta_grammar::cpp::esc_name(ptr->name) << " :\n";
        {
            squeal::meta_grammar::scope S0(p_ctxt);
            p_ctxt.indent();
            p_ctxt.out << "tao::pegtl::seq<\n";
            {
                squeal::meta_grammar::scope S1(p_ctxt);
                p_ctxt.indent();
                p_ctxt.out << "tao::pegtl::not_at<key_word>,\n";
                ptr->defn->render(p_ctxt);
            }
            p_ctxt.out << ">\n";
        }
        p_ctxt.indent();
        p_ctxt.out << "{};\n";
    }
}
// namespace anonymous

int main(int argc, const char* argv[])
{
    ifstream in(argv[1]);

    string out_base = argv[2];

    map<string, squeal::meta_grammar::node_ptr> defns;
    map<string, string> meta;

    string txt;
    string line;

    while (getline(in, line))
    {
        if (line.size() > 0 && line.front() == '#')
        {
            continue;
        }
        if (line.size() == 0)
        {
            if (txt.size() > 0)
            {
                process(txt, defns, meta);
                txt.clear();
            }
        }
        else
        {
            if (txt.size() > 0)
            {
                txt += " ";
            }
            txt += line;
        }
    }
    if (txt.size() > 0)
    {
        process(txt, defns, meta);
        txt.clear();
    }

    if (1)
    {
        {
            ofstream out(out_base + "/squeal_grammar_fwd_decls.hpp");
            fwds(out, defns);
        }

        {
            ofstream out(out_base + "/squeal_grammar_blacklist.hpp");

            for (auto itr = defns.begin(); itr != defns.end(); ++itr)
            {
                auto ptr = dynamic_pointer_cast<squeal::meta_grammar::defn_node>(itr->second);
                if (!ptr)
                {
                    continue;
                }

                auto qtr = dynamic_pointer_cast<squeal::meta_grammar::disj_node>(ptr->defn);
                if (!qtr)
                {
                    continue;
                }

                bool ok = true;
                for (auto jtr = qtr->nodes.begin(); jtr != qtr->nodes.end() && ok; ++jtr)
                {
                    auto rtr = dynamic_pointer_cast<squeal::meta_grammar::name_node>(*jtr);
                    if (!rtr)
                    {
                        ok = false;
                    }
                }

                if (ok)
                {
                    out << "    template<> struct blacklist<squeal::grammar::"
                                << squeal::meta_grammar::cpp::esc_name(itr->first) << "> : std::false_type {};" << endl;
                }
            }
        }

        string identifier_rule;
        if (meta.find("identifier-rule") != meta.end())
        {
            identifier_rule = meta.at("identifier-rule");
            std::cout << "identifier-rule: " << identifier_rule << std::endl;
        }

        string reserved_word_rule;
        if (meta.find("reserved-word-rule") != meta.end())
        {
            reserved_word_rule = meta.at("reserved-word-rule");
        }

        set<string> reserved;
        if (defns.find(reserved_word_rule) != defns.end())
        {
            defns.at(reserved_word_rule)->words(reserved);
        }

        string non_reserved_word_rule;
        if (meta.find("other-keyword-rule") != meta.end())
        {
            non_reserved_word_rule = meta.at("other-keyword-rule");
        }

        set<string> non_reserved;
        if (defns.find(non_reserved_word_rule) != defns.end())
        {
            defns.at(non_reserved_word_rule)->words(non_reserved);
        }

        set<string> keywords;
        keywords.insert(reserved.begin(), reserved.end());
        keywords.insert(non_reserved.begin(), non_reserved.end());

        string out_name(out_base + "/squeal_grammar_main.hpp");
        if (meta.find("grammar-main-file") != meta.end())
        {
            out_name = meta.at("grammar-main-file");
        }

        ofstream out(out_name);
        squeal::meta_grammar::context ctxt(out);
        ctxt.keywords = keywords;

        incl_guard G(ctxt, out_name);

        ns_scope NS0(ctxt, "squeal");
        ns_scope NS1(ctxt, "grammar");

        if (keywords.size())
        {

            ns_scope NS2(ctxt, "keywords");
            {
                ns_scope NS3(ctxt, "detail");
                for (char c = 'A'; c <= 'Z'; ++c)
                {
                    char l = c - 'A' + 'a';
                    ctxt.indent();
                    ctxt.out << "struct " << c << " : tao::pegtl::utf8::one<'" << c << "', '" << l  << "'> {};" << endl;
                }
                ctxt.indent();
                ctxt.out << "struct hypen : tao::pegtl::utf8::one<'-'> {};" << endl;
                ctxt.indent();
                ctxt.out << "struct underscore : tao::pegtl::utf8::one<'_'> {};" << endl;
            }
            ctxt.out << endl;

            for (auto itr = reserved.begin(); itr != reserved.end(); ++itr)
            {
                ctxt.indent();
                ctxt.out << "struct " << squeal::meta_grammar::cpp::esc_word(*itr) << " :" << endl;
                {
                    squeal::meta_grammar::scope S0(ctxt);
                    ctxt.indent();
                    ctxt.out << "detail::reserved<" << keyword_chars(*itr) << ">" << endl;
                }
                ctxt.indent();
                ctxt.out << "{};" << endl;
                ctxt.out << endl;
            }
            for (auto itr = non_reserved.begin(); itr != non_reserved.end(); ++itr)
            {
                ctxt.indent();
                ctxt.out << "struct " << squeal::meta_grammar::cpp::esc_word(*itr) << " :" << endl;
                {
                    squeal::meta_grammar::scope S0(ctxt);
                    ctxt.indent();
                    ctxt.out << "detail::keyword<" << keyword_chars(*itr) << ">" << endl;
                }
                ctxt.indent();
                ctxt.out << "{};" << endl;
                ctxt.out << endl;
            }
        }
        ctxt.out << endl;

        set<string> tokens;
        if (meta.find("token-rule") != meta.end())
        {
            string token_rule = meta.at("token-rule");
            deque<string> wanted;
            wanted.push_back(token_rule);
            gather(wanted, defns, tokens);
        }

        cout << tokens.count("<character string literal part>") << endl;

        if (0)
        {
            for (auto itr = tokens.begin(); itr != tokens.end(); ++itr)
            {
                cout << *itr << endl;
            }
        }

        map<string,set<string>> S;
        deps(defns, S);
        tarjan T(S);

        for (auto itr = T.R.begin(); itr != T.R.end(); ++itr)
        {
            const set<string>& xs = *itr;

            map<string,set<string>> Sd;
            for (auto jtr = xs.begin(); jtr != xs.end(); ++jtr)
            {
                auto ktr = defns.find(*jtr);
                set<string> dx;
                squeal::meta_grammar::defn_node_ptr p = dynamic_pointer_cast<squeal::meta_grammar::defn_node>(ktr->second);
                if (p)
                {
                    squeal::meta_grammar::name_node_ptr q = dynamic_pointer_cast<squeal::meta_grammar::name_node>(p->defn);
                    if (q && xs.count(q->name))
                    {
                        dx.insert(q->name);
                    }
                }
                Sd[ktr->first] = dx;
            }
            tarjan Td(Sd);
            for (auto jtr = Td.R.begin(); jtr != Td.R.end(); ++jtr)
            {
                const set<string>& ys = *jtr;
                for (auto ktr = ys.begin(); ktr != ys.end(); ++ktr)
                {
                    auto ltr = defns.find(*ktr);
                    if (ltr == defns.end())
                    {
                        continue;
                    }
                    if (tokens.count(*ktr) == 0)
                    {
                        combinator_ns C(ctxt, "detail::");

                        if (*ktr == identifier_rule)
                        {
                            render_identifier_rule(ctxt, ltr->second);
                        }
                        else
                        {
                            ltr->second->render(ctxt);
                        }
                        out << endl;
                    }
                    else
                    {
                        if (*ktr == identifier_rule)
                        {
                            render_identifier_rule(ctxt, ltr->second);
                        }
                        else
                        {
                            ltr->second->render(ctxt);
                        }
                        out << endl;
                    }
                }
            }
        }
    }
    return 0;   
}
