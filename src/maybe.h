#pragma once

#include <parser.h>

#include <expected>
#include <optional>
#include <string>

// clang-format off

/** @brief Optionally runs a sub-parser, succeeding even if the sub-parser fails.
 *  @param parser The sub-parser to run.
 *  @returns A callable parser that returns a matched item on success, or std::nullopt.
 */
template <typename P>
auto Maybe(P parser) -> decltype(auto)
{
    return Parser
    {
        [parser](State& state) -> std::expected<std::optional<typename P::ResultType>, std::string>
        {
            auto result = parser(state);
            if (!result)
            {
                return std::nullopt;
            }
            return *result;
        },
        "maybe"
    };
}

// clang-format on
