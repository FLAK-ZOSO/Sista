import sista
import time

field = sista.Field(30, 5)
settings = sista.create_ansi_settings(sista.F_RED, sista.B_BLACK, sista.A_BLINK)
coordinates = sista.create_coordinates(0, 0)
pawn = field.create_pawn('P', settings, coordinates)
assert isinstance(pawn, sista.Pawn), "Field.create_pawn must return a Pawn object"

border = sista.create_border(
    '#', sista.create_ansi_settings(
        sista.F_CYAN,
        sista.B_BLUE,
        sista.A_BRIGHT
    )
)

try:
    sista.clear_screen(True)
    field.print_with_border(border)
    time.sleep(2)

    field.move_pawn(pawn, 1, 1)

    sista.clear_screen(True)
    field.print_with_border(border)
    time.sleep(2)

    # Explicit negative-path example for the new exception model.
    try:
        field.move_pawn(pawn, 999, 999)
    except IndexError as exc:
        print()
        print(f"Expected move_pawn error: {exc}")
finally:
    sista.reset_ansi()
    print()
