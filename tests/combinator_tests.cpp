// clang-format off

#include <gtest/gtest.h>

#include <parser.h>

TEST(ParserTests, BasicParserTest)
{
    auto parser = Parser
    {
        [&](State& state) -> bool
        {
            return true;
        },
        "example"
    };

    EXPECT_EQ(parser.Name(), "example");

    auto empty_state = State({});
    EXPECT_TRUE(parser(empty_state));
}

TEST(StateTests, EmptyState)
{
    auto state = State({});
    
    EXPECT_TRUE(state.Done());
    EXPECT_EQ(state.Peek(), "");
    state.Advance();
    EXPECT_TRUE(state.Done());
    EXPECT_EQ(state.Peek(), "");
}

TEST(StateTests, LastItemInState)
{
    auto source = std::vector<std::string>
    {
        "a"
    };
    auto state = State(source);
    
    EXPECT_FALSE(state.Done());
    EXPECT_EQ(state.Peek(), "a");
    state.Advance();
    EXPECT_TRUE(state.Done());
    EXPECT_EQ(state.Peek(), "");
}

TEST(StateTests, ManyItemsInState)
{
    auto source = std::vector<std::string>
    {
        "a", "b", "c"
    };
    auto state = State(source);
    
    EXPECT_FALSE(state.Done());
    EXPECT_EQ(state.Peek(), "a");
    state.Advance();
    EXPECT_FALSE(state.Done());
    EXPECT_EQ(state.Peek(), "b");
}

// clang-format on
