``Intro``
====================

The purpose of this document is to provide a quick example of how to use the ``Sista`` library.

I will use this `sista.cpp <https://github.com/FLAK-ZOSO/Sista/blob/main/sista.cpp>`_ file as the example and I will provide a walkthrough.

``Installation``
--------------------

To use the ``Sista`` library, you can either include it as a header-only library or install it as a shared library. In the following example we illustrate the latter method.

.. code-block:: bash

    git clone https://github.com/FLAK-ZOSO/Sista
    cd Sista
    sudo make install

This will install the ``Sista`` library in your system library path, allowing you to link against it when compiling your project.

Since v2.2.0, Sista is available as a shared library on Windows using MinGW. To install it, you can use the following commands in MinGW or MSYS2:

.. code-block:: bash

    git clone https://github.com/FLAK-ZOSO/Sista
    cd Sista
    # Make sure to run this in an elevated shell (as administrator) since 'sudo' is not available in MinGW/MSYS2
    make install

If you want to use it as a header-only library, you can simply copy the ``include/sista/`` directory to your project source directory.

``Include``
--------------------

The first thing you need to do is include the ``Sista`` library. The header file you need to include is ``sista.hpp``.

If you installed the library as a shared library, you can include it like this:

.. code-block:: cpp

    #include <sista/sista.hpp>

Otherwise, if you are using it as a header-only library, you can include it like this:

.. code-block:: cpp

    #include "include/sista/sista.hpp"

Provided that you have the ``include/sista/`` directory in your project's source directory.

``Namespace``
--------------------

