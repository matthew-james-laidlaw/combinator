#pragma once

#include <parser.h>
#include <state.h>
#include <utilities.h>

#include <expected>
#include <format>
#include <string>
#include <utility>

// clang-format off

/** @brief   Attempt a collection of sub-parsers. The first to succeed is returned. If none of them
 *           succeed the whole rule fails.
 *  @param   first At least one parser is required
 *  @param   rest Variadic amount of other parsers
 *  @returns A callable parser returning the matched item or a parse failure.
 */
template <typename T, typename... Ts>
auto Choice(Parser<T> first, Parser<Ts>... rest) -> decltype(auto)
{
	static_assert(
		(std::same_as<T, Ts> && ...),
		"choice parser requires all sub-parsers to have the same return type"
	);

	return Parser<T>
	{
		[first, rest...](State& state) -> std::expected<T, std::string>
		{
			for (auto const& p : { first, rest... })
			{
				auto result = p(state);
				if (result)
				{
					return result;
				}
			}

			auto names = std::vector<std::string>();
			names.reserve(sizeof...(Ts) + 1);
			names.push_back(first.Name());
			(names.push_back(rest.Name()), ...);

			return std::unexpected(
				std::format("expected one of ['{}'] but got '{}'.", Join(names, "', '"), state.Peek())
			);
		},
		"choice"
	};
}

// clang-format on
