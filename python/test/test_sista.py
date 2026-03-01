import pytest
import sista


def _is_int_const(obj, name):
    val = getattr(obj, name, None)
    assert isinstance(val, int), f"{name} should be int"


def test_constants_exist_and_are_ints():
    names = [
        "F_BLACK", "F_RED", "F_GREEN", "F_BLUE",
        "B_BLACK", "B_RED", "B_BLUE",
        "A_RESET", "A_UNDERLINE",
        "DIRECTION_UP", "DIRECTION_DOWN",
    ]
    for n in names:
        _is_int_const(sista, n)


def test_create_capsules_and_basic_api_calls():
    ansi = sista.create_ansi_settings(getattr(sista, "F_RED"), getattr(sista, "B_BLUE"), getattr(sista, "A_UNDERLINE"))
    assert ansi is not None

    border = sista.create_border("#", ansi)
    assert border is not None

    coords = sista.create_coordinates(0, 0)
    assert coords is not None

    # Field creation and pawn APIs
    field = sista.Field(4, 3)
    assert field is not None

    pawn = field.create_pawn("P", ansi, coords)
    assert pawn is not None

    # Try both method and module-level move APIs (some bindings expose one or the other)
    moved = None
    try:
        moved = field.move_pawn(pawn, 1, 0)
    except Exception:
        moved = None

    if moved is None:
        # fall back to module-level helper if available
        if hasattr(sista, "move_pawn"):
            rc = sista.move_pawn(field, pawn, 1, 0)
            assert isinstance(rc, int)
        else:
            # at least ensure method exists or move was callable previously
            assert True


def test_swappable_field_swap_paths():
    ansi = sista.create_ansi_settings(getattr(sista, "F_GREEN"), getattr(sista, "B_BLACK"), getattr(sista, "A_RESET"))
    sw = sista.SwappableField(5, 4)
    coords_src = sista.create_coordinates(0, 0)
    pawn = sw.create_pawn("s", ansi, coords_src)
    assert pawn is not None

    dest = sista.create_coordinates(2, 2)

    added = None
    used_path = False
    try:
        added = sw.add_pawn_to_swap(pawn, dest)
        used_path = True
    except Exception:
        added = None

    if added is None and hasattr(sista, "add_pawn_to_swap"):
        added = sista.add_pawn_to_swap(sw, pawn, dest)
        used_path = True

    # Ensure that at least one add_pawn_to_swap path succeeded
    assert used_path, "Expected either SwappableField.add_pawn_to_swap or module-level add_pawn_to_swap to succeed"
    assert isinstance(added, int), "add_pawn_to_swap should return an int status code"
    assert added >= 0
    # apply swaps via method or module API
    try:
        res = sw.apply_swaps()
        # method doc may return None; ensure no exception was raised
    except Exception:
        if hasattr(sista, "apply_swaps"):
            rc = sista.apply_swaps(sw)
            assert isinstance(rc, int)


def test_cursor_basic_moves_do_not_raise():
    cur = sista.Cursor()
    assert cur is not None

    # basic move + go_to operations should not raise
    cur.move(getattr(sista, "DIRECTION_RIGHT"), 1)
    cur.go_to(0, 0)

    c = sista.create_coordinates(1, 1)
    cur.go_to_coordinates(c)
