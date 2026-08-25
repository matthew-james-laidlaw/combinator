#pragma once

#include <result.h>
#include <state.h>

#include <expected>
#include <functional>
#include <string>

template <typename T>
class Parser
{
private:

    using F = std::function<Result<T>(const State&)>;
    F m_parser;

    std::string m_name;

public:

    Parser(F parser, std::string name)
        : m_parser(parser), m_name(name)
    {}

    auto operator()(const State& state) const -> decltype(auto)
    {
        return m_parser(state);
    }

    auto Name() const -> std::string
    {
        return m_name;
    }
};
