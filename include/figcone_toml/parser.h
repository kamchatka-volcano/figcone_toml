#ifndef FIGCONE_TOML_PARSER_H
#define FIGCONE_TOML_PARSER_H

#include <figcone_tree/tree.h>
#include <figcone_tree/iparser.h>
#include <istream>

namespace figcone::toml{
class Parser : public IParser{
public:
    TreeNode parse(std::istream& stream) override;
};

}

#endif //FIGCONE_TOML_PARSER_H