# Utilxx
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Utlixx is a header only lib, which contains different types and functions I am using across multiple projects.
Utilxx is a C++17 libary and can therefor only be used with compilers supporting C++17.

A lot of types are move only to avoid copying, and most types support a monad-like interface with the functions
`flatMap` and `map`.

### Opt
`Opt` is an optional type which is based on `std::optional` but with an monad-like interface through
`flatMap` and `map`. Aside from that free functions such as `traverse` make it easy to use `Opt`
with `std::vector`.

### Result
`Result` is a type like `std::expected` which is proposed to be added to the standard. It can be used as return type of functions, holding either the result of the function or an error. `Result` also has a monad-like interface through
`flatMap` and `map`. And also free functions like `Try` to wrap up call which might throw an exception into a `Result`.
