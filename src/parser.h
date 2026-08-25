#pragma once

#include <state.h>

#include <expected>
#include <functional>
#include <string>

template <typename T>
class Parser
{
private:

    using F = std::function<std::expected<T, std::string>(State&)>;
    F m_parser;

    std::string m_name;

public:

    Parser(F parser, std::string name)
        : m_parser(parser), m_name(name)
    {}

    auto operator()(State& state) const -> decltype(auto)
    {
        return m_parser(state);
    }

    auto Name() const -> std::string
    {
        return m_name;
    }
};
