# `Sista`

`Sista` is a *lightweight*, *fast*, *easy-to-use* and *OS-agnostic* *object-oriented* library for making terminal videogames in `C++`.

`Sista` provides a set of classes and functions to make terminal games in `C++` easier, shielding developers from having to reinvent the wheel every time they want to make a terminal videogame.

## Installation

To install Sista, simply download the latest release from [`GitHub`](https://github.com/FLAK-ZOSO/Sista/releases), and extract the contents of the archive to your project's source directory.

If you want to use Sista as a shared library, you can use the provided `Makefile` in the repository. Simply run the following command in your terminal with administrative privileges:

```bash
make install
```

This will install the `libSista.so` shared library in the system library path, and the headers in the system include path. This is the preferred inclusion method in Linux for versions v`2.0.0` and later. More on this in the [documentation](https://sista.readthedocs.io/en/latest/).

## Usage

To use Sista, simply include the `"sista.hpp"` header in your project's source files.

```cpp

#include "include/sista/sista.hpp"

```

The `"sista.hpp"` header includes all of the other headers in the `"include/sista/"` directory, so you don't have to include them individually.

## Documentation

The english documentation for Sista can be found at [`Sista - ReadTheDocs`](https://sista.readthedocs.io/).

Additional information about versions can be found in the [`Release Notes`](ReleaseNotes.md).


## Sista-based works

Here are some of the most relevant works based on Sista.

- [`Inomhus`](https://github.com/FLAK-ZOSO/Inomhus) - _Bättre att stanna inomhus_ (better be in the house) - a survival videogame
- [`Starklag`](https://github.com/Lioydiano/Starklag) - _den starkastes lag_ (the law of the strongest) - a partial evolution simulator
- [`Dödas`](https://github.com/Lioydiano/Dodas) - _de dödas angrepp_ (attack of the dead) - a survival speedrun videogame
- [`Dune`](https://github.com/Lioydiano/Dune) - a survival videogame inspired by Dune
- [`Inävjaga`](https://github.com/FLAK-ZOSO/Inavjaga) - _Inälvor jagade_ (intestin hunt) - a survival videogame with hordes of enemies