If you want you can use the ``sista`` namespace [#]_.

.. code-block:: cpp

    using namespace sista;

``Input/Output``
--------------------

The next thing the program does is to unsync the C++ standard input/output streams from the C standard streams.

.. code-block:: cpp

    std::ios_base::sync_with_stdio(false);

This line will make I/O faster since we only use C++ standard input/output. You can read more about it `on Stack Overflow <https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull>`_.

.. code-block:: cpp

    ANSI::reset(); // Reset the settings

This line of code will reset the ANSI settings of the terminal.

.. code-block:: cpp

    std::cout << HIDE_CURSOR;

This line of code will hide the cursor to reduce that noisy flickering.

ℹ️ - You don't need to do this explicitly since the ``sista::Field`` class includes a private ``sista::Cursor`` object that will hide the cursor when the constructor is called.

.. code-block:: cpp

    sista::clearScreen();

The ``clearScreen()`` [#]_ function will clear the screen and the scrollback buffer, and move the cursor to the top left corner.

ℹ️ - You don't need to do this explicitly since the ``sista::Field`` class includes a private ``sista::Cursor`` object that will call ``sista::clearScreen()``.

``Pawn``
--------------------

The next thing to do is to create a ``std::vector<sista::Pawn*>`` object as a list of the Pawns.

.. code-block:: cpp

    std::vector<sista::Pawn*> pawns;

The ``Pawn`` is allocated on the heap, so you need to use the ``new`` keyword to create one.

.. code-block:: cpp

    pawns = {
        new sista::Pawn(
            'X', sista::Coordinates(0, 0),
            ANSI::Settings(
                ANSI::ForegroundColor::F_RED,
                ANSI::BackgroundColor::B_BLACK,
                ANSI::Attribute::BRIGHT
            )
        ) // You can add more pawns here
    };

This line of code will add a ``Pawn`` object with the following properties:

- ``Character``: ``'X'``
- ``Coordinates``: ``0, 0``
- ``ANSI Settings``: ``Foreground Color``: ``Red``, ``Background Color``: ``Black``, ``Attribute``: ``Bright``

``Border``
--------------------

The next thing to do is to create a ``Border`` object.

.. code-block:: cpp

    sista::Border border(
        ' ', ANSI::Settings(
            ANSI::ForegroundColor::F_BLACK,
            ANSI::BackgroundColor::B_WHITE,
            ANSI::Attribute::BRIGHT
        )
    );

The ``Border`` is allocated on the stack, so you don't need to use the ``new`` keyword to create it.

I do so because I don't need to use the ``Border`` object outside of the ``main()`` function.

This line of code will create a ``Border`` object with the following properties:

- ``Character``: ``' '`` (Space)
- ``ANSI Settings``: ``Foreground Color``: ``Black``, ``Background Color``: ``White``, ``Attribute``: ``Bright``

``Field``
--------------------

The next thing to do is to create a ``Field`` object. In this case, I will use the ``sista::SwappableField`` class, which is a subclass of the ``sista::Field`` class that allows you to swap pawns in case of apparent collisions.

.. code-block:: cpp

    sista::SwappableField field(TEST_SIZE, TEST_SIZE);

In this case I am creating a ``sista::SwappableField`` object with the following - in order - properties:

- ``Width``: ``50``
- ``Height``: ``50``

Now that we have created the ``Field`` object, we can add the ``Pawn*`` to it.

.. code-block:: cpp

    for (auto pawn : pawns)
        field.addPawn(pawn);

This line of code will add the ``pawns`` to the ``Field`` object at the ``pawn->coordinates`` coordinates.

.. code-block:: cpp

    std::vector<sista::Coordinates> coords(pawns.size());

This line of code will create a ``std::vector<sista::Coordinates>`` object with the same size as the ``pawns`` object, to precalculate the coordinates and then assign them.

``Main Loop``
--------------------

The next thing to do is to create the main loop to test the ``SwappableField`` object and the ``Pawn`` movement.

.. code-block:: cpp

    field.print(border);

First of all, we need to print the ``Field`` object with the ``Border`` object.

.. code-block:: cpp

    for (int i=0; i<TEST_SIZE*TEST_SIZE; i++) {
        coords[0] = field.movingByCoordinates(pawns[0], 1, 1, PACMAN_EFFECT);
        coords[1] = field.movingByCoordinates(pawns[1], -1, -1, PACMAN_EFFECT);
        coords[2] = field.movingByCoordinates(pawns[2], -1, 1, PACMAN_EFFECT);
        coords[3] = field.movingByCoordinates(pawns[3], 1, -1, PACMAN_EFFECT);
        coords[4] = field.movingByCoordinates(pawns[4], 1, 0, PACMAN_EFFECT);
        coords[5] = field.movingByCoordinates(pawns[5], 0, 1, PACMAN_EFFECT);
        try {
            for (int k=0; k<(int)pawns.size(); k++) {
                field.movePawn(pawns[k], coords[k]);
            }
        } catch (const std::invalid_argument& e) {
            for (int k=0; k<(int)pawns.size(); k++) {
                field.addPawnToSwap(pawns[k], coords[k]);
            }
            field.applySwaps();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << std::flush;
    }

Since now we'll never going to re-print the ``Field`` object, we'll edit only the needed characters in the ``stdout`` stream. This is the strength of Sista: it allows you to edit only the characters that need to be changed, instead of re-printing the whole field.

In this loop, we are moving the pawns in different directions using the ``movingByCoordinates()`` method of the ``Field`` object, that doesn't actually move the ``Pawn`` but rather calculates its future position. The coordinates are stored in the ``coords`` vector.

Analyzing the code, we can see that we are moving the pawns in the following directions:

- Pawn 0: Down-Right (1, 1)
- Pawn 1: Up-Left (-1, -1)
- Pawn 2: Up-Right (-1, 1)
- Pawn 3: Down-Left (1, -1)
- Pawn 4: Right (1, 0)
- Pawn 5: Down (0, 1)

If the movement is valid, we will move the pawn to the new coordinates using the ``movePawn()`` method.

If the movement is not valid, we will add the pawn to the swap list using the ``addPawnToSwap()`` method, and then we will apply the swaps using the ``applySwaps()`` method. This is useful when the pawn is trying to move to a position that is already occupied by another pawn, but that other pawn is moving out of the way at the same time.

After applying all the movements, we'll swap the characters in the ``stdout`` stream, and then we'll flush the ``stdout`` stream.

``Compilation``
--------------------

To compile the ``sista.cpp`` file, you need to use the following commands...

.. code-block:: bash

    g++ -std=c++17 -Wall -g -c $(IMPLEMENTATIONS)
	g++ -std=c++17 -Wall -g -c sista.cpp
	g++ -std=c++17 -Wall -g -o sista sista.o ANSI-Settings.o border.o coordinates.o cursor.o pawn.o field.o
	rm -f *.o

...where ``$(IMPLEMENTATIONS)`` is the list of the ``Sista`` library implementation files.

.. code-block:: bash

    IMPLEMENTATIONS = include/sista/ANSI-Settings.cpp include/sista/border.cpp include/sista/coordinates.cpp include/sista/cursor.cpp include/sista/field.cpp include/sista/pawn.cpp

In case you have ``make`` installed, it's easier to directly use it in pair with the `Makefile <https://github.com/FLAK-ZOSO/Sista/blob/main/Makefile>`_.

.. code-block:: bash

    make

``Execution``
--------------------

.. code-block:: bash

    ./sista

On Windows it is slightly different, but it is assumed that whoever reaches this point in the documentation is aware of how to launch an executable from a command line interface.

``Notes``
====================

.. [#] In the example the namespace is always specified for clarity
.. [#] The ``clearScreen()`` function was OS-specific and only worked on ``Windows`` until ``v0.5.0`` when it became cross-platform