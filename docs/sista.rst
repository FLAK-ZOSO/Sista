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


⚠️ Warning
================

From this point all the elements of the library are part of the ``sista`` namespace.

``border.hpp``
================

This `header <https://github.com/FLAK-ZOSO/Sista/blob/main/include/sista/border.hpp>`_ contains the following class used to represent the border of a field.

.. code-block:: cpp

    class Border {
    protected:
        char symbol; // Symbol of the Border
        ANSI::Settings settings; // settings of the Border style
    public:
        Border(char, ANSI::Settings);
        Border(char, ANSI::Settings&, bool);
        virtual void print(bool apply_settings=true);
    };

``coordinates.hpp``
================

This `header <https://github.com/FLAK-ZOSO/Sista/blob/main/include/sista/coordinates.hpp>`_ contains the following struct used to represent the coordinates of a Pawn.

.. code-block:: cpp

    struct Coordinates { // 2D coordinates
        unsigned short y; // y coordinate
        unsigned short x; // x coordinate

        Coordinates();
        Coordinates(unsigned short, unsigned short);
        Coordinates(Coord);

        bool operator==(const Coordinates&) const;
        bool operator!=(const Coordinates&) const;
        Coordinates operator+(const Coordinates&) const;
    };

This header also contains the following typedef used to represent the coordinates of a Pawn.

.. code-block:: cpp

    typedef std::pair<unsigned short, unsigned short> Coord;

The library uses the ``Coordinate`` struct more often than the ``Coord`` typedef, but almost all the functions of the library can use both.

``cursor.hpp``
================

This `header <https://github.com/FLAK-ZOSO/Sista/blob/main/include/sista/coordinates.hpp>`_ contains the following constants:

+--------------+--------------+-----------------------------+
| Constant     | Value        | Description                 |
+==============+==============+=============================+
| CHA          | 'H'          | Cursor Horizontal Absolute  |
+--------------+--------------+-----------------------------+
| VPA          | 'd'          | Vertical Position Absolute  |
+--------------+--------------+-----------------------------+

This header also contains the following function.

.. code-block:: cpp

    void clearScreen();

This header also contains the following struct used to represent the cursor of the terminal.

.. code-block:: cpp

    struct Cursor {
        unsigned short int x;
        unsigned short int y;

        Cursor();
        ~Cursor();

        void set(unsigned short int, unsigned short int);
        void set(sista::Coordinates);
    };

The coordinates are 0-based like in the ``Coordinates`` struct, they will be adapted to the {3, 2}-based coordinates of the terminal when printed.