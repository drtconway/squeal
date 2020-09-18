
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

    void deps(const map<string, node_ptr>& p_defns, map<string,set<string>>& p_deps)
    {
        for (auto itr = p_defns.begin(); itr != p_defns.end(); ++itr)
        {
            set<string> nms;
            itr->second->names(nms);
            p_deps[itr->first] = nms;
        }
    }

    void gather(deque<string>& p_wanted, const map<string, node_ptr>& p_defns, map<string, node_ptr>& p_res)
    {
        set<string> seen(p_wanted.begin(), p_wanted.end());

        while (p_wanted.size() > 0)
        {
            string nm = p_wanted.front();
            p_wanted.pop_front();
            p_res[nm] = p_defns.at(nm);
            set<string> nms;
            p_defns.at(nm)->names(nms);
            for (auto itr = nms.begin(); itr != nms.end(); ++itr)
            {
                if (seen.count(*itr) > 0)
                {
                    continue;
                }
                p_wanted.push_back(*itr);
                seen.insert(*itr);
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
}
// namespace anonymous

int main(int argc, const char* argv[])
{
    ifstream in(argv[1]);

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
            ofstream out("squeal_grammar_fwd_decls.hpp");
            fwds(out, defns);
        }

        set<string> reserved;
        defns.at("<reserved word>")->words(reserved);

        set<string> non_reserved;
        defns.at("<non-reserved word>")->words(non_reserved);

        set<string> keywords;
        keywords.insert(reserved.begin(), reserved.end());
        keywords.insert(non_reserved.begin(), non_reserved.end());

        {
            ofstream out("squeal_grammar_keywords.hpp");

            squeal::meta_grammar::context ctxt(out);
            ctxt.keywords = keywords;

            ns_scope NS0(ctxt, "squeal");
            ns_scope NS1(ctxt, "grammar");
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
        };

        map<string,node_ptr> tokens;
        {
            deque<string> wanted;
            wanted.push_back("<token>");
            gather(wanted, defns, tokens);
        }

        set<string> seen;
        {
            ofstream out("squeal_grammar_lexemes.hpp");

            squeal::meta_grammar::context ctxt(out);
            ctxt.keywords = keywords;

            map<string,set<string>> S;
            deps(tokens, S);
            tarjan T(S);

            ns_scope NS0(ctxt, "squeal");
            ns_scope NS1(ctxt, "grammar");

            for (auto itr = T.R.begin(); itr != T.R.end(); ++itr)
            {
                const set<string>& xs = *itr;
                for (auto jtr = xs.begin(); jtr != xs.end(); ++jtr)
                {
                    auto ktr = tokens.find(*jtr);
                    if (ktr == tokens.end())
                    {
                        continue;
                    }
                    seen.insert(ktr->first);
                    ktr->second->render(ctxt);
                    out << endl;
                }
            }
        }
        {
            ofstream out("squeal_grammar_main.hpp");

            squeal::meta_grammar::context ctxt(out);
            ctxt.keywords = keywords;

            map<string,set<string>> S;
            deps(defns, S);
            tarjan T(S);

            ns_scope NS0(ctxt, "squeal");
            ns_scope NS1(ctxt, "grammar");

            for (auto itr = T.R.begin(); itr != T.R.end(); ++itr)
            {
                const set<string>& xs = *itr;
                for (auto jtr = xs.begin(); jtr != xs.end(); ++jtr)
                {
                    if (seen.count(*jtr) > 0)
                    {
                        continue;
                    }
                    auto ktr = defns.find(*jtr);
                    if (ktr == defns.end())
                    {
                        continue;
                    }
                    seen.insert(ktr->first);
                    ktr->second->render(ctxt);
                    out << endl;
                }
            }
        }
    }
    return 0;   
}
