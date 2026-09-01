#pragma once

#include <parser.h>

#include <array>

// clang-format off

template <typename T, typename... Ts>
auto Combine(Parser<T> first, Parser<Ts>... rest) -> decltype(auto)
{
    using R = std::array<T, sizeof...(Ts) + 1>;
    return Parser<R>
    {
        [first, rest...](State const& state)
        {
            auto current = state;
            auto results = R();
            size_t i = 0;
            for (auto const& p : { first, rest... })
			{
				auto result = p(current);
				if (!result.Ok())
				{
					return result;
				}
                current = result.Rest();
                results[i++] = result;
			}
        },
        "combine"
    };
}

// clang-format on
