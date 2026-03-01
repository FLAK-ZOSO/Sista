import sista
import time

field = sista.Field(30, 5)
settings = sista.create_ansi_settings(sista.F_RED, sista.B_BLACK, sista.A_BLINK)
coordinates = sista.create_coordinates(0, 0)
pawn = field.create_pawn('P', settings, coordinates)
border = sista.create_border(
    '#', sista.create_ansi_settings(
        sista.F_CYAN,
        sista.B_BLUE,
        sista.A_BRIGHT
    )
)
field.print_with_border(border)
time.sleep(2)
