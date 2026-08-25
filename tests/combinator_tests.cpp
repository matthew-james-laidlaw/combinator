#include <gtest/gtest.h>

#include <choice.h>
#include <expect.h>
#include <maybe.h>
#include <parser.h>
#include <state.h>

// clang-format off

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

TEST(ChoiceTests, MatchFirstItem)
{
    auto source = std::vector<std::string>
    {
        "a", "b", "c"
    };
    auto state = State(source);

    auto parser = Choice(Expect("a"), Expect("y"), Expect("z"));
    auto result = parser(state);

    ASSERT_TRUE(result);
    ASSERT_EQ(*result, "a");
}

TEST(ChoiceTests, MatchMiddleItem)
{
    auto source = std::vector<std::string>
    {
        "a", "b", "c"
    };
    auto state = State(source);

    auto parser = Choice(Expect("y"), Expect("a"), Expect("z"));
    auto result = parser(state);

    ASSERT_TRUE(result);
    ASSERT_EQ(*result, "a");
}

TEST(ChoiceTests, MatchLastItem)
{
    auto source = std::vector<std::string>
    {
        "a", "b", "c"
    };
    auto state = State(source);

    auto parser = Choice(Expect("y"), Expect("z"), Expect("a"));
    auto result = parser(state);

    ASSERT_TRUE(result);
    ASSERT_EQ(*result, "a");
}

TEST(ChoiceTests, NoMatches)
{
    auto source = std::vector<std::string>
    {
        "a", "b", "c"
    };
    auto state = State(source);

    auto parser = Choice(Expect("x"), Expect("y"), Expect("z"));
    auto result = parser(state);

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), "expected one of ['x', 'y', 'z'] but got 'a'.");
}

TEST(MaybeTests, Matches)
{
    auto source = std::vector<std::string>
    {
        "a", "b", "c"
    };
    auto state = State(source);

    auto parser = Maybe(Expect("a"));
    auto result = parser(state);

    ASSERT_TRUE(result);
    ASSERT_TRUE(*result);
    EXPECT_EQ(result->value(), "a");
}

TEST(MaybeTests, DoesntMatch)
{
    auto source = std::vector<std::string>
    {
        "a", "b", "c"
    };
    auto state = State(source);

    auto parser = Maybe(Expect("x"));
    auto result = parser(state);

    ASSERT_TRUE(result);
    ASSERT_FALSE(*result);
}

// clang-format on
