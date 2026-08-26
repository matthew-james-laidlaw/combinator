#pragma once

// clang-format off

/** @brief   Parser that takes two sub-parsers and runs them in sequence, but only returns the
 *           result of the last parser. Expects the ignored parser to succeed.
 *  @param   p1 The parser who's result is ignored.
 *  @param   p2 The parser who's result is returned.
 *  @returns The result of the second parser.
 */
template <typename T1, typename T2>
auto Fold(Parser<T1> p1, Parser<T2> p2) -> decltype(auto)
{
    return Parser<T2>
    {
        [p1, p2](State const& state) -> Result<T2>
        {
            auto r1 = p1(state);
            if (!r1.Ok())
            {
                return Result<T2>::Failure(state, r1.Error());
            }

            auto r2 = p2(r1.Rest());
            return r2;
        },
        "fold"
    };
}

// clang-format on
