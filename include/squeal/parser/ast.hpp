#ifndef SQUEAL_PARSER_AST_HPP
#define SQUEAL_PARSER_AST_HPP

#include <memory>
#include <map>
#include <string>
#include <vector>

namespace squeal
{
    namespace parser
    {
        namespace ast
        {
            struct node
            {
                virtual ~node() {}

                virtual std::string json() const = 0;

                virtual bool is_atom() const { return false; }
                virtual bool is_array() const { return false; }
                virtual bool is_object() const { return false; }
            };
            using node_ptr = std::shared_ptr<node>;

            struct atom_node : node
            {
                std::string value;

                atom_node(const std::string& p_value)
                    : value(p_value)
                {}

                virtual bool is_atom() const { return true; }

                virtual std::string json() const
                {
                    std::string s;
                    s += "\"";
                    s += value;
                    s += "\"";
                    return s;
                }
            };

            struct array_node : node
            {
                std::vector<node_ptr> value;

                array_node() {}

                array_node(const std::vector<node_ptr>& p_value)
                    : value(p_value)
                {}

                virtual bool is_array() const { return true; }

                virtual std::string json() const
                {
                    std::string s;
                    s += "[";
                    for (auto itr = value.begin(); itr != value.end(); ++itr)
                    {
                        if (itr != value.begin())
                        {
                            s += ", ";
                        }
                        s += (*itr)->json();
                    }
                    s += "]";
                    return s;
                }
            };

            struct object_node : node
            {
                std::map<std::string, node_ptr> value;

                object_node() {}

                object_node(const std::map<std::string, node_ptr>& p_value)
                    : value(p_value)
                {}

                virtual bool is_object() const { return true; }

                virtual std::string json() const
                {
                    std::string s;
                    s += "{";
                    for (auto itr = value.begin(); itr != value.end(); ++itr)
                    {
                        if (itr != value.begin())
                        {
                            s += ", ";
                        }
                        s += "\"";
                        s += itr->first;
                        s += "\": ";
                        s += itr->second->json();
                    }
                    s += "}";
                    return s;
                }

                static node_ptr singleton(const std::string& p_key, node_ptr p_value)
                {
                    std::map<std::string,node_ptr> m;
                    m[p_key] = p_value;
                    return node_ptr(new object_node(m));
                }
            };
        }
        // namespace ast
    }
    // namespace parser
}
// namespace squeal

#endif // SQUEAL_PARSER_AST_HPP
