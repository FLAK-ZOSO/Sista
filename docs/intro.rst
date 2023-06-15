``Intro``
====================

The purpose of this document is to provide a quick example of how to use the ``Sista`` library.

I will use the `sista.cpp <https://github.com/FLAK-ZOSO/Sista/blob/main/sista.cpp>`_ file as the example to explain.

``Include``
--------------------

The first thing you need to do is include the ``Sista`` library.

.. code-block:: cpp

    #include "include/sista/sista.hpp"


``Namespace``
--------------------

The next thing you should do is to use the ``sista`` namespace [#]_.

.. code-block:: cpp

    using namespace sista;


``Input/Output``
--------------------

The next thing to do is to set the input and output streams.

.. code-block:: cpp

    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);

This two lines of code will make ``I/O`` faster.

.. code-block:: cpp

    ANSI::reset(); // Reset the settings

This line of code will reset the ANSI settings of the terminal [#]_.

.. code-block:: cpp

    std::cout << HIDE_CURSOR;

This line of code will hide the cursor [#]_ to reduce that noisy flickering.

ℹ️ - You don't need to do this since the ``sista::Field`` class includes a private ``sista::Cursor`` object that will hide the cursor when the constructor is called.

.. code-block:: cpp

    sista::clearScreen();

The ``clearScreen()`` [#]_ function will clear the screen and the buffer [#]_, and move the cursor to the top left corner.

ℹ️ - You don't need to do this since the ``sista::Field`` class includes a private ``sista::Cursor`` object that will call ``sista::clearScreen()``.

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

The next thing to do is to create a ``Field`` object [#]_.

.. code-block:: cpp

    sista::SwappableField field(TEST_SIZE, TEST_SIZE);

In this case I am creating a ``sista::SwappableField`` [#]_ object with the following properties:

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

Since now we'll never going to re-print the ``Field`` object, we'll edit only the needed characters in the ``stdout`` stream.

After applying all the movements, we'll swap the characters in the ``stdout`` stream, and then we'll flush the ``stdout`` stream.

``Notes``
====================

.. [#] In the example I anyway specify the namespace despite the fact that I already used the ``using namespace sista;`` statement. This is because I want to make it clear that I am using the ``sista`` namespace.
.. [#] The ``ANSI::reset`` function comes from the ``ANSI-Settings.hpp`` header.
.. [#] The ``HIDE_CURSOR`` preprocessor constant comes from the ``ANSI-Settings.hpp`` header.
.. [#] The ``clearScreen()`` function was OS-specific and only worked on ``Windows`` until ``v0.5.0`` when it became cross-platform.
.. [#] The ``clearScreen()`` function comes from the ``cursor.hpp`` header.
.. [#] The ``TEST_SIZE`` preprocessor constant was previously defined, and expands to ``50``.
.. [#] The ``sista::SwappableField`` class comes from the ``SwappableField.hpp`` header since ``v0.4.0`` and inherits from the ``sista::Field`` class.