# `Sista` demo

This directory contains a set of demo programs that showcase the features of the `Sista` library. Each demo is a standalone program that demonstrates a specific aspect of the library.

## Demos

- `header-test`: A simple program that tests the header-only usage of `Sista`
- `shared-test`: A program that tests the shared library usage of `Sista` for dynamic linking
- `shared-test-static`: A program that tests the shared library usage of `Sista` for static linking
- `colors24-bit`: showcases the 24-bit color support
- `colors256`: showcases the 256-color support
- `conflictTest`: tests the conflict resolution features of `sista::SwappableField`
- `resetAttribute`: tests the `sista::resetAttribute` function
- `screen-mode`: showcases the screen modes being changed
- `swapTest`: two pawns swapping places in a `sista::SwappableField`
- `verticalTest`: tests the vertical pacman effect

Consider that some demos are made to verify the terminal's support for certain features, and not all of them will always work as expected on every terminal. The demos are designed to be run in a terminal that supports ANSI escape codes and the features being tested, that often go beyond the standard ANSI capabilities.

## Building the demos

These demos do not require the installation of `Sista` to build. You can compile them directly using `g++`. 

```bash
g++ -std=c++17 -Wall -Wno-narrowing -Wno-sign-compare -g -c header-test.cpp
g++ -std=c++17 -Wall -g -o header-test header-test.o ANSI-Settings.o border.o coordinates.o cursor.o field.o pawn.o
```

You can replace `header-test.cpp` with any of the other demo files to compile them. The `Makefile` in this directory provides a convenient way to build all demos at once. It does not however, for convenience reasons, include the tests that require the shared library to be installed.

```bash
make
# Equivalent to running: make all
```

All demos are compiled with debugging symbols enabled, which allows you to run them in a debugger if needed.

To clean up the compiled objects and executables, you can run:

```bash
make clean
```

This will remove all object files and executables created during the build process, keeping the directory clean.

### `shared-test`

The `shared-test` demo is built similarly, but it links against the `Sista` shared library. Ensure that the `Sista` library is available in your library path when compiling this demo.

```bash
# Go to the main Sista/ directory, root of this repository
sudo make install
```

This will install the `Sista` library, making it available for linking with the demos.

Then you can compile the `shared-test` demo:

```bash
# Back in the Sista/demo directory
make shared-test
```

This will create the `shared-test` executable, which you can run to test the installation of `libSista`.

```bash
./shared-test
```

You can also verify if you can link statically against the library.

```bash
# Back in the Sista/demo directory
make shared-test-static
```

This will create the `shared-test-static` executable, which you can [also after uninstalling the library](https://stackoverflow.com/questions/311882/what-do-statically-linked-and-dynamically-linked-mean).

### Uninstalling the library

If you want to remove the installed files, you can run:

```bash
sudo make uninstall
```

## Running the demos

After building the demos, you can run them directly from the terminal. For example:

```bash
./header-test
```

This will execute the `header-test` demo, which will display the output of the test cases defined in the program.

![24 bit colors demo](../docs/img/colors24-bit.png "24-bit colors demo")

Above is a screenshot of the `colors24-bit` demo, which showcases the 24-bit color support in `Sista`. Each demo has its own unique output and functionality, even tho most are ugly.

## Learning from the demos

The `demo/` files were initially intended to be used for development and testing purposes. However, they represent a valuable resource for learning how to use the `Sista` library effectively.

You can look at the source code of each demo to understand how to use the `Sista` library effectively. Each demo is designed to highlight specific features and functionalities of the library, making it easier to learn and apply them in your own projects. Don't be afraid to look at the demos' C++ source code and experiment with them.

## Contributing

If you would like to contribute to the `Sista` demos, feel free to submit a pull request. We welcome contributions that improve the demos, add new features, or fix bugs.
