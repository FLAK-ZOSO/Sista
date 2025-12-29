# Changelog

All notable changes to Sista are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/) and this project follows [Semantic Versioning](https://semver.org/spec/v2.0.0.html) since version 2. More details can be found in the [release notes](ReleaseNotes.md).

## [Unreleased]

### Added

- Added `std::hash` specialization for `sista::Coordinates` to allow its use in hash-based containers like `std::unordered_map` and `std::unordered_set`

- Improved internal implementation of `sista::ANSISettings::apply()` for better readability and semantics with [`std::variant::holds_alternative`](https://en.cppreference.com/w/cpp/utility/variant/holds_alternative)
- Added `const` qualifier to methods that do not modify the state of the object for better semantics and to allow calling them on `const` instances

- Testing on memory safety with `valgrind`, detected no memory leaks or invalid accesses

- Added files for `.deb` packaging under `packageroot`

- Exposed C API for stable ABI that allows FFI bindings and easier integration with other programming languages
    - Added `api.h` header file with C API declarations
    - Added `api.cpp` implementation file with C API definitions
    - Updated `Makefile` to build the C API and link it with the C++ library
- Updated CI workflows to build and test the C API

- Added Python C extension module `sista._sista` loaded in the `sista` Python module
    - Added `python/` directory with the C extension source code and `setup.py` for building and installing the Python module
    - Updated CI workflows to build and test the Python module

### Changed

- Changed `sista::Field` to use `std::shared_ptr<sista::Pawn>` instead of raw pointers for memory safety and easier memory management
    - Removed `Field::reset` method as it is redundant with `Field::clear` in this context
- Updated demos to use `std::shared_ptr<sista::Pawn>` and `std::make_shared<sista::Pawn>` for creating and managing pawns
- Updated documentation to reflect changes in `sista::Field` and `sista::Pawn` usage

- Renamed `ANSI-Settings.hpp` and `ANSI-Settings.cpp` to `ansi.hpp` and `ansi.cpp` respectively for consistency with other filenames
- Removed overloads with non-const reference parameters and replaced them with overloads taking parameters by value or const reference

- Renamed `sista::Coordinates::set` to `goTo` for better clarity (it moves the cursor to the coordinates)
- Using `const` qualifier for references where appropriate for better performance and semantics
- Moving `sista::SwappableField::movingByCoordinates` to `sista::Field` as it does not depend on `SwappableField` functionality

- Wrapped former `_EFFECT` constants into a scoped `enum class Effect` inside the `sista` namespace
- Changed `enum` types to `enum class` for better type safety and to avoid name clashes
    - Fixed `Cursor::move` overload using `MoveCursorSCO`, which was incorrectly using `int` instead of `char`

- Updated `Makefile` for hardcoding the rpath of the MacOS shared library to avoid issues with `DYLD_LIBRARY_PATH`
- Updated `Makefile` to reflect the new filenames and ensure correct compilation and linking

- Minimized includes in header files to reduce compilation dependencies and improve build times
- Optimized `sista::SwappableField` internal logic for better performance
- Improved encapsulation of `sista::SwappableField` by making internal methods private and exposing only necessary public methods

- Constructor and destructor of `sista::Cursor` only hide/show the cursor, but do not alter the ANSI settings nor clear the screen anymore

### Removed

- Removed `ANSI` namespace and moved all ANSI-related functionality to `sista::`, among which `ANSI::Settings`->`sista::ANSISettings`
- Removed `sista::Coord` type alias of `std::pair<unsigned short, unsigned short>` to minimize the public surface area of the library
    - Removed all functions taking `sista::Coord` as parameter
    - Created static methods in `sista::Coordinates` to convert from and to `std::pair<unsigned short, unsigned short>`
- Removed `y` and `x` attributes from `sista::Cursor`, as they were not used outside the struct nor necessary for its functionality

## [`2.2.1`] - added

### Added

- Adapted `Makefile` for MacOS install

## [`2.2.0`] - minor

### Added

- `Sista` now available as a shared library on Windows via `MinGW`, `MSYS2` or alternative toolchains

## [`2.1.2`] - patch

### Added

- Added new demo `shared-test-static` to test static linking against the `Sista` library
- Updated `demo/Makefile` to include the new demo and to build it correctly
- Updated Makefile CI workflow to build all demos, including the new `shared-test-static` demo

## [`2.1.1`] - patch

### Changed

- Changed the `Makefile` to correctly build the demos without the need for `Sista` to be installed

### Added

- Added documentation in the `demo/README.md` file
- Updated and refreshed the documentation on ReadTheDocs, under `docs/`

## [`2.1.0`] - minor

- Changed path of the `libSista.so` shared library from `{PREFIX}/lib64/libSista.so` to `{PREFIX}/lib/libSista.so` for `ld` to find it correctly on most systems
- Added `uninstall` target to the `Makefile` to remove the installed files
- Added `demo/shared-test.cpp` and related `Makefile` target to test the shared library installation

## [`2.0.0`] - major

- Sista now available as a shared library, `libSista.so`, which can be installed in the system library path

## [`1.1.8`] - patch

### Fixed

- Fixed `sista::Coordinates` operator overload `<` to be a strict weak ordering relation

## [`1.1.7`] - patch

### Changed

- Allow `ANSI::Settings` to be initialized with mixed `ForegroundColor` and `RGBColor` or `RGBColor` and `BackgroundColor`

## [`1.1.6`] - patch

### Added

- Added `<` comparison operator to `sista::Coordinates`

## [`1.1.5`] - patch

### Added

- Added `RGBColor` and support for it in the `ANSI::Settings` struct

## [`1.1.4`] - patch

### Added

- Added `sista::Field::removePawn(sista::Coordinates&)` to remove a pawn from the field by coordinates without the need of a pointer to the pawn
- Added `sista::Field::erasePawn(sista::Coordinates&)` to erase a pawn from the field by coordinates without the need of a pointer to the pawn

## [`1.1.3`] - patch

### Added

- Added `sista::Field::rePrintPawn()`
- Added operator (`*`) for scalar multiplication for `sista::Coordinates` struct

## [`1.1.2`] - patch

### Added

- Added more operators for `sista::Coordinates` struct

## [`1.1.1`] - patch

### Added

- Added `sista::Field::erasePawn()` to remove and erase Pawn from the screen

## [`1.0.0`] - major

### Changed

- Divided Sista in `.hpp` headers and `.cpp` sources

## [`0.9.4`] - patch

### Added

- Added `sista::Field::addPrintPawn()` to add and print Pawn without reprint

## [`0.9.3`] - patch

### Fixed

- Fixed `sista::Field::reset()` which was resizing the field to 0x0

## [`0.9.2`] - patch

### Added

- Added ScreenMode management
- Added resetter for `sista::Field` instances, to empty the field from the `sista::Pawn`s

## [`0.9.0`] - minor

### Added

- Added 256 color support
- Added 24-biit RGB color support

## [`0.8.0`] - minor

### Added

- Added [more ANSI cursor commands](https://github.com/FLAK-ZOSO/Sista/blob/3f861a7e1f61609f4d8f9cf03aaaf3c056db1278/include/sista/cursor.hpp#L70-L89)
- Added `ESC` constant to `ANSI-Settings.hpp`

## [`0.7.1`] - patch

### Fixed

- Added [condition](https://github.com/FLAK-ZOSO/Sista/blob/10d881c7c5f999d4d5741a70e17bfeb271f14825/include/sista/ansi.cpp#L39-L45) over the attribute reset function

---

### Notes
- Entries are grouped as Added, Changed, Deprecated, Removed, Fixed, Security where applicable.
- Use the Unreleased section to collect upcoming changes before a release.

[Unreleased]: #unreleased
