#ifndef FIGCONE_TOML_PARSER_H
#define FIGCONE_TOML_PARSER_H

#include "detail/external/toml.hpp"
#include <figcone_tree/tree.h>
#include <figcone_tree/iparser.h>
#include <figcone_tree/errors.h>
#include <vector>
#include <string>
#include <sstream>

namespace figcone::toml::detail
{
    inline std::string str(const toml::value& val)
    {
        if (val.is_string())
            return val.as_string();

        auto stream = std::stringstream{};
        stream << val;
        return stream.str();
    }

    inline void parseToml(const toml::value& toml, figcone::TreeNode& node)
    {
        for (auto& [key, value] : toml.as_table()){
            if (value.is_table()){
                auto& newNode = node.asItem().addNode(key);
                parseToml(value, newNode);
            }
            else if (value.is_array()){
                if (!value.as_array().empty() && value.as_array().front().is_table()) {
                    auto& newNode = node.asItem().addNodeList(key);;
                    for (auto& item : value.as_array())
                        parseToml(item, newNode.asList().addNode());
                }
                else{
                    auto valuesList = std::vector<std::string>{};
                    for (auto& item : value.as_array()) {
                        if (item.is_array())
                            throw ConfigError{"Array '" + key + "': figcone_toml doesn't support nested arrays"};
                        valuesList.emplace_back(str(item));
                    }

                    node.asItem().addParamList(key, valuesList);
                }
            }
            else
                node.asItem().addParam(key, str(value));
        }
    }
}

namespace figcone::toml{
class Parser : public IParser{
public:
    TreeNode parse(std::istream& stream) override
    {
        const auto toml = [&]{
            try {
                return toml::parse(stream);
            }
            catch (const toml::exception& e) {
                throw figcone::ConfigError{e.what(), {e.location().line(), e.location().column()}};
            }
        }();

        auto tree = figcone::makeTreeRoot();
        detail::parseToml(toml, tree);
        return tree;
    }
};

}

#endif //FIGCONE_TOML_PARSER_H