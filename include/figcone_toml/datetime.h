#pragma once
#include "detail/external/toml.hpp"
#include <figcone_tree/stringconverter.h>
#include <chrono>
#include <sstream>

namespace figcone::toml{
struct TimeDuration{
    std::chrono::seconds value;
};
struct DateTimePoint{
    std::chrono::system_clock::time_point value;
};
}

namespace figcone{

template<>
struct StringConverter<toml::DateTimePoint>{
    static std::optional<toml::DateTimePoint> fromString(const std::string& data)
    {
        auto dateStr = "date = " + data;
        auto stream = std::stringstream{dateStr};
        const auto tomlData = ::toml::parse(stream);
        const auto date = ::toml::get<std::chrono::system_clock::time_point>(tomlData.at("date"));
        return toml::DateTimePoint{date};
    }
};

template<>
struct StringConverter<toml::TimeDuration>{
    static std::optional<toml::TimeDuration> fromString(const std::string& data)
    {
        auto timeStr = "time = " + data;
        auto stream = std::stringstream{timeStr};
        const auto tomlData = ::toml::parse(stream);
        const auto time = ::toml::get<std::chrono::seconds>(tomlData.at("time"));
        return toml::TimeDuration{time};
    }
};


}