=====
``Sista``
=====

``Sista`` is a *lightweight* and *easy-to-use* *object-oriented* library for handling terminal graphics in ``C++``.

``Sista`` provides a set of classes and functions to make terminal games in ``C++`` easier, thus preventing developers from having to reinvent the wheel every time they want to make a terminal game.

``Installation``
-------------

To install Sista, simply download the latest release from `GitHub <https://github.com/FLAK-ZOSO/Sista/releases>`_.
Extract the contents of the archive to your project's source directory.

An easier approach can be to directly clone the repository into your project's directory.

.. code-block:: bash

    git clone https://github.com/FLAK-ZOSO/Sista

``Usage``
-------------

To use Sista, simply include the ``"sista.hpp"`` header in your project's source files.

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

``Derived works``
----------------

Here are some of the most relevant works based on Sista, which you can use as a base for your project or as examples to better understand the syntax coming with the library.

-  `Inomhus <https://github.com/FLAK-ZOSO/Inomhus>`_ - *Bättre att stanna inomhus* (better be in the house) - a survival videogame
-  `Starklag <https://github.com/Lioydiano/Starklag>`_ - *den starkastes lag* (the law of the strongest) - a partial evolution simulator
-  `Dödas <https://github.com/Lioydiano/Dodas>`__ - *de dödas angrepp* (attack of the dead) - a survival speedrun videogame
-  `Dune <https://github.com/Lioydiano/Dune>`__ - a survival videogame inspired by Dune
-  `Inavjaga <https://github.com/FLAK-ZOSO/Inavjaga>`__ - *Inälvor jagade* (intestin hunt) - a survival videogame with hordes of enemies