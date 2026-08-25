#pragma once

#include <state.h>

#include <string>

template <typename F>
class Parser
{
private:

    F m_parser;
    std::string m_name;

public:

    using ResultType = std::invoke_result_t<F, State&>;

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
