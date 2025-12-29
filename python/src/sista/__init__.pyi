"""Python type hints and pydocstrings for the Sista C extension module."""
from __future__ import annotations
from typing import Any

# Type alias used for opaque Python capsules returned by the C extension.
Capsule = Any

__version__ = '3.0.0-beta.1'

# constants
F_BLACK: int
F_RED: int
F_GREEN: int
F_YELLOW: int
F_BLUE: int
F_MAGENTA: int
F_CYAN: int
F_WHITE: int

B_BLACK: int
B_RED: int
B_GREEN: int
B_YELLOW: int
B_BLUE: int
B_MAGENTA: int
B_CYAN: int
B_WHITE: int

A_RESET: int
A_BRIGHT: int
A_FAINT: int
A_ITALIC: int
A_UNDERLINE: int
A_BLINK: int
A_BLINK_FAST: int
A_REVERSE: int
A_HIDDEN: int
A_STRIKETHROUGH: int

DIRECTION_UP: int
DIRECTION_DOWN: int
DIRECTION_RIGHT: int
DIRECTION_LEFT: int
BEGINNING_OF_NEXT_LINE: int
BEGINNING_OF_PREVIOUS_LINE: int

def set_foreground_color(color: int) -> None:
    """
    Set the terminal foreground color using one of the F_* constants.

    :param color: One of the F_* constants (e.g. F_RED).
    :type color: int
    """
    ...
def set_background_color(color: int) -> None:
    """
    Set the terminal background color using one of the B_* constants.

    :param color: One of the B_* constants (e.g. B_BLUE).
    :type color: int
    """
    ...
def set_attribute(attribute: int) -> None:
    """
    Enable a terminal text attribute using one of the A_* constants.

    :param attribute: One of the A_* constants (e.g. A_UNDERLINE).
    :type attribute: int
    """
    ...
def reset_attribute(attribute: int) -> None:
    """
    Disable/reset a terminal text attribute using one of the A_* constants.

    :param attribute: One of the A_* constants (e.g. A_RESET).
    :type attribute: int
    """
    ...
def reset_ansi() -> None:
    """
    Reset all ANSI text attributes and colors to the terminal defaults.
    """
    ...
def print(message: str) -> None:
    """
    Print a message to the terminal using Sista's configured output stream.

    The function respects Sista's current ANSI settings (colors/attributes)
    as managed by the extension.

    :param message: Message to print (a single text line).
    :type message: str
    """
    ...

def create_ansi_settings(fgcolor: int = ..., bgcolor: int = ..., attribute: int = ...) -> Capsule:
    """
    Create an ANSI settings object and return it as a Capsule.

    The settings object describes foreground/background colors and a text
    attribute to be applied when rendering borders, pawns, etc.

    :param fgcolor: Foreground color (one of the F_* constants).
    :param bgcolor: Background color (one of the B_* constants).
    :param attribute: Text attribute (one of the A_* constants).
    :return: Capsule wrapping the ANSISettings handler.
    """
    ...
def create_border(symbol: str, ansi_settings: Capsule) -> Capsule:
    """
    Create a Border object that uses a single-character symbol and ANSI settings.

    :param symbol: Single character string used to draw border bricks.
    :param ansi_settings: Capsule returned by create_ansi_settings.
    :return: Capsule wrapping the Border handler.
    """
    ...

class Field:
    """
    Class representing a terminal Field for pawns and borders.
    """

    def __new__(cls, width: int, height: int) -> Field: ...

    def __init__(self, width: int, height: int) -> None:
        """
        Create and return a Field wrapper object.

        The returned object is a Python wrapper that owns the underlying C
        Field handler. Use the instance methods (create_pawn, move_pawn,
        print_with_border) on the returned Field object. The wrapper
        manages the C-side lifetime (it will destroy the C handler when the
        Python object is deallocated).

        :param width: Field width (number of columns).
        :param height: Field height (number of rows).
        """
        ...

    def create_pawn(self, symbol: str, ansi_settings: Capsule, coords: Capsule) -> Capsule:
        """
        Create a Pawn inside this Field and return a Pawn capsule.

        Pawns created in plain Fields are managed by the Field object.

        :param symbol: Single character string representing the pawn.
        :param ansi_settings: Capsule returned by create_ansi_settings.
        :param coords: Capsule returned by create_coordinates.
        :return: Capsule wrapping the Pawn handler.
        """
        ...
    def move_pawn(self, pawn: Capsule, y: int, x: int) -> int:
        """
        Move a pawn inside this Field by the given delta and return a status code.

        The meaning of the returned integer follows the library's convention
        (0 for success, non-zero for various errors such as out-of-bounds or
        occupied destination).

        :param pawn: Capsule for the Pawn to move.
        :param y: y coordinate of the destination.
        :param x: x coordinate of the destination.
        :return: Integer status code (0 == success).
        """
        ...
    def print_with_border(self, border: Capsule) -> None:
        """
        Render this Field to the terminal using the given Border object.

        :param border: Capsule for the Border to draw around the field.
        """
        ...

