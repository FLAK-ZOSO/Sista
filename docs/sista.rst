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

+-------------+-------------+-----------------------------+
| Constant    | Value       | Description                 |
+=============+=============+=============================+
| CSI         | "\x1b["     | Command Sequence Introducer |
+-------------+-------------+-----------------------------+
| ESC         | "\x1b"      | ESC                         |
+-------------+-------------+-----------------------------+
| CLS         | "\x1b[2J"   | CLean Screen                |
+-------------+-------------+-----------------------------+
| SSB         | "\x1b[3J"   | Scroll Screen Buffer        |
+-------------+-------------+-----------------------------+
| TL          | "\x1b[H"    | Top Left                    |
+-------------+-------------+-----------------------------+
| HIDE_CURSOR | "\x1b[?25l" | Hide Cursor                 |
+-------------+-------------+-----------------------------+
| SHOW_CURSOR | "\x1b[?25h" | Show Cursor                 |
+-------------+-------------+-----------------------------+

This header also contains the following functions:

.. code-block:: cpp

    void setForegroundColor(ForegroundColor);
    void setBackgroundColor(BackgroundColor);
    void setAttribute(Attribute);
    void resetAttribute(Attribute);
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

This header also contains the following enums based on the `ANSI escape codes <https://en.wikipedia.org/wiki/ANSI_escape_code>`_

.. code-block:: cpp

    enum EraseScreen : int;
    enum EraseLine : int;
    enum MoveCursor : int;
    enum MoveCursorDEC : int;
    enum MoveCursorSCO : int;

This header also contains the following struct used to represent the cursor of the terminal.

.. code-block:: cpp

    struct Cursor {
        unsigned short int x;
        unsigned short int y;

        Cursor();
        ~Cursor();

        void set(unsigned short int, unsigned short int);
        void set(sista::Coordinates);

        void eraseScreen(EraseScreen);
        void eraseLine(EraseLine);
        void move(MoveCursor, unsigned short int);
        void move(MoveCursorDEC);
        void move(MoveCursorSCO);
    };

The coordinates are 0-based like in the ``Coordinates`` struct, they will be adapted to the {3, 2}-based coordinates of the terminal when printed.

``field.hpp``
================

This `header <https://github.com/FLAK-ZOSO/Sista/blob/main/include/sista/field.hpp>`_ contains the following constants:

+---------------+--------------+-----------------------------+
| Constant      | Value        | Description                 |
+===============+==============+=============================+
| PACMAN_EFFECT | 0            | Pacman effect               |
+---------------+--------------+-----------------------------+
| MATRIX_EFFECT | 1            | Matrix effect               |
+---------------+--------------+-----------------------------+

This header also contains the following "abstract" class used to represent a field.

.. code-block:: cpp

    class Field {
    protected:
        std::vector<std::vector<Pawn*>> pawns; // Matrix of pawns
        Cursor cursor; // Cursor
        int width; // Width of the matrix
        int height; // Height of the matrix
    
    public:
        Field(int, int);
        ~Field();
    
        void clear();
        void print();
        void print(char);
        void print(Border&);
    
        virtual void addPawn(Pawn*);
        virtual void removePawn(Pawn*);
        Pawn* getPawn(Coordinates&);

        void movePawn(Pawn*, Coordinates&);
        void movePawnBy(Pawn*, Coordinates&);
        void movePawnBy(Pawn*, Coordinates&, bool);
        void movePawnFromTo(Coordinates&, Coordinates&);
    
        bool isOccupied(Coordinates&);
        bool isOutOfBounds(Coordinates&);
        bool isFree(Coordinates&);
        void validateCoordinates(Coordinates&);
    };

ℹ️ - All the methods with a ``Coordinates&`` argument can use a ``Coord`` typedef or two ``unsigned short`` instead.

When using a ``SwappableField``, the movement of a ``Pawn`` can be queued using a ``Path`` object.

.. code-block:: cpp

    struct Path { // Path struct - begin and end Coordinates of a path
        static int current_priority; // current_priority - priority of the current Path [counter]
        int priority; // priority - priority of the Path (used in operator<)
        Coordinates begin;
        Coordinates end;
        Pawn* pawn; // pawn - the pawn that is moving along the path

        Path(Coordinates, Coordinates, Pawn*);

        bool operator|(const Path& other) const;
        bool operator<(const Path& other) const;
    };

Then the ``SwappableField`` class can be used to represent a field with some useful function to handle cell-conflicts.

.. code-block:: cpp
    
    class SwappableField: public Field {
    private:
        std::vector<std::vector<short int>> pawnsCount;
        std::vector<Path> pawnsToSwap;
        Coord firstInvalidCell(std::vector<std::vector<short int>>&);
    
    public:
        SwappableField(int, int);
        ~SwappableField();
    
        void addPawn(Pawn*);
        void removePawn(Pawn*);
        void clearPawnsToSwap();

        Coordinates movingByCoordinates(Pawn*, unsigned short, unsigned short);
        Coordinates movingByCoordinates(Pawn*, unsigned short, unsigned short, bool);

        void addPawnToSwap(Pawn*, Coordinates&);
        void addPawnToSwap(Path&);
        void applySwaps();
        void swapTwoPawns(Coordinates&, Coordinates&);
        void swapTwoPawns(Pawn*, Pawn*);
    };

``pawn.hpp``
================

This `header <https://github.com/FLAK-ZOSO/Sista/blob/main/include/sista/pawn.hpp>`_ contains the following "abstract" class used to represent a pawn.

.. code-block:: cpp

    class Pawn {
    protected:
        char symbol;
        Coordinates coordinates;
        ANSI::Settings settings;

    public:
        Pawn(char, Coordinates, ANSI::Settings);
        Pawn(char, Coordinates&, ANSI::Settings&, bool);
        virtual ~Pawn();

        virtual void print();
    };

``sista.hpp``
================

This `header <https://github.com/FLAK-ZOSO/Sista/blob/main/include/sista/sista.hpp>`_ includes all the other headers.

.. code-block:: cpp

    #include "ANSI-Settings.hpp" // ANSI::ForegroundColor, ANSI::BackgroundColor, ANSI::Attribute, ANSI::Settings
    #include "border.hpp" // Border
    #include "coordinates.hpp" // Coord, Coordinates, <utility>
    #include "pawn.hpp" // Pawn
    #include "field.hpp" // Field, Path, SwappableField
    #include "cursor.hpp" // Cursor, clearScreen [cross-platform since v0.6.0]