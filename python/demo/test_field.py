import sista
import time

field = sista.create_swappable_field(30, 5)
settings = sista.create_ansi_settings(sista.F_RED, sista.B_BLACK, sista.A_BLINK)
coordinates = sista.create_coordinates(0, 0)
pawn = sista.create_pawn_in_swappable_field(field, 'P', settings, coordinates)
border = sista.create_border(
    '#', sista.create_ansi_settings(
        sista.F_CYAN,
        sista.B_BLUE,
        sista.A_BRIGHT
    )
)
sista.print_swappable_field_with_border(field, border)
time.sleep(2)
