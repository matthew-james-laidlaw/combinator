#pragma once

#include <parser.h>
#include <state.h>
#include <utilities.h>

#include <expected>
#include <format>
#include <string>
#include <utility>

// clang-format off

/** @brief Attempt a collection of sub-parsers. The first to succeed is returned. If none of them succeed the whole rule fails.
 *  @tparam Ps Sub-parser parameter pack.
 *  @param parsers Collection of sub-parsers.
 *  @returns A callable parser returning the matched token or a parse failure.
 */
template <typename... Ps>
auto Choice(Ps&&... parsers) -> decltype(auto)
{
	return Parser
	{
		[parsers...](State& state) -> std::expected<std::string, std::string>
		{
			for (auto const& p : { parsers... })
			{
				auto result = p(state);
				if (result)
				{
					return result;
				}
			}

			auto names = std::vector<std::string>();
			names.reserve(sizeof...(parsers));
			(names.push_back(parsers.Name()), ...);

			return std::unexpected(
				std::format("expected one of ['{}'] but got '{}'.", Join(names, "', '"), state.Peek())
			);
		},
		"choice"
	};
}

// clang-format on
