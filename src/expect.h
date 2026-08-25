#pragma once

#include <parser.h>

#include <expected>
#include <format>
#include <string>

// clang-format off

/** @brief   Primitive parser that expects a given string from the source. Advances the state on
 *           success.
 *  @param   expected The expected string.
 *  @returns A parser that parses the expected string or returns a parse error.
 */
auto Expect(std::string expected) -> decltype(auto)
{
	using R = Result<std::string>;
	return Parser<std::string>
	{
		[expected](State const& state) -> R
		{
			if (state.Done())
			{
				auto msg = std::format("unexpected end of source: expected '{}'.", expected);
				return R::Failure(state, msg);
			}

			auto actual = state.Peek();
			if (actual != expected)
			{
				auto msg = std::format("unexpected token: expected '{}' but got '{}'.", expected, actual);
				return R::Failure(state, msg);
			}

			return R::Success(actual, state.Advance());
		},
		expected
	};
}

// clang-format on
