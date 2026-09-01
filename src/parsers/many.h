#pragma once

#include <parser.h>

// clang-format off

/** @brief   Run the given sub-parser indefinitely until it fails. Failure on the first try is
 *           still counted as valid.
 *  @param   parser The sub-parser to run.
 *  @returns A list of results accumulated from all successful runs.
 */
template <typename T>
auto Many(Parser<T> parser) -> decltype(auto)
{
    using R = Result<std::vector<T>>;
    return Parser<std::vector<T>>
    {
        [parser](State const& state) -> R
        {
            auto values = std::vector<T>();
            auto result = parser(state);
            for (; result.Ok(); result = parser(result.Rest()))
            {
                values.push_back(result.Value());
            }
            return R::Success(values, result.Rest());
        },
        "many"
    };
}

// clang-format on
