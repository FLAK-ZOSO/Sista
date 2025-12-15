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




### Added
- C API (api.h / api.cpp) and packaging files under `packageroot`.
- std::hash specialization for `sista::Coordinates`.
- `.deb` packaging assets.
- CI workflows updated to build and test the C API.

### Changed
- `sista::Field` now uses `std::shared_ptr<sista::Pawn>` for pawn storage.
- Converted many `enum` types to `enum class` for stronger type safety.
- Moved ANSI functionality into `sista::` and renamed `ANSI::Settings` → `sista::ANSISettings`.
- Renamed `ANSI-Settings.hpp/.cpp` → `ansi.hpp/.cpp`.
- Reworked `sista::ANSISettings::apply()` to use `std::variant` utilities.
- Converted `sista::Coordinates::set` → `sista::Coordinates::goTo`.
- `Cursor` no longer exposes `x`/`y` members; cursor movement API simplified.
- Many functions and overloads updated to use const-correct references or pass-by-value.
- Minimized header includes to reduce build dependencies and improve compile times.
- Updated demos and documentation to use `std::shared_ptr` and `std::make_shared`.
- Makefile and CI updated for renamed files and shared/C API builds; MacOS rpath handling improved.
- Improved encapsulation and internal performance of `SwappableField` and moved some logic to `Field`.

### Removed
- `Field::reset()` (redundant with `Field::clear()` after refactor).
- `ANSI` namespace (moved into `sista::`).
- Public alias `sista::Coord` and all APIs that accepted it.
- Overloads using non-const reference parameters where unnecessary.

### Fixed
- Cursor move overloads (corrected types for SCO save/restore).
- Memory-safety issues validated with valgrind (no leaks reported).

---

## [2.2.1] - patch
### Changed
- Makefile tweaks for MacOS installation.

---

## [2.2.0] - minor
### Added
- Build and install support for Windows shared library via MinGW/MSYS2 toolchains (MSVC not supported).

---

## [2.1.2] - patch
### Added
- New demo `shared-test-static`.
### Changed
- Demo Makefiles and CI to include the new demo.

---

## [2.1.1] - patch
### Fixed
- Makefile fixes allowing demos to build without Sista being installed.
### Added
- Demo documentation (`demo/README.md`).
- Documentation updates on ReadTheDocs.

---

## [2.1.0] - minor
### Changed
- Installer path for libSista.so adjusted to `{PREFIX}/lib/libSista.so`.
- Added `uninstall` target to Makefile.
### Added
- `demo/shared-test.cpp` and related Makefile target.

---

## [2.0.0] - major
### Added
- Shared library distribution (`libSista.so`) and install targets.

---

## [1.1.8] - patch
### Fixed
- Corrected `sista::Coordinates::operator<` to provide a strict weak ordering:
  - Compare `y` first, then `x`.

---

## [1.1.7] - patch
### Changed
- Allow mixed initialization of `ANSI::Settings` with `ForegroundColor`, `BackgroundColor`, and `RGBColor`.

---

## [1.1.6] - patch
### Added
- `<` operator for `sista::Coordinates` (previous implementation based on distance from origin).

---

## [1.1.5] - patch
### Added
- `RGBColor` support and integration with `ANSI::Settings` (24-bit color support).
### Changed
- Backwards-compatible initializers preserved for `ForegroundColor`/`BackgroundColor`.

---

## [1.1.4] - patch
### Added
- `sista::Field::removePawn(Coordinates&)` and `sista::Field::erasePawn(Coordinates&)` to remove/erase pawns by coordinates.

---

## [1.1.3] - patch
### Added
- `sista::Field::rePrintPawn(Pawn*)`.
- Scalar multiplication operator for `sista::Coordinates`.

---

## [1.1.2] - patch
### Added
- Additional arithmetic operators for `sista::Coordinates`: `-`, `+=`, `-=`.

---

## [1.1.1] - patch
### Added
- `sista::Field::erasePawn(Pawn*)` to remove and clear a pawn from the screen.

---

## [1.0.0] - minor
### Changed
- Project split into `.hpp` headers and `.cpp` sources to support multi-file projects.

---

## [0.9.4] - patch
### Added
- `sista::Field::addPrintPawn(Pawn*)` to add a pawn and print it without reprinting the whole field.

---

## [0.9.3] - patch
### Fixed
- Fixed `sista::Field::reset()` logic that previously resized the field to 0×0 and ensured proper deletion and clearing of pawns.

---

## [0.9.2] - minor
### Added
- ScreenMode management and resetter for Field instances (`reset()` to clear pawns safely).

---

## [0.9.0] - minor
### Added
- 256-color and 24-bit RGB ANSI color support for foreground/background.

---

## [0.8.0] - minor
### Added
- Additional ANSI cursor commands, SCO/DEC cursor controls and `ESC` constant.

---

## [0.7.1] - patch
### Changed
- Fixed attribute reset logic for `BRIGHT` attribute to use correct reset code.

---

## [0.1.0] - initial
### Added
- Initial development version of Sista.

---

### Notes
- Entries are grouped as Added, Changed, Deprecated, Removed, Fixed, Security where applicable.
- Use the Unreleased section to collect upcoming changes before a release.

[Unreleased]: #unreleased
