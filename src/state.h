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

    auto Advance() const -> State
    {
        if (m_source.empty()) {
            return m_source;
        }
        return m_source.subspan(1);
    }

    friend auto operator==(const State& a, const State& b) -> bool
    {
        if (a.m_source.size() != b.m_source.size()) {
            return false;
        }

        for (size_t i = 0; i < a.m_source.size(); ++i) {
            if (a.m_source[i] != b.m_source[i]) {
                return false;
            }
        }

        return true;
    }
};
