#ifndef FIGCONE_TOML_DATETIME_H
#define FIGCONE_TOML_DATETIME_H

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

namespace figcone {
template<>
struct StringConverter<toml::DateTimePoint> {
    static std::optional<toml::DateTimePoint> fromString(const std::string& data);
};

template<>
struct StringConverter<toml::TimeDuration> {
    static std::optional<toml::TimeDuration> fromString(const std::string& data);
};

}

#endif //FIGCONE_TOML_DATETIME_H