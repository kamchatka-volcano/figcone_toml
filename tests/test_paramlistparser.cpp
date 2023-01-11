#include "assert_exception.h"
#include <figcone_toml/parser.h>
#include <gtest/gtest.h>
#include <sstream>

namespace test_paramlistparser {

auto parseParam(const std::string& str)
{
    auto input = std::stringstream{str};
    auto parser = figcone::toml::Parser{};
    return parser.parse(input);
}

TEST(TestParamListParser, Basic)
{
    auto result = parseParam(R"( testIntList = [1, 2, 3] )");
    auto& tree = result.asItem();
    ASSERT_EQ(tree.paramsCount(), 1);
    EXPECT_EQ(tree.param("testIntList").valueList(), (std::vector<std::string>{"1", "2", "3"}));
}

TEST(TestParamListParser, BasicWithoutMacro)
{
    auto result = parseParam(R"( testIntList = [1, 2, 3] )");
    auto& tree = result.asItem();
    ASSERT_EQ(tree.paramsCount(), 1);
    EXPECT_EQ(tree.param("testIntList").valueList(), (std::vector<std::string>{"1", "2", "3"}));
}

TEST(TestParamListParser, MissingParamError)
{
    assert_exception<figcone::ConfigError>(
            []
            {
                parseParam(R"( testIntList = [[1, 2], 3] )");
            },
            [](const figcone::ConfigError& error)
            {
                EXPECT_EQ(std::string{error.what()}, "Array 'testIntList': figcone_toml doesn't support nested arrays");
            });
}

} //namespace test_paramlistparser
