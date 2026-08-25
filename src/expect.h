#pragma once

#include <parser.h>

#include <expected>
#include <string>

// clang-format off

/** @brief Primitive parser that expects a given string from the source. Advances the state on success.
 * @param expected The expected string.
 * @returns A parser that parses the expected string or returns a parse error.
 */
auto Expect(std::string expected) -> decltype(auto)
{
	return Parser
	{
		[expected](State& state) -> std::expected<std::string, std::string>
		{
			if (state.Done())
			{
				auto msg = std::format("unexpected end of source: expected '{}'.", expected);
				return std::unexpected(msg);
			}

			auto actual = state.Peek();
			if (actual != expected)
			{
				auto msg = std::format("unexpected token: expected '{}' but got '{}'.", expected, actual);
				return std::unexpected(msg);
			}

			state.Advance();
			return actual;
		},
		expected
	};
}

// clang-format on
