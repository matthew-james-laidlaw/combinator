// clang-format off

#include <gtest/gtest.h>

#include <expect.h>
#include <parser.h>
#include <state.h>

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

TEST(ExpectTests, ExpectNormal)
{
    auto source = std::vector<std::string>
    {
        "a", "b", "c"
    };
    auto state = State(source);

    auto parser = Expect("a");
    auto result = parser(state);

    ASSERT_TRUE(result);
    EXPECT_EQ(*result, "a");
}

TEST(ExpectTests, ExpectOnEmptyState)
{
    auto source = std::vector<std::string>();
    auto state = State(source);

    auto parser = Expect("a");
    auto result = parser(state);

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), "unexpected end of source: expected 'a'.");
}

TEST(ExpectTests, Unexpected)
{
    auto source = std::vector<std::string>
    {
        "a", "b", "c"
    };
    auto state = State(source);

    auto parser = Expect("z");
    auto result = parser(state);

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), "unexpected token: expected 'z' but got 'a'.");
}

// clang-format on
