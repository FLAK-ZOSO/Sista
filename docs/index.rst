.. class:: center

    =====
    ``Sista``
    =====

.. image:: https://github.com/FLAK-ZOSO/Sista/blob/main/docs/img/OX.png?raw=true
    :alt: Sista Logo
    :width: 200px
    :align: center

``Sista`` is a *lightweight*, *fast*, and *easy-to-use* *OOP* library for making terminal games in ``C++``.

``Sista`` is a *header-only* library that provides a set of classes and functions to make it easier to create terminal games in ``C++``.

Inspired by their `Forsiktig <https://github.com/Lioydiano/Forsiktig>`_ 's `variables.hpp <https://github.com/Lioydiano/Forsiktig/blob/main/variables.hpp>`_ header, @FLAK-ZOSO decided to make a library to prevent others from having to reinvent the wheel every time they wanted to make a terminal game.

``OS Compatibility``
----------------------

Sista is fully compatible with ``Windows``.
It may work on any other OS which provides an ANSI-supporting Terminal.

The only thing that may not work is the ``clearScreen()`` function from ``"clearScreen.h"``, which uses the ``<Windows.h>`` header.

If you want to use this function, you will have to replace it with your own implementation.

**NOTE**: This function is not used by any of the classes in Sista, thanks to preprocessing guards.

.. code-block:: cpp

    #if (_WIN32 || _WIN64)
        #include "clearScreen.hpp" // clearScreen [Windows-specific]
    #endif

``Installation``
-------------

To install Sista, simply download the latest release from `GitHub <https://github.com/FLAK-ZOSO/Sista>`_.
Extract the contents of the archive to your project's source directory.

``Usage``
-------------

To use Sista, simply include the ``"sista.hpp"`` header in your project's source files.

.. code-block:: cpp

    #include "include/sista/sista.hpp"


The ``"sista.hpp"`` header includes all of the other headers in the ``"include/sista/"`` directory, so you don't have to include them individually.

``Documentation``
--------------

Some of the documentation for Sista can be found in the `Release Notes <ReleaseNotes.md>`_ and `Benchmarks <Benchmarks.md>`_ files.