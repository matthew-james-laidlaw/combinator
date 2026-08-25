# Combinator

The Combinator project is a combinatorial parsing framework for C++ implemented as an [embedded domain-specific-language (eDSL)](https://en.wikipedia.org/wiki/Domain-specific_language#Domain-specific_language_topics) using operator overloads. A parser combinator is a function that composes simpler parsers into a more complex one. Combinatorial parsing allows for rapid prototyping due to the simplicity of plugging together primitive parsers.

## Parser Combinators

### Expect

The expect parser is the most primitive parser, all it does is expect a given token from the source stream. Other parsers will combine primitives like this to make more complicated parsers.

```c++
auto parser = Expect("fun");
```
