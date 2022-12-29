``Library``
================

``Sista`` as a library is a collection of the following headers:

- ``ANSI-Settings.hpp``: ANSI escape codes for terminal colors and styles
- ``border.hpp``: Border
- ``coordinates.hpp``: Coordinates manipulation
- ``cursor.hpp``: Cursor, clearScreen
- ``field.hpp``: Field
- ``pawn.hpp``: Pawn
- ``sista.hpp``: main header file, includes all the others

``ANSI-Settings.hpp``
================

This `header <https://github.com/FLAK-ZOSO/Sista/blob/main/include/sista/ANSI-Settings.hpp>`_ contains the following preprocessor constants:

+--------------+--------------+-----------------------------+
| Constant     | Value        | Description                 |
+==============+==============+=============================+
| CSI          | "\x1b["      | Command Sequence Introducer |
+--------------+--------------+-----------------------------+
| CLS          | "\x1b[2J"    | CLean Screen                |
+--------------+--------------+-----------------------------+
| SSB          | "\x1b[3J"    | Scroll Screen Buffer        |
+--------------+--------------+-----------------------------+
| TL           | "\x1b[H"     | Top Left                    |
+--------------+--------------+-----------------------------+
| HIDE_CURSOR  | "\x1b[?25l"  | Hide Cursor                 |
+--------------+--------------+-----------------------------+
| SHOW_CURSOR  | "\x1b[?25h"  | Show Cursor                 |
+--------------+--------------+-----------------------------+

This header also contains the following functions:

.. code-block:: cpp

    void setForegroundColor(ForegroundColor);
    void setBackgroundColor(BackgroundColor);
    void setAttribute(Attribute);
    void reset();

This header also contains the following enums based on the `ANSI escape codes <https://en.wikipedia.org/wiki/ANSI_escape_code>`_

.. code-block:: cpp

    enum ForegroundColor : int;
    enum BackgroundColor : int;
    enum Attribute : int;

This header also contains the following struct used to represent the style of a char in the terminal:

.. code-block:: cpp

    struct Settings {
        ForegroundColor foregroundColor;
        BackgroundColor backgroundColor;
        Attribute attribute;
    };