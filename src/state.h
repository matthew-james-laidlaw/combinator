#pragma once

#include <span>
#include <string>

class State
{
private:

    std::span<std::string> m_source;

public:

    State(std::span<std::string> source)
        : m_source(source)
    {}

    auto Done() const -> bool
    {
        return m_source.empty();
    }

    auto Peek() const -> std::string
    {
        if (m_source.empty()) {
            return "";
        }
        return m_source.front();
    }

    auto Advance() -> void
    {
        if (m_source.empty()) {
            return;
        }
        m_source = m_source.subspan(1);
    }
};
