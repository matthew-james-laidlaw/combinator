#pragma once

#include <state.h>

#include <optional>
#include <stdexcept>
#include <string>

/** @brief Holds the result of a parser. Can either be constructed with Success where we
 * capture the successful result of a parser and the remaining state, or with Failure
 * where we capture the previous state and an error message.
 */
template <typename T>
class Result
{
private:

    std::optional<T> m_value;
    State m_rest;
    std::string m_error;

    Result(std::optional<T> value, State rest, std::string error)
        : m_value(value), m_rest(rest), m_error(error)
    {}

public:

    static auto Success(T value, State rest)
    {
        return Result(value, rest, "");
    }

    static auto Failure(State rest, std::string error)
    {
        return Result(std::nullopt, rest, error);
    }

    Result(const Result& other)
        : Result(other.m_value, other.m_rest, other.m_error)
    {}

    auto operator=(const Result& other) -> Result&
    {
        if (&other != this) {
            m_value = other.m_value;
            m_rest = other.m_rest;
            m_error = other.m_error;
        }
        return *this;
    }

    auto Ok() const -> bool
    {
        return static_cast<bool>(m_value);
    }

    auto Value() const -> T
    {
        if (!m_value) {
            throw std::runtime_error("attempted dereference of empty optional");
        }
        return *m_value;
    }

    auto Rest() const -> State
    {
        return m_rest;
    }

    auto Error() const -> std::string
    {
        return m_error;
    }
};
