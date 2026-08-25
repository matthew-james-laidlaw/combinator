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
    
    ASSERT_TRUE(state.Done());
    ASSERT_EQ(state.Peek(), "");

    auto new_state = state.Advance();
    ASSERT_TRUE(new_state.Done());
    ASSERT_EQ(new_state.Peek(), "");
}

TEST(StateTests, LastItemInState)
{
    auto source = std::vector<std::string>
    {
        "a"
    };
    auto state = State(source);
    
    ASSERT_FALSE(state.Done());
    ASSERT_EQ(state.Peek(), "a");
    
    auto new_state = state.Advance();
    ASSERT_TRUE(new_state.Done());
    ASSERT_EQ(new_state.Peek(), "");
}

TEST(StateTests, ManyItemsInState)
{
    auto source = std::vector<std::string>
    {
        "a", "b", "c"
    };
    auto state = State(source);
    
    ASSERT_FALSE(state.Done());
    ASSERT_EQ(state.Peek(), "a");

    auto new_state = state.Advance();
    ASSERT_FALSE(new_state.Done());
    ASSERT_EQ(new_state.Peek(), "b");
}

TEST(ParserTests, BasicParserTest)
{
    auto parser = Parser<bool>
    {
        [&](State const& state) -> Result<bool>
        {
            return Result<bool>::Success(true, state);
        },
        "example"
    };

    ASSERT_EQ(parser.Name(), "example");

    auto empty_state = State({});
    auto result = parser(empty_state);
    ASSERT_TRUE(result.Ok());
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

    ASSERT_TRUE(result.Ok());
    ASSERT_EQ(result.Value(), "a");
}

TEST(ExpectTests, ExpectOnEmptyState)
{
    auto source = std::vector<std::string>();
    auto state = State(source);

    auto parser = Expect("a");
    auto result = parser(state);

    ASSERT_FALSE(result.Ok());
    ASSERT_EQ(result.Error(), "unexpected end of source: expected 'a'.");
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

    ASSERT_FALSE(result.Ok());
    ASSERT_EQ(result.Error(), "unexpected token: expected 'z' but got 'a'.");
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

    ASSERT_TRUE(result.Ok());
    ASSERT_EQ(result.Value(), "a");
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

    ASSERT_TRUE(result.Ok());
    ASSERT_EQ(result.Value(), "a");
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

    ASSERT_TRUE(result.Ok());
    ASSERT_EQ(result.Value(), "a");
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

    ASSERT_FALSE(result.Ok());
    ASSERT_EQ(result.Error(), "expected one of ['x', 'y', 'z'] but got 'a'.");
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

    ASSERT_TRUE(result.Ok());
    ASSERT_TRUE(result.Value());
    ASSERT_EQ(*result.Value(), "a");
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

    ASSERT_TRUE(result.Ok());
    ASSERT_FALSE(result.Value());
}

// clang-format on
