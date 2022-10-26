#define _CRT_SECURE_NO_WARNINGS
#include <gtest/gtest.h>
#include <figcone_toml/datetime.h>
#include <figcone_tree/stringconverter.h>
#include <ctime>

#include <iostream>

namespace test_datetime{

TEST(TestDateTime, LocalDate)
{
    const auto res = figcone::detail::convertFromString<figcone::toml::DateTimePoint>("2018-12-23");
    ASSERT_TRUE(res.has_value());
    auto tm = std::tm{};
    tm.tm_year = 118;
    tm.tm_mon = 11;
    tm.tm_mday = 23;
    const auto t = std::mktime(&tm);
    const auto tt = std::localtime(&t);
    const auto expectedTimePoint = std::chrono::system_clock::from_time_t(std::mktime(tt));
    EXPECT_EQ(res->value, expectedTimePoint);
}

TEST(TestDateTime, LocalDateTime)
{
    const auto res = figcone::detail::convertFromString<figcone::toml::DateTimePoint>("2018-12-23T12:30:00");
    ASSERT_TRUE(res.has_value());
    auto tm = std::tm{};
    tm.tm_year = 118;
    tm.tm_mon = 11;
    tm.tm_mday = 23;
    tm.tm_hour = 12;
    tm.tm_min = 30;
    tm.tm_sec = 0;
    const auto t = std::mktime(&tm);
    const auto tt = std::localtime(&t);
    const auto expectedTimePoint = std::chrono::system_clock::from_time_t(std::mktime(tt));
    EXPECT_EQ(res->value, expectedTimePoint);
}

namespace crossplatform
{
    std::time_t timegm(std::tm* _Tm)
    {
        auto t = std::mktime(_Tm);
        return t + (std::mktime(std::localtime(&t)) - std::mktime(std::gmtime(&t)));
    }
}

TEST(TestDateTime, OffsetDateTime)
{
    const auto res = figcone::detail::convertFromString<figcone::toml::DateTimePoint>("2018-12-23T12:30:00+09:30");
    ASSERT_TRUE(res.has_value());
    auto tm = std::tm{};
    tm.tm_year = 2018 - 1900;
    tm.tm_mon = 12 - 1;
    tm.tm_mday = 23;
    tm.tm_hour = 3;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    const auto t = crossplatform::timegm(&tm);
    const auto expectedTimePoint = std::chrono::system_clock::from_time_t(t);
    EXPECT_EQ(res->value, expectedTimePoint);
}

TEST(TestDateTime, LocalTime)
{
    const auto res = figcone::detail::convertFromString<figcone::toml::TimeDuration>("12:30:00");
    ASSERT_TRUE(res.has_value());
    const auto expectedTime = std::chrono::seconds{45000};
    EXPECT_EQ(res->value, expectedTime);
}

}