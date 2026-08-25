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
