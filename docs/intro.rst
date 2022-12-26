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

The next thing you need to do is to use the ``sista`` namespace [namespace]_.

.. code-block:: cpp

    using namespace sista;


``Input/Output``
--------------------

The next thing to do is to set the input and output streams.

.. code-block:: cpp

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

This two lines of code will make ``I/O`` faster.

.. code-block:: cpp

    ANSI::reset(); // Reset the settings

This line of code will reset the ANSI settings of the terminal [1]_.

.. code-block:: cpp

    std::cout << HIDE_CURSOR;

This line of code will hide the cursor [2]_ to reduce that noisy flickering.

.. code-block:: cpp

    clearScreen();

The ``clearScreen()`` [3]_ function will clear the screen and the buffer [4]_, and move the cursor to the top left corner.

``Pawn``
--------------------

The next thing to do is to create a ``Pawn`` object.

.. code-block:: cpp

    sista::Pawn* pawn = new sista::Pawn(
        'X', sista::Coordinates(0, 0),
        ANSI::Settings(
            ANSI::ForegroundColor::F_RED,
            ANSI::BackgroundColor::B_BLACK,
            ANSI::Attribute::BRIGHT
        )
    );

The ``Pawn`` is allocated on the heap, so you need to use the ``new`` keyword to create it.

Than ``pawn`` is a pointer to the ``Pawn`` object.

This line of code will create a ``Pawn`` object with the following properties:

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

The next thing to do is to create a ``Field`` object [TEST_SIZE]_.

.. code-block:: cpp

    sista::SwappableField field(TEST_SIZE, TEST_SIZE);

In this case I am creating a ``sista::SwappableField`` [5]_ object with the following properties:

- ``Width``: ``50``
- ``Height``: ``50``

Now that we have created the ``Field`` object, we can add the ``Pawn*``s to it.

.. code-block:: cpp

    field.addPawn(pawn);

This line of code will add the ``pawn`` to the ``Field`` object at the ``pawn->coordinates`` coordinates.

``Main Loop``
--------------------

The next thing to do is to create the main loop to test the ``SwappableField`` object and the ``Pawn``s movement.

.. code-block:: cpp

    for (int i=0; i<TEST_SIZE; i++) {
        for (int j=0; j<TEST_SIZE; j++) {
            coords = field.movingByCoordinates(pawn, 0, 1, MATRIX_EFFECT); // Calculate the new coordinates
            field.addPawnToSwap(pawn, coords); // Add the pawn to the swap list
            coords = field.movingByCoordinates(pawn2, 0, -1, MATRIX_EFFECT);
            field.addPawnToSwap(pawn2, coords);

            field.applySwaps(); // Apply the queued swaps

            std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Wait 20 milliseconds
            clearScreen(); // Clear the screen
            field.print(border); // Print the field with the border object
        }
    }

This is the main loop, it will move the ``Pawn``s ``TEST_SIZE*TEST_SIZE`` times across the field.


``Notes``
====================

.. [namespace] In the example I anyway specify the namespace despite the fact that I already used the ``using namespace sista;`` statement. This is because I want to make it clear that I am using the ``sista`` namespace.
.. [1] The ``ANSI::reset`` function comes from the ``ANSI-Settings.hpp`` header.
.. [2] The ``HIDE_CURSOR`` preprocessor constant comes from the ``ANSI-Settings.hpp`` header.
.. [3] The ``clearScreen()`` function is OS-specific and only works on ``Windows``.
.. [4] The ``clearScreen()`` function comes from the ``clearScreen.hpp`` header.
.. [TEST_SIZE] The ``TEST_SIZE`` preprocessor constant was previously defined, and expands to ``50``.
.. [5] The ``sista::SwappableField`` class comes from the ``SwappableField.hpp`` header since ``v0.4.0`` and inherits from the ``sista::Field`` class.