# Combinator

The Combinator project is a combinatorial parsing framework for C++ implemented as an [embedded domain-specific-language (eDSL)](https://en.wikipedia.org/wiki/Domain-specific_language#Domain-specific_language_topics) using operator overloads. A parser combinator is a function that composes simpler parsers into a more complex one. Combinatorial parsing allows for rapid prototyping due to the simplicity of plugging together primitive parsers.

## Parser Combinators

### Expect

The expect parser is the most primitive parser, all it does is expect a given token from the source stream. Other parsers will combine primitives like this to make more complicated parsers.

This parser expects the text "fun" from the source string.

```c++
auto parser = Expect("fun");
```

### Choice

The choice parser takes in a variadic number of sub-parsers and attempts each one in order. The first parser to succeed is returned. If none of the parsers in the list pass, the whole parser fails.

This creates a parser that can either match "fun" or "var".

```c++
auto parser = Choice(Expect("fun"), Expect("var"));
```

### Maybe

The maybe parser takes in a single sub-parser and makes its success optional. On success returns the sub-parser, otherwise returns a std::nullopt without a failure.

The below parser will not fail if "fun" is not next in the source stream.

```c++
auto parser = Maybe(Expect("fun"));
```

### Many

The many parser takes in a single sub-parser rule and runs it until it fails, allowing for zero successes. The parser returns a list of results accumulated from each successful run.

This parser will match the string "fun" until it stops showing up in the source stream.

```c++
auto parser = Many(Expect("fun"));
```