class SwappableField:
    """
    Class representing a terminal SwappableField for pawns and borders.
    """

    def __new__(cls, width: int, height: int) -> SwappableField: ...

    def __init__(self, width: int, height: int) -> None:
        """
        Create and return a SwappableField wrapper object.

        The returned object is a Python wrapper that owns the underlying C
        SwappableField handler. Use the instance methods (create_pawn,
        print_with_border, add_pawn_to_swap, apply_swaps) on the returned
        SwappableField object. The wrapper manages the C-side lifetime (it
        will destroy the C handler when the Python object is deallocated).

        :param width: Field width (number of columns).
        :param height: Field height (number of rows).
        """
        ...

    def create_pawn(self, symbol: str, ansi_settings: Capsule, coords: Capsule) -> Capsule:
        """
        Create a Pawn inside this SwappableField and return a Pawn capsule.

        The pawn is created at the specified coordinates and rendered using the
        provided ANSI settings. Pawns created in swappable fields are managed by
        the field (caller should not free the pawn handle).

        :param symbol: Single character string used to represent the pawn.
        :param ansi_settings: Capsule returned by create_ansi_settings.
        :param coords: Capsule returned by create_coordinates.
        :return: Capsule wrapping the Pawn handler.
        """
        ...
    def print_with_border(self, border: Capsule) -> None:
        """
        Render this SwappableField to the terminal using the given Border object.

        :param border: Capsule for the Border to draw around the field.
        """
        ...
    def add_pawn_to_swap(self, pawn: Capsule, coords: Capsule) -> int:
        """
        Schedule a pawn to be moved (swapped) later in this SwappableField.

        The function adds the pawn and its destination coordinates to the swap
        list managed by the SwappableField. Call apply_swaps (or the
        equivalent) to execute scheduled swaps.

        :param pawn: Capsule for the Pawn to schedule.
        :param coords: Capsule with the destination coordinates.
        :return: Integer status code (0 == added successfully).
        """
        ...
    def apply_swaps(self) -> None:
        """
        Execute all scheduled pawn swaps in this SwappableField.

        The function processes all pawns previously added to the swap list
        using add_pawn_to_swap, moving them to their target coordinates.

        :return: None. Raises an exception on error.
        """
        ...

def create_coordinates(y: int, x: int) -> Capsule:
    """
    Create a Coordinates object and return it as a Capsule.

    Coordinates are small value objects (y,row and x,column) used by pawn
    creation and movement functions. Caller is responsible for freeing the
    capsule when no longer needed (the extension provides destructors).

    :param y: Row index (unsigned short).
    :param x: Column index (unsigned short).
    :return: Capsule wrapping a Coordinates struct.
    """
    ...
def move_pawn(field: Capsule, pawn: Capsule, dx: int, dy: int) -> int:
    """
    Move a pawn inside a Field by the given delta and return a status code.

    The meaning of the returned integer follows the library's convention
    (0 for success, non-zero for various errors such as out-of-bounds or
    occupied destination).

    :param field: Capsule for the Field containing the pawn.
    :param pawn: Capsule for the Pawn to move.
    :param dx: Delta in the x (column) direction.
    :param dy: Delta in the y (row) direction.
    :return: Integer status code (0 == success).
    """
    ...
def add_pawn_to_swap(field: Capsule, pawn: Capsule, coords: Capsule) -> int:
    """
    Schedule a pawn to be moved (swapped) later in a SwappableField.

    The function adds the pawn and its destination coordinates to the swap
    list managed by the SwappableField. Call sista.apply_swaps (or the
    equivalent) to execute scheduled swaps.

    :param field: Capsule for the SwappableField.
    :param pawn: Capsule for the Pawn to schedule.
    :param coords: Capsule with the destination coordinates.
    :return: Integer status code (0 == added successfully).
    """
    ...
def apply_swaps(field: Capsule) -> int:
    """
    Execute all scheduled pawn swaps in the given SwappableField.

    The function processes all pawns previously added to the swap list
    using add_pawn_to_swap, moving them to their target coordinates.

    :param field: Capsule for the SwappableField.
    :return: Integer status code (0 == success).
    """
    ...
def create_pawn_in_field(field: Capsule, symbol: str, ansi_settings: Capsule, coords: Capsule) -> Capsule:
    """
    Create a Pawn inside a non-swappable Field and return a Pawn capsule.

    Pawns created in plain Fields are managed by the Field object.

    :param field: Capsule returned by the Field creation function.
    :param symbol: Single character string representing the pawn.
    :param ansi_settings: Capsule returned by create_ansi_settings.
    :param coords: Capsule returned by create_coordinates.
    :return: Capsule wrapping the Pawn handler.
    """
    ...
def print_swappable_field_with_border(field: Capsule, border: Capsule) -> None:
    """
    Render a SwappableField to the terminal using the given Border object.

    :param field: Capsule for the SwappableField to print.
    :param border: Capsule for the Border to draw around the field.
    """
    ...
def print_field_with_border(field: Capsule, border: Capsule) -> None:
    """
    Render a Field to the terminal using the given Border object.

    :param field: Capsule for the Field to print.
    :param border: Capsule for the Border to draw around the field.
    """
    ...

class Cursor:
    """
    Class representing a terminal cursor for movement operations.
    """

    def __new__(cls) -> Cursor: ...

    def __init__(self) -> None:
        """
        Create and return a Cursor wrapper object.

        The returned object is a Python wrapper that owns the underlying C
        Cursor handler. Use the instance methods (move, go_to,
        go_to_coordinates) on the returned Cursor object. The wrapper
        manages the C-side lifetime (it will destroy the C handler when the
        Python object is deallocated).
        """
        ...

    def move(self, direction: int, amount: int) -> None:
        """
        Move the cursor in the specified direction by the given amount.

        :param direction: One of the DIRECTION_* constants (or equivalent).
        :param amount: Number of positions to move the cursor.
        """
        ...

    def go_to(self, y: int, x: int) -> None:
        """
        Move the cursor to the absolute (y, x) position.

        :param y: Row index to move to.
        :param x: Column index to move to.
        """
        ...

    def go_to_coordinates(self, coords: Capsule) -> None:
        """
        Move the cursor to the position described by a Coordinates capsule.

        :param coords: Capsule returned by create_coordinates.
        """
        ...
