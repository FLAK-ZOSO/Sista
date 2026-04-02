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

sista.clear_screen(True)
field.print_with_border(border)
time.sleep(2)

status = field.move_pawn(pawn, 1, 1)
assert status == 0, f"move_pawn failed with status {status}"

sista.clear_screen(True)
field.print_with_border(border)
time.sleep(2)
