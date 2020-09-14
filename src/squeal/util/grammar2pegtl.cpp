
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

    string sane(const string& p_str)
    {
        string s(p_str.begin()+1, p_str.end()-1);
        replace(s.begin(), s.end(), ' ', '_');
        replace(s.begin(), s.end(), '-', '_');
        replace(s.begin(), s.end(), '/', '_');
        return s;
    }

    string escape(char p_ch)
    {
        string s;
        switch (p_ch)
        {
            case '\'':
            case '\\':
                s.push_back('\\');
        }
        s.push_back(p_ch);
        return s;
    }

    string keyword_chars(const std::string& p_word)
    {
        string s;
        for (size_t i = 0; i < p_word.size(); ++i)
        {
            if (i > 0)
            {
                s += ", ";
            }
            switch (p_word[i])
            {
                case '_':
                {
                    s += "detail::underscore";
                    break;
                }
                case '-':
                {
                    s += "detail::hypen";
                    break;
                }
                default:
                {
                    s += "detail::";
                    s.push_back(p_word[i]);
                }
            }
        }
        return s;
    }

    string sane_keyword(const string& p_word)
    {
        string s(p_word);
        if (p_word == "TRUE" || p_word == "FALSE" || p_word == "NULL")
        {
            s.push_back('_');
        }
        return s;
    }

    template <typename T, typename X>
    bool attempt(const node_ptr& p_ptr, X p_closure)
    {
        std::shared_ptr<const T> p = dynamic_pointer_cast<const T>(p_ptr);
        if (!p)
        {
            return false;
        }
        p_closure(*p);
        return true;
    }

    void names(const node_ptr& p_ptr, set<string>& p_names)
    {
        using namespace squeal::meta_grammar;

        bool r;
        r = attempt<name_node>(p_ptr, [&](const name_node& p_node) mutable {
            p_names.insert(p_node.name);
        });
        if (r) { return; }
        r = attempt<conj_node>(p_ptr, [&](const conj_node& p_node) mutable {
            for (auto itr = p_node.nodes.begin(); itr != p_node.nodes.end(); ++itr)
            {
                names(*itr, p_names);
            }
        });
        if (r) { return; }
        r = attempt<disj_node>(p_ptr, [&](const disj_node& p_node) mutable {
            for (auto itr = p_node.nodes.begin(); itr != p_node.nodes.end(); ++itr)
            {
                names(*itr, p_names);
            }
        });
        if (r) { return; }
        r = attempt<star_node>(p_ptr, [&](const star_node& p_node) mutable {
            names(p_node.child, p_names);
        });
        if (r) { return; }
        r = attempt<plus_node>(p_ptr, [&](const plus_node& p_node) mutable {
            names(p_node.child, p_names);
        });
        if (r) { return; }
        r = attempt<opt_node>(p_ptr, [&](const opt_node& p_node) mutable {
            names(p_node.child, p_names);
        });
        if (r) { return; }
    }

    void words(const node_ptr& p_ptr, set<string>& p_names)
    {
        using namespace squeal::meta_grammar;

        bool r;
        r = attempt<word_node>(p_ptr, [&](const word_node& p_node) mutable {
            p_names.insert(p_node.word);
        });
        if (r) { return; }
        r = attempt<conj_node>(p_ptr, [&](const conj_node& p_node) mutable {
            for (auto itr = p_node.nodes.begin(); itr != p_node.nodes.end(); ++itr)
            {
                words(*itr, p_names);
            }
        });
        if (r) { return; }
        r = attempt<disj_node>(p_ptr, [&](const disj_node& p_node) mutable {
            for (auto itr = p_node.nodes.begin(); itr != p_node.nodes.end(); ++itr)
            {
                words(*itr, p_names);
            }
        });
        if (r) { return; }
        r = attempt<star_node>(p_ptr, [&](const star_node& p_node) mutable {
            words(p_node.child, p_names);
        });
        if (r) { return; }
        r = attempt<plus_node>(p_ptr, [&](const plus_node& p_node) mutable {
            words(p_node.child, p_names);
        });
        if (r) { return; }
        r = attempt<opt_node>(p_ptr, [&](const opt_node& p_node) mutable {
            words(p_node.child, p_names);
        });
        if (r) { return; }
    }

    void indent(ostream& p_out, int p_ind)
    {
        for (int i = 0; i < p_ind; ++i)
        {
            p_out << "    ";
        }
    }

    void renderExpr(const node_ptr& p_ptr, ostream& p_out, int p_ind, const set<string>& p_keywords, const string& p_ns)
    {
        using namespace squeal::meta_grammar;

        bool r;
        r = attempt<special_node>(p_ptr, [&](const special_node& p_node) mutable {
            indent(p_out, p_ind);
            p_out << p_node.word;
        });
        if (r) { return; }
        r = attempt<name_node>(p_ptr, [&](const name_node& p_node) mutable {
            indent(p_out, p_ind);
            p_out << sane(p_node.name);
        });
        if (r) { return; }
        r = attempt<word_node>(p_ptr, [&](const word_node& p_node) mutable {
            indent(p_out, p_ind);
            if (p_keywords.count(p_node.word) > 0)
            {
                p_out << "keywords::" << sane_keyword(p_node.word);
                return;
            }
            if (p_node.word.size() == 1)
            {
                p_out << "tao::pegt::utf8::one<'" << escape(p_node.word[0]) << "'>";
                return;
            }
            p_out << "tao::pegt::utf8::string<";
            for (auto itr = p_node.word.begin(); itr != p_node.word.end(); ++itr)
            {
                if (itr != p_node.word.begin())
                {
                    p_out << ",";
                }
                p_out << "'" << escape(*itr) << "'";
            }
            p_out << ">";
        });
        if (r) { return; }
        r = attempt<conj_node>(p_ptr, [&](const conj_node& p_node) mutable {
            indent(p_out, p_ind);
            p_out << p_ns << "seq<\n";
            for (auto itr = p_node.nodes.begin(); itr != p_node.nodes.end(); ++itr)
            {
                if (itr != p_node.nodes.begin())
                {
                    p_out << ",\n";
                }
                renderExpr(*itr, p_out, p_ind+1, p_keywords, p_ns);
            }
            p_out << "\n";
            indent(p_out, p_ind);
            p_out << ">";
        });
        if (r) { return; }
        r = attempt<disj_node>(p_ptr, [&](const disj_node& p_node) mutable {
            indent(p_out, p_ind);
            p_out << p_ns << "sor<\n";
            for (auto itr = p_node.nodes.begin(); itr != p_node.nodes.end(); ++itr)
            {
                if (itr != p_node.nodes.begin())
                {
                    p_out << ",\n";
                }
                renderExpr(*itr, p_out, p_ind+1, p_keywords, p_ns);
            }
            p_out << "\n";
            indent(p_out, p_ind);
            p_out << ">";
        });
        if (r) { return; }
        r = attempt<star_node>(p_ptr, [&](const star_node& p_node) mutable {
            indent(p_out, p_ind);
            p_out << p_ns << "star<\n";
            renderExpr(p_node.child, p_out, p_ind+1, p_keywords, p_ns);
            p_out << "\n";
            indent(p_out, p_ind);
            p_out << ">";
        });
        if (r) { return; }
        r = attempt<plus_node>(p_ptr, [&](const plus_node& p_node) mutable {
            indent(p_out, p_ind);
            p_out << p_ns << "plus<\n";
            renderExpr(p_node.child, p_out, p_ind+1, p_keywords, p_ns);
            p_out << "\n";
            indent(p_out, p_ind);
            p_out << ">";
        });
        if (r) { return; }
        r = attempt<opt_node>(p_ptr, [&](const opt_node& p_node) mutable {
            indent(p_out, p_ind);
            p_out << p_ns << "opt<\n";
            renderExpr(p_node.child, p_out, p_ind+1, p_keywords, p_ns);
            p_out << "\n";
            indent(p_out, p_ind);
            p_out << ">";
        });
        if (r) { return; }
    }

    void renderTokenRule(const string& p_name, const node_ptr& p_defn, ostream& p_out, const set<string>& p_keywords)
    {
        using namespace squeal::meta_grammar;

        std::shared_ptr<const special_node> p = dynamic_pointer_cast<const special_node>(p_defn);
        if (p)
        {
            p_out << "#if 0\n";
        }
        p_out << "        struct " << sane(p_name) << " :\n";
        renderExpr(p_defn, p_out, 3, p_keywords, "tao::pegtl::");
        p_out << "\n";
        p_out << "        {};\n";
        if (p)
        {
            p_out << "#endif\n";
        }
    }

    void renderRule(const string& p_name, const node_ptr& p_defn, ostream& p_out, const set<string>& p_keywords)
    {
        using namespace squeal::meta_grammar;

        std::shared_ptr<const special_node> p = dynamic_pointer_cast<const special_node>(p_defn);
        if (p)
        {
            p_out << "#if 0\n";
        }
        p_out << "        struct " << sane(p_name) << " :\n";
        renderExpr(p_defn, p_out, 3, p_keywords, "sep::");
        p_out << "\n";
        p_out << "        {};\n";
        if (p)
        {
            p_out << "#endif\n";
        }
    }

    void deps(const map<string, node_ptr>& p_defns, map<string,set<string>>& p_deps)
    {
        for (auto itr = p_defns.begin(); itr != p_defns.end(); ++itr)
        {
            set<string> nms;
            names(itr->second, nms);
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
            names(p_defns.at(nm), nms);
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

    void process(const string& p_txt, map<string, node_ptr>& p_defns)
    {
        tao::pegtl::string_input in(p_txt, "string");
        squeal::meta_grammar::state S;
        bool result = tao::pegtl::parse<squeal::meta_grammar::definition, squeal::meta_grammar::build_ast>(in, S);
        if (!result || S.nodes.size() != 1)
        {
            std::cerr << p_txt << std::endl;
            return;
        }
        squeal::meta_grammar::defn_node_ptr p = dynamic_pointer_cast<squeal::meta_grammar::defn_node>(S.nodes[0]);
        p_defns[p->name] = p->defn;
    }

    void fwds(std::ostream& p_out, map<string,node_ptr>& p_defns)
    {
        p_out << "namespace squeal" << endl;
        p_out << "{" << endl;
        p_out << "    namespace grammar" << endl;
        p_out << "    {" << endl;
        for (auto itr = p_defns.begin(); itr != p_defns.end(); ++itr)
        {
            string s = sane(itr->first);
            p_out << str(format("        struct %s;") % s) << endl;
        }
        p_out << "    }" << endl;
        p_out << "    // namespace grammar" << endl;
        p_out << "}" << endl;
        p_out << "// namespace squeal" << endl;
    }

}
// namespace anonymous

int main(int argc, const char* argv[])
{
    ifstream in(argv[1]);

    map<string, squeal::meta_grammar::node_ptr> defns;

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
                process(txt, defns);
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
        process(txt, defns);
        txt.clear();
    }

    if (1)
    {
        {
            ofstream out("squeal_grammar_fwd_decls.hpp");
            fwds(out, defns);
        }

        set<string> reserved;
        words(defns.at("<reserved word>"), reserved);

        set<string> non_reserved;
        words(defns.at("<non-reserved word>"), non_reserved);

        set<string> keywords;
        keywords.insert(reserved.begin(), reserved.end());
        keywords.insert(non_reserved.begin(), non_reserved.end());

        {
            ofstream out("squeal_grammar_keywords.hpp");
            out << "namespace squeal" << endl;
            out << "{" << endl;
            out << "    namespace grammar" << endl;
            out << "    {" << endl;
            out << "        namespace keywords" << endl;
            out << "        {" << endl;
            for (auto itr = reserved.begin(); itr != reserved.end(); ++itr)
            {
                
                out << "            struct " << sane_keyword(*itr) << " :" << endl;
                out << "                detail::reserved<" << keyword_chars(*itr) << ">" << endl;
                out << "            {};" << endl;
                out << endl;
            }
            for (auto itr = non_reserved.begin(); itr != non_reserved.end(); ++itr)
            {
                
                out << "            struct " << sane_keyword(*itr) << " :" << endl;
                out << "                detail::keyword<" << keyword_chars(*itr) << ">" << endl;
                out << "            {};" << endl;
                out << endl;
            }
            out << "        }" << endl;
            out << "        //namespace keywords" << endl;
            out << "    }" << endl;
            out << "    //namespace grammar" << endl;
            out << "}" << endl;
            out << "//namespace squeal" << endl;
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

            map<string,set<string>> S;
            deps(tokens, S);
            tarjan T(S);

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
                    renderTokenRule(ktr->first, ktr->second, out, keywords);
                    out << endl;
                }
            }
        }
        {
            ofstream out("squeal_grammar_main.hpp");

            map<string,set<string>> S;
            deps(defns, S);
            tarjan T(S);

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
                    renderRule(ktr->first, ktr->second, out, keywords);
                    out << endl;
                }
            }
        }
    }
    return 0;   
}
