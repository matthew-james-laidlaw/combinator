#pragma once

#include <string>

inline auto Join(const auto& strings, std::string separator) -> std::string
{
    auto result = std::string();

    for (const auto& string : strings) {
        if (!result.empty()) {
            result += separator;
        }
        result += string;
    }

    return result;
};
