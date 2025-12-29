# Release Notes

Here you can find the release notes for each version of `Sista` since `v0.1.0`, with changelog since v`0.7.0`; these are listed in a bottom-up order.

## Unreleased v`3.0.0`

Major release.

- Changed `sista::Field` to use `std::shared_ptr<sista::Pawn>` instead of raw pointers for memory safety and easier memory management
    - Removed `Field::reset` method as it is redundant with `Field::clear` in this context
- Updated demos to use `std::shared_ptr<sista::Pawn>` and `std::make_shared<sista::Pawn>` for creating and managing pawns
- Updated documentation to reflect changes in `sista::Field` and `sista::Pawn` usage
- Removed `ANSI` namespace and moved all ANSI-related functionality to `sista::`, among which `ANSI::Settings`->`sista::ANSISettings`
- Wrapped former `_EFFECT` constants into a scoped `enum class Effect` inside the `sista` namespace
- Changed `enum` types to `enum class` for better type safety and to avoid name clashes
    - Fixed `Cursor::move` overload using `MoveCursorSCO`, which was incorrectly using `int` instead of `char`
- Renamed `ANSI-Settings.hpp` and `ANSI-Settings.cpp` to `ansi.hpp` and `ansi.cpp` respectively for consistency with other filenames
- Removed overloads with non-const reference parameters and replaced them with overloads taking parameters by value or const reference
- Improved internal implementation of `sista::ANSISettings::apply()` for better readability and semantics with [`std::variant::holds_alternative`](https://en.cppreference.com/w/cpp/utility/variant/holds_alternative)
- Removed `sista::Coord` type alias of `std::pair<unsigned short, unsigned short>` to minimize the public surface area of the library
    - Removed all functions taking `sista::Coord` as parameter
    - Created static methods in `sista::Coordinates` to convert from and to `std::pair<unsigned short, unsigned short>`
- Removed `y` and `x` attributes from `sista::Cursor`, as they were not used outside the struct nor necessary for its functionality
- Renamed `sista::Coordinates::set` to `goTo` for better clarity (it moves the cursor to the coordinates)
- Using `const` qualifier for references where appropriate for better performance and semantics
- Added `const` qualifier to methods that do not modify the state of the object for better semantics and to allow calling them on `const` instances
- Moving `sista::SwappableField::movingByCoordinates` to `sista::Field` as it does not depend on `SwappableField` functionality
- Minimized includes in header files to reduce compilation dependencies and improve build times
- Added `std::hash` specialization for `sista::Coordinates` to allow its use in hash-based containers like `std::unordered_map` and `std::unordered_set`
- Optimized `sista::SwappableField` internal logic for better performance
- Improved encapsulation of `sista::SwappableField` by making internal methods private and exposing only necessary public methods
- Exposed C API for stable ABI that allows FFI bindings and easier integration with other programming languages
    - Added `api.h` header file with C API declarations
    - Added `api.cpp` implementation file with C API definitions
    - Updated `Makefile` to build the C API and link it with the C++ library
- Updated CI workflows to build and test the C API

- Added Python C extension module `sista._sista` loaded in the `sista` Python module
    - Added `python/` directory with the C extension source code and `setup.py` for building and installing the Python module
    - Updated CI workflows to build and test the Python module

- Updated `Makefile` for hardcoding the rpath of the MacOS shared library to avoid issues with `DYLD_LIBRARY_PATH`
- Updated `Makefile` to reflect the new filenames and ensure correct compilation and linking

- Added files for `.deb` packaging under `packageroot`

- Testing on memory safety with `valgrind`, detected no memory leaks or invalid accesses

- Constructor and destructor of `sista::Cursor` only hide/show the cursor, but do not alter the ANSI settings nor clear the screen anymore

## v`2.2.1`

Patch release.

- Adapted `Makefile` for MacOS install

## v`2.2.0`

Minor release.

- `Sista` now available as a shared library on Windows via `MinGW`, `MSYS2` or alternative toolchains

The previous state was that `Sista` was only available in source format on Windows, but now it can be installed on the system as a shared library.

MSVC support is not available, and it won't for the foreseeable future unless there is a demand for it and a volunteer to test it.

## v`2.1.2`

- Added new demo `shared-test-static` to test static linking against the `Sista` library
- Updated `demo/Makefile` to include the new demo and to build it correctly
- Updated Makefile CI workflow to build all demos, including the new `shared-test-static` demo

## v`2.1.1`

- Fixed the `Makefile` to correctly build the demos without the need for `Sista` to be installed
- Added documentation in the `demo/README.md` file
- Updated and refreshed the documentation on ReadTheDocs, under `docs/`

## v`2.1.0`

Minor release.

- Changed path of the `libSista.so` shared library from `{PREFIX}/lib64/libSista.so` to `{PREFIX}/lib/libSista.so` for `ld` to find it correctly on most systems
- Added `uninstall` target to the `Makefile` to remove the installed files
- Added `demo/shared-test.cpp` and related `Makefile` target to test the shared library installation

## v`2.0.0`

Major release.

- Sista now available as a shared library, `libSista.so`, which can be installed in the system library path

## v`1.1.8`

Bug fix release.

- Fixed `sista::Coordinates` operator overload `<` to be a strict weak ordering relation

```diff
bool Coordinates::operator<(const Coordinates& other) const {
-    return (y + x) < (other.y + other.x);
+    if (y != other.y)
+        return y < other.y;
+    return x < other.x;
}
```

This change is necessary to ensure that constructs such as `std::set<sista::Coordinates>` work correctly, as it requires a strict weak ordering relation.

We don't plan to implement an hash function for `sista::Coordinates` at the moment as the direct comparison is more efficient and straightforward for the intended use cases.

## v`1.1.7`

- Allow `ANSI::Settings` to be initialized with mixed `ForegroundColor` and `RGBColor` or `RGBColor` and `BackgroundColor`

This change has the purpose to allow more flexibility, especially when using a custom foreground color with a coded background color.

```c++
ANSI::Settings settings = {
    ANSI::RGBColor(42, 42, 42),
    ANSI::BackgroundColor::B_BLACK,
    ANSI::Attribute::BRIGHT
};
```

## v`1.1.6`

- Added `<` comparison operator to `sista::Coordinates`

The purpose is to allow `std::set<sista::Coordinates>`. It is based solely on the distance from the origin.

```c++
bool Coordinates::operator<(const Coordinates& other) const {
    return (y + x) < (other.y + other.x);
}
```

## v`1.1.5`

- Added `RGBColor` and support for it in the `ANSI::Settings` struct

It is now possible to initialize `ANSI::Settings` instances as follows. Even if in general using the constructor could be a bless for backwards compatibility of your code.

```c++
ANSI::Settings settings = {
    ANSI::RGBColor(42, 42, 42),
    ANSI::RGBColor(69, 69, 69),
    ANSI::Attribute::BRIGHT
};
```

The library does not enforce consistency across foreground and background indications, as in one of the two can be an `RGBColor` and the other one a `ForegroundColor`, for instance.

This change is backwards compatible, so the `ForegroundColor`/`BackgroundColor` based initialization is still functional and will always be supported.

## v`1.1.4`

- Added `sista::Field::removePawn(sista::Coordinates&)` to remove a pawn from the field by coordinates without the need of a pointer to the pawn

```c++
void Field::removePawn(Coordinates& coordinates) { // Remove a pawn from the matrix
    pawns[coordinates.y][coordinates.x] = nullptr; // Set the pawn to nullptr
}
```

- Added `sista::Field::erasePawn(sista::Coordinates&)` to erase a pawn from the field by coordinates without the need of a pointer to the pawn

```c++
void Field::erasePawn(Coordinates& coordinates) { // Erase a pawn from the matrix
    removePawn(coordinates); // Remove the pawn from the matrix
    cursor.set(coordinates); // Set the cursor to the pawn's coordinates
    ANSI::reset(); // Reset the settings for that cell
    std::cout << ' '; // Print a space to clear the cell
}
```

## v`1.1.3`

- Added `sista::Field::rePrintPawn()`
- Added operator for scalar multiplication for `sista::Coordinates` struct

```c++
void Field::rePrintPawn(Pawn* pawn) { // Print a pawn
    cursor.set(pawn->getCoordinates()); // Set the cursor to the pawn's coordinates
    pawn->print(); // Print the pawn
}
```

```c++
Coordinates operator*(const unsigned short int) const;
```

## v`1.1.2`

- Added more operators for `sista::Coordinates` struct

```c++
Coordinates operator-(const Coordinates&) const;
Coordinates operator+=(const Coordinates&);
Coordinates operator-=(const Coordinates&);
```

## v`1.1.1`

- Added `sista::Field::erasePawn()` to remove and erase Pawn from the screen

```c++
void Field::erasePawn(Pawn* pawn) { // Erase a pawn from the matrix
    removePawn(pawn); // Remove the pawn from the matrix
    cursor.set(pawn->getCoordinates()); // Set the cursor to the pawn's coordinates
    ANSI::reset(); // Reset the settings for that cell
    std::cout << ' '; // Print a space to clear the cell
}
```

## v`1.0.0`

- Divided Sista in `.hpp` headers and `.cpp` sources

This should make it possible to use Sista in projects with multiple source files.

## v`0.9.4`

- Added `sista::Field::addPrintPawn()` to add and print Pawn without reprint

```c++
void addPrintPawn(Pawn* pawn) { // Add a pawn to the matrix and print it
    addPawn(pawn); // Add the pawn to the matrix
    this->cursor.set(pawn->getCoordinates()); // Set the cursor to the pawn's coordinates
    pawn->print(); // Print the pawn
}
```

## v`0.9.3`

- Fixed `sista::Field::reset()` which was resizing the field to 0x0

```c++
void reset() {
    for (auto& row: pawns) { // For each row
        for (auto& pawn: row) {
            if (pawn != nullptr) // If the pawn is not nullptr
                delete pawn; // Delete the pawn
            pawn = nullptr; // Set the pawn to nullptr
        }
    }        
}
```

## v`0.9.2`

- Added ScreenMode management

```c++
enum ScreenMode {
    MONOCROME_TEXT_40_25 = 0,
    COLOR_TEXT_40_25 = 1,
    MONOCROME_TEXT_80_25 = 2,
    COLOR_TEXT_80_25 = 3,
    FOUR_COLORS_GRAPHICS_320_200 = 4,
    MONOCROME_GRAPHICS_320_200 = 5,
    MONOCROME_GRAPHICS_640_200 = 6,
    LINE_WRAPPING = 7,
    COLOR_GRAPHICS_320_200 = 13,
    COLOR_16_COLORS_GRAPHICS_640_200 = 14,
    MONOCROME_2_COLORS_GRAPHICS_640_350 = 15,
    COLOR_16_COLORS_GRAPHICS_640_350 = 16,
    MONOCROME_2_COLORS_GRAPHICS_640_480 = 17,
    COLOR_16_COLORS_GRAPHICS_640_480 = 18,
    COLOR_256_COLORS_GRAPHICS_320_200 = 19
};

void setScreenMode(ScreenMode mode) {
    std::cout << CSI << '=' << mode << 'h';
}
void unsetScreenMode(ScreenMode mode) {
    std::cout << CSI << '=' << mode << 'l';
}
```

- Added resetter for `sista::Field` instances, to empty the field from the `sista::Pawn`s

```c++
void reset() {
    for (auto& row: pawns) // For each row
        for (auto& pawn: row) // For each pawn
            if (pawn != nullptr) // If the pawn is not nullptr
                delete pawn; // Delete the pawn
    pawns.clear(); // Clear the pawns
}
```

## v`0.9.0`

- Added 256 color support

```c++
void setForegroundColor(unsigned short int color) {
    std::cout << CSI << "38;5;" << color << "m";
}
void setBackgroundColor(unsigned short int color) {
    std::cout << CSI << "48;5;" << color << "m";
}
```

- Added 24-biit RGB color support

```c++
void setForegroundColor(unsigned short int red, unsigned short int green, unsigned short int blue) {
    std::cout << CSI << "38;2;" << red << ";" << green << ";" << blue << "m";
}
void setBackgroundColor(unsigned short int red, unsigned short int green, unsigned short int blue) {
    std::cout << CSI << "48;2;" << red << ";" << green << ";" << blue << "m";
}
```

## v`0.8.0`

- Added [more ANSI cursor commands](https://github.com/FLAK-ZOSO/Sista/blob/3f861a7e1f61609f4d8f9cf03aaaf3c056db1278/include/sista/cursor.hpp#L70-L89)

```c++
enum EraseScreen {
    FROM_CURSOR_TO_END = 0,
    FROM_CURSOR_TO_BEGINNING = 1,
    ENTIRE_SCREEN = 2,
    ERASE_SAVED_LINES = 3,
};
enum EraseLine {
    LINE_FROM_CURSOR_TO_END = 0,
    LINE_FROM_CURSOR_TO_BEGINNING = 1,
    ENTIRE_LINE = 2,
};
enum MoveCursor {
    UP = (int)'A',
    DOWN = (int)'B',
    RIGHT = (int)'C',
    LEFT = (int)'D',
    BEGINNING_OF_NEXT_LINE = (int)'E',
    BEGINNING_OF_PREVIOUS_LINE = (int)'F',
    HORIZONTAL_ABSOLUTE = (int)'G'
};
enum MoveCursorDEC {
    SAVE_CURSOR_POSITION = 7,
    RESTORE_CURSOR_POSITION = 8
};
enum MoveCursorSCO {
    SCO_SAVE_CURSOR_POSITION = (int)'s',
    SCO_RESTORE_CURSOR_POSITION = (int)'u'
};

// In Cursor struct
void eraseScreen(EraseScreen eraseScreen_) {
    std::cout << CSI << eraseScreen_ << "J";
}
void eraseLine(EraseLine eraseLine_, bool moveCursor=true) {
    std::cout << CSI << eraseLine_ << "K";
    if (moveCursor) {
        this->set(this->y, 0);
        std::cout << '\r';
    }
}

void move(MoveCursor moveCursor_, unsigned short int n=1) {
    std::cout << CSI << n << (char)moveCursor_;
}
void move(MoveCursorDEC moveCursorDEC_) {
    std::cout << ESC << ' ' << moveCursorDEC_;
}
void move(MoveCursorSCO moveCursorSCO_) {
    std::cout << ESC << ' ' << moveCursorSCO_;
}
```

- Added `ESC` constant to `ANSI-Settings.hpp`

## v`0.7.1`

- Added [condition](https://github.com/FLAK-ZOSO/Sista/blob/main/include/sista/ANSI-Settings.hpp#L57-L60) over the attribute reset function

```c++
void resetAttribute(Attribute attribute) {
    if (attribute == Attribute::BRIGHT) {
        std::cout << CSI << attribute + 21 << "m";
        return;
    }
    std::cout << CSI << attribute + 20 << "m";
}
```

I added the if statement to check if the attribute is `BRIGHT` or not, because the `BRIGHT` reset code is `+21` (from set code) and the rest are `+20`.

## v`0.1.0`

This is the first version of `Sista` and it is still in development.
