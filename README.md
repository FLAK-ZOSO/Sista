# `Sista`

`Sista` is a *lightweight*, *fast*, and *easy-to-use* *OOP* library for making terminal games in `C++`.
`Sista` is a *header-only* library that provides a set of classes and functions to make it easier to create terminal games in `C++`.

Inspired by their [`Forsiktig`](https://github.com/Lioydiano/Forsiktig)'s [`variables.hpp`](https://github.com/Lioydiano/Forsiktig/blob/main/variables.hpp) header, @FLAK-ZOSO decided to make a library to prevent others from having to reinvent the wheel every time they wanted to make a terminal game.

## OS Compatibility

Sista is compatible with `Windows`.
It may work on any other OS which provides an ANSI-supporting Terminal.

The only thing that may not work is the `clearScreen()` function from `"clearScreen.h"`, which uses the `<Windows.h>` header.
If you want to use this function, you will have to replace it with your own implementation.
**NOTE**: This function is not used by any of the classes in Sista.

## Installation

To install Sista, simply download the latest release from [`GitHub`](https://github.com/FLAK-ZOSO/Sista), and extract the contents of the archive to your project's source directory.

## Usage

To use Sista, simply include the `"sista.hpp"` header in your project's source files.

```cpp

#include "include/sista/sista.hpp"

```

The `"sista.hpp"` header includes all of the other headers in the `"include/sista/"` directory, so you don't have to include them individually.

## Documentation

Some of the documentation for Sista can be found in the [`Release Notes`](ReleaseNotes.md) and [`Benchmarks`](Benchmarks.md) files.
