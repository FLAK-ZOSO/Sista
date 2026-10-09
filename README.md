# `Sista`

`Sista` is a *lightweight*, *fast*, *easy-to-use*, *memory-safe* and *OS-agnostic* *object-oriented* library for making terminal videogames and animations in `C++`.

`Sista` provides a set of classes and functions to make terminal games in `C++` easier, shielding developers from having to reinvent the wheel every time they want to make a terminal videogame.

## Installation

### Sista as a source library

To install Sista, simply download the latest release from [`GitHub`](https://github.com/FLAK-ZOSO/Sista/releases), and extract the contents of the archive to your project's source directory.

### Sista as a compiled library

If you want to use Sista as a compiled library, use the provided `Makefile`. Build the libraries first, then install them with administrative privileges.

```bash
make
sudo make install
```

`make` (equivalently, `make all` or `make build`) builds the core and C API libraries in both shared and static forms, using the platform's shared-library format. Shared libraries dynamically link system dependencies. Static archives contain only Sista objects.

`make install` installs the libraries in the system library path and the headers in the system include path. This is the preferred inclusion method for versions v`3.0.0` and later. More on this in the [documentation](https://sista.readthedocs.io/en/latest/).

```bash
sudo make uninstall
```

This will remove the installed files from the system library and include paths. The same disclaimer applies as above, you will need administrative privileges to run this command.

### More GNU Make targets

The terminal demo is optional and can be built with `make sista`. It embeds Sista while dynamically linking system dependencies. `make sista_against_static_lib_local` explicitly links the local Sista archive with the same dependency policy.

The Makefile follows the conventional cleanup target hierarchy:

- `make mostlyclean` removes intermediate object files while preserving built libraries and the optional `sista` executable.
- `make clean` removes every normal build output, including libraries and `sista`.
- `make distclean` additionally removes generated documentation.
- `make maintainer-clean` additionally removes `TAGS` and distribution archives.

Other standard GNU Make targets are available:

- `make check` (or `make test`) builds and runs the self-test without installing Sista.
- `make installcheck` tests the installed shared library.
- `make installdirs`, `make install-strip`, and `make uninstall` manage installation directories and installed files. `install` preserves debugging information; `install-strip` strips the installed shared libraries without modifying the build tree. Static archives retain their debugging information.
- The section-3 and section-7 man pages in `docs/man` are hand-written roff files, ready to install. `make man` checks that they exist; editing one requires no generation step. Use `make check-man` to render and validate them and compile their examples (requires Python 3, Groff, and C/C++ compilers). Preview a page with `man -l docs/man/sista.7`.
- `make install` and `make install-man` install the man pages and aliases for common class and C function names. `make html` generates the exhaustive Doxygen reference, and `make install-html` installs it. The `info`, `dvi`, `pdf`, and `ps` targets and their installation counterparts are successful no-ops because Sista has no manuals in those formats.
- `make TAGS` creates an Emacs tags table
- `make dist` creates `sista-VERSION.tar.gz` from the current Git revision.

### Sista as a shared library - `.deb` package

We release a `.deb` package for Debian and derivatives with each release. The upload is manual for the moment.

- go to the [latest release](https://github.com/FLAK-ZOSO/Sista/releases)
- download the `sista_<VERSION>_<ARCHITECTURE>.deb` release asset
- use `sudo apt install path/to/sista_<VERSION>_amd64.deb`, like `sudo apt install ~/Downloads/sista_3.0.0-1_amd64.deb`

For the moment only `amd64` (for x86_64 architectures essentially) packages are published. With the right tools you can package your own.

```bash
git clone https://github.com/FLAK-ZOSO/Sista
cd packageroot
debuild -us -uc -a arm64 -b # Specify your architecture, such as "i386", "arm64", "amd64"
```

### Sista as a shared library - `.rpm` package

We also publish an RPM package for Fedora, RHEL-derived distributions, and
other RPM-based systems. Download the `sista-<VERSION>-<RELEASE>.<ARCH>.rpm`
asset from the [latest release](https://github.com/FLAK-ZOSO/Sista/releases),
then install it with your package manager, for example:

```bash
sudo dnf install ~/Downloads/sista-3.1.0-0.rc2.el9.x86_64.rpm
```

To build an RPM locally, install `rpm-build` and run:

```bash
packageroot/rpm/build-rpm.sh
```

The resulting package is placed under `rpmbuild/RPMS/`.

## Usage

### Using Sista as a source library

To use Sista, simply include the `"sista.hpp"` header in your project's source files.

```cpp

#include "include/sista/sista.hpp"

```

The `"sista.hpp"` header includes all of the other headers in the `"include/sista/"` directory, so you don't have to include them individually.

### Using Sista as a shared library

You also need to include the `"sista/sista.hpp"` header in your source files, as shown above.

```cpp
#include <sista/sista.hpp>
```

This approach will require you to link against `libSista` when compiling your project. You can do this by adding the `-lSista` flag to your `g++` command.

```bash
g++ -std=c++17 -o my_project my_project.cpp -lSista
``` 

See the [documentation](https://sista.readthedocs.io/en/latest/) for more details on how to use Sista as a shared library and how to link against it. A comprehensive example is provided in the [`Makefile`](Makefile) in the repository, together with the installation targets.

## Documentation

The English tutorials and basic documentation for Sista can be found at [`Sista - ReadTheDocs`](https://sista.readthedocs.io/).

The actual, detailed documentation of both library and C API can be found at [`flak-zoso.github.io`](https://flak-zoso.github.io/Sista/) and is automatically generated from the source code using [`Doxygen`](https://www.doxygen.nl/).

Under the `demo/` directory, you can find many minimal demos that showcase the features of Sista. These demos are minimal examples and do not aim to provide a complete walkthrough of the library, unlike the `sista.cpp` example. Their description is provided in the [`demo/README.md`](demo/README.md) file.

Additional information about versions can be found in the [`Release Notes`](ReleaseNotes.md).

The documentation for the Python module can be found at [`flak-zoso.github.io/Sista/sista-python/`](https://flak-zoso.github.io/Sista/sista-python).


## Sista-based works

Here are some of the most relevant works based on Sista.

- [`Inomhus`](https://github.com/FLAK-ZOSO/Inomhus) - _Bättre att stanna inomhus_ (better be in the house) - a survival videogame
- [`Starklag`](https://github.com/Lioydiano/Starklag) - _den starkastes lag_ (the law of the strongest) - a partial evolution simulator
- [`Dödas`](https://github.com/Lioydiano/Dodas) - _de dödas angrepp_ (attack of the dead) - a survival speedrun videogame
- [`Dune`](https://github.com/Lioydiano/Dune) - a survival videogame inspired by Dune
- [`Inävjaga`](https://github.com/FLAK-ZOSO/Inavjaga) - _Inälvor jagade_ (intestin hunt) - a survival videogame with hordes of enemies
