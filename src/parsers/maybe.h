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
template <typename T>
auto Maybe(Parser<T> parser) -> decltype(auto)
{
    using R = Result<std::optional<T>>;
    return Parser<std::optional<T>>
    {
        [parser](State const& state) -> R
        {
            auto result = parser(state);
            if (!result.Ok())
            {
                return R::Success(std::nullopt, state);
            }
            return R::Success(result.Value(), result.Rest());
        },
        "maybe"
    };
}

// clang-format on
