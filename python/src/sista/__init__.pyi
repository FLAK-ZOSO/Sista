from typing import Any

# Type alias used for opaque Python capsules returned by the C extension.
Capsule = Any

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

# API functions (adjust signatures if needed)
def set_foreground_color(color: int) -> None: ...
def set_background_color(color: int) -> None: ...
def set_attribute(attribute: int) -> None: ...
def reset_attribute(attribute: int) -> None: ...
def reset_ansi() -> None: ...
def print(message: str) -> None: ...

def create_swappable_field(width: int, height: int) -> Capsule: ...
def create_ansi_settings(fgcolor: int = ..., bgcolor: int = ..., attribute: int = ...) -> Capsule: ...
def create_border(symbol: str, ansi_settings_capsule: Capsule) -> Capsule: ...
def create_pawn_in_swappable_field(field_capsule: Capsule, symbol: str, ansi_capsule: Capsule, coords_capsule: Capsule) -> Capsule: ...
def create_coordinates(y: int, x: int) -> Capsule: ...
def move_pawn(field_capsule: Capsule, pawn_capsule: Capsule, dx: int, dy: int) -> int: ...
def add_pawn_to_swap(field_capsule: Capsule, pawn_capsule: Capsule, coords_capsule: Capsule) -> int: ...
def create_pawn_in_field(field_capsule: Capsule, symbol: str, ansi_capsule: Capsule, coords_capsule: Capsule) -> Capsule: ...
