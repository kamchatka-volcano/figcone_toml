#pragma once
#include <chrono>
#include <figcone_tree/stringconverter.h>
#include <toml.hpp>
#include <sstream>

namespace figcone::toml{
struct Time{
    std::chrono::seconds value;
};
struct DateTime{
    std::chrono::system_clock::time_point value;
};
}

namespace figcone{

template<>
struct StringConverter<toml::DateTime>{
    static std::optional<toml::DateTime> fromString(const std::string& data)
    {
        auto dateStr = "date = " + data;
        auto stream = std::stringstream{dateStr};
        const auto tomlData = ::toml::parse(stream);
        const auto date = ::toml::get<std::chrono::system_clock::time_point>(tomlData.at("date"));
        return toml::DateTime{date};
    }
};

template<>
struct StringConverter<toml::Time>{
    static std::optional<toml::Time> fromString(const std::string& data)
    {
        auto timeStr = "time = " + data;
        auto stream = std::stringstream{timeStr};
        const auto tomlData = ::toml::parse(stream);
        const auto time = ::toml::get<std::chrono::seconds>(tomlData.at("time"));
        return toml::Time{time};
    }
};


}