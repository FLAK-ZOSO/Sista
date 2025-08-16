=====
``Sista``
=====

``Sista`` is a *lightweight* and *easy-to-use* *object-oriented* library for handling terminal graphics in ``C++``.

``Sista`` provides a set of classes and functions to make terminal games in ``C++`` easier, thus preventing developers from having to reinvent the wheel every time they want to make a terminal game.

``Download``
-------------

To install Sista, simply download the latest release from `GitHub <https://github.com/FLAK-ZOSO/Sista/releases>`_.
Extract the contents of the archive to your project's source directory.

An easier approach can be to directly clone the repository into your project's directory.

.. code-block:: bash

    git clone https://github.com/FLAK-ZOSO/Sista

``Usage``
-------------

The way you use Sista depends on how you want to include it in your project. There are two main ways to use Sista:

1. As a header-only library
2. As a shared library

In the first case, you will include the Sista headers in your project and compile the source files along with your project.
In the second case, you will install Sista as a shared library and link against it when compiling your project.

As header only library
-----------------

To use Sista, simply include the ``"sista.hpp"`` header in your project's source files. This is the inclusion method for versions before v`2.0.0`.

.. code-block:: cpp

    #include "include/sista/sista.hpp"


The ``"sista.hpp"`` header includes all of the other headers in the ``"include/sista/"`` directory, so you don't have to include them individually.
However, you will have to include them in the compilation process as shown here.

.. code-block:: bash

    IMPLEMENTATIONS = include/sista/ANSI-Settings.cpp include/sista/border.cpp include/sista/coordinates.cpp include/sista/cursor.cpp include/sista/field.cpp include/sista/pawn.cpp

    all: objects file clean

    objects:
        g++ -std=c++17 -Wall -g -c $(IMPLEMENTATIONS)

    file: objects
        g++ -std=c++17 -Wall -g -c sista.cpp
        g++ -std=c++17 -Wall -g -o sista sista.o ANSI-Settings.o border.o coordinates.o cursor.o pawn.o field.o

    clean:
        rm -f *.o

This assumes that you have the ``include/sista/`` directory in your project's source directory, and that ``sista.cpp`` is the only file of your project that uses Sista.
For more complex projects, you can use a build system like `CMake <https://cmake.org/>`_ or `Make <https://www.gnu.org/software/make/>`_ to manage the compilation process.

You can likely find a good example of a Makefile for a statically linked from source Sista project at `Inävjaga <https://github.com/FLAK-ZOSO/Inavjaga/blob/main/Makefile>`_.

As a shared library
-----------------

To use Sista as a shared library, you will need to install it in your system library path. This is the preferred inclusion method in Linux for versions v`2.0.0` and later.

To install Sista, you can use the provided Makefile in the repository. Simply run the following command in your terminal with administrative privileges:

.. code-block:: bash

    sudo make install

After installing Sista, you can include it in your project by adding the following line to your source files:

.. code-block:: cpp

    #include <sista/sista.hpp>

You will also need to link against the Sista library when compiling your project. You can do this by adding the following flags to your compilation command:

.. code-block:: bash

    g++ -std=c++17 -o sista sista.cpp -lSista

This assumes that you have installed Sista in the default system library path, which is `/usr/local/lib` for libraries and `/usr/local/include/sista` for headers, and that `sista.cpp` is the only file of your project that uses Sista.
For more complex projects, you can use a build system like `CMake <https://cmake.org/>`_ or `Make <https://www.gnu.org/software/make/>`_ to manage the compilation process.

You can verify that Sista is installed correctly by running the following command in your terminal:

.. code-block:: bash

    ldconfig -p | grep libSista

If Sista is installed correctly, you should see an output similar to this:

.. code-block:: text

    libSista.so (libc6,x86-64) => /usr/local/lib/libSista.so

If you see this output, you can now use Sista in your projects as a shared library as described above.

You can also link statically against Sista by using the following command:

.. code-block:: bash

    g++ -std=c++17 -o sista sista.cpp -static -lSista

This will create a statically linked executable that includes the Sista library, which can be useful if you want to distribute your application without requiring users to install Sista separately.

If you need to uninstall Sista, you can run the following command in your terminal with administrative privileges:

.. code-block:: bash

    sudo make uninstall

``Documentation``
--------------

Most of the documentation can be found here on Read the Docs: `Sista Documentation <https://sista.readthedocs.io/en/latest/>`_.

- `Sista reference <sista.html>`_ - library documentation
- `Introduction <intro.html>`_ - documented example

Some additional documentation for Sista can be found in the `Release Notes <https://github.com/FLAK-ZOSO/Sista/blob/main/ReleaseNotes.md>`_ on GitHub.

``Introduction``
----------------

A simple example of how to use Sista to make a terminal animation is provided by `sista.cpp <https://github.com/FLAK-ZOSO/Sista/blob/main/sista.cpp>`_.

A more detailed explaination of the example can be found in the `intro <intro.html>`_.

``Demos``
----------------

You can find some demos of Sista in the `demo <https://github.com/FLAK-ZOSO/Sista/blob/main/demo>`_ directory of the repository.

These demos showcase various features of Sista. They are minimal examples and, unlike the `sista.cpp` example, they do not provide a complete walkthrough of the library.

``Derived works``
----------------

Here are some of the most relevant works based on Sista, which you can use as a base for your project or as examples to better understand the syntax coming with the library.

-  `Inomhus <https://github.com/FLAK-ZOSO/Inomhus>`_ - *Bättre att stanna inomhus* (better be in the house) - a survival videogame
-  `Starklag <https://github.com/Lioydiano/Starklag>`_ - *den starkastes lag* (the law of the strongest) - a partial evolution simulator
-  `Dödas <https://github.com/Lioydiano/Dodas>`__ - *de dödas angrepp* (attack of the dead) - a survival speedrun videogame
-  `Dune <https://github.com/Lioydiano/Dune>`__ - a survival videogame inspired by Dune
-  `Inävjaga <https://github.com/FLAK-ZOSO/Inavjaga>`__ - *Inälvor jagade* (intestin hunt) - a survival videogame with hordes of enemies