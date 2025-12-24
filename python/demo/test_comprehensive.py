#!/usr/bin/env python3
"""Comprehensive (not actually) test script for sista Python C extension module"""

import sys
import traceback
import time
import typing

try:
    import sista
    print("Successfully imported sista module")
except ImportError as e:
    print(f"Failed to import sista module: {e}", file=sys.stderr)
    sys.exit(1)

def test_basic_functionality():
    """Test basic functionality of the module"""
    print("=== Testing Basic Functionality ===")
    
    # Test print function
    sista.print("Testing basic print function")
    
    # Test setting colors and attributes
    sista.set_foreground_color(sista.F_RED)
    sista.print("This should be red")
    
    sista.set_background_color(sista.B_BLUE)
    sista.print("This should have blue background")
    
    sista.set_attribute(sista.A_BRIGHT)
    sista.print("This should be bold")
    
    sista.reset_attribute(sista.A_BRIGHT)
    sista.print("This should not be bold")
    
    sista.reset_ansi()
    sista.print("ANSI settings reset")

def test_swappable_field():
    """Test SwappableField creation and manipulation"""
    print("=== Testing SwappableField ===")
    
    # Create a swappable field
    field = sista.create_swappable_field(10, 5)
    print(f"Created swappable field: {field}")
    
    # Test invalid dimensions
    try:
        sista.create_swappable_field(-1, 5)
        print("ERROR: Should have failed with negative width")
    except ValueError:
        print("Correctly rejected negative width")
    
    try:
        sista.create_swappable_field(5, -1)
        print("ERROR: Should have failed with negative height")
    except ValueError:
        print("Correctly rejected negative height")
    
    # Create ANSI settings
    settings = sista.create_ansi_settings(sista.F_GREEN, sista.B_BLACK, sista.A_UNDERLINE)
    print(f"Created ANSI settings: {settings}")
    
    # Create coordinates
    coords = sista.create_coordinates(2, 3)
    print(f"Created coordinates: {coords}")
    
    # Create pawn
    pawn = sista.create_pawn_in_swappable_field(field, "P", settings, coords)
    print(f"Created pawn: {pawn}")
    
    # Test invalid pawn creation
    try:
        sista.create_pawn_in_swappable_field(None, "P", settings, coords)
        print("ERROR: Should have failed with None field")
    except ValueError:
        print("Correctly rejected None field")
    
    # Test invalid symbol length
    try:
        sista.create_pawn_in_swappable_field(field, "PP", settings, coords)
        print("ERROR: Should have failed with multi-character symbol")
    except ValueError:
        print("Correctly rejected multi-character symbol")
    
    sista.add_pawn_to_swap(field, pawn, sista.create_coordinates(3, 3))
    print("Scheduled pawn for swap")

    sista.apply_swaps(field)
    print("Applied swaps in swappable field")

def test_border_functionality():
    """Test Border creation and usage"""
    print("=== Testing Border Functionality ===")
    
    # Create a swappable field
    field = sista.create_swappable_field(15, 8)
    
    # Create ANSI settings for border
    border_settings = sista.create_ansi_settings(sista.F_CYAN, sista.B_BLACK, sista.A_BRIGHT)
    
    # Create border
    border = sista.create_border("#", border_settings)
    print(f"Created border: {border}")
    
    # Test invalid border symbol
    try:
        sista.create_border("##", border_settings)
        print("ERROR: Should have failed with multi-character border symbol")
    except ValueError:
        print("Correctly rejected multi-character border symbol")
    
    # Test invalid border settings
    try:
        sista.create_border("#", None)
        print("ERROR: Should have failed with None settings")
    except ValueError:
        print("Correctly rejected None settings")

def test_coordinates():
    """Test Coordinates creation and handling"""
    print("=== Testing Coordinates ===")
    
    # Create valid coordinates
    coords = sista.create_coordinates(10, 20)
    print(f"Created coordinates: {coords}")
    
    # Test coordinate values
    coords2 = sista.create_coordinates(0, 0)
    print(f"Created zero coordinates: {coords2}")

def test_pawn_operations():
    """Test pawn-related operations"""
    print("=== Testing Pawn Operations ===")
    
    # Create field, settings, and pawn
    field = sista.create_swappable_field(10, 10)
    settings = sista.create_ansi_settings(sista.F_WHITE, sista.B_BLACK, sista.A_RESET)
    coords = sista.create_coordinates(5, 5)
    pawn = sista.create_pawn_in_swappable_field(field, "P", settings, coords)
    
    # Test adding pawn to swap
    result = sista.add_pawn_to_swap(field, pawn, coords)
    print(f"Add pawn to swap result: {result}")
    
    # Test invalid add operation
    try:
        sista.add_pawn_to_swap(None, pawn, coords)
        print("ERROR: Should have failed with None field")
    except ValueError:
        print("Correctly rejected None field in add_pawn_to_swap")
    
    try:
        sista.add_pawn_to_swap(field, None, coords)
        print("ERROR: Should have failed with None pawn")
    except ValueError:
        print("Correctly rejected None pawn in add_pawn_to_swap")

def test_enum_exposure():
    """Test that all enums are properly exposed"""
    print("=== Testing Enum Exposure ===")
    
    # Test all foreground colors
    colors = [
        sista.F_BLACK, sista.F_RED, sista.F_GREEN, sista.F_YELLOW,
        sista.F_BLUE, sista.F_MAGENTA, sista.F_CYAN, sista.F_WHITE
    ]
    
    for i, color in enumerate(colors):
        print(f"Foreground color {i}: {color}")
    
    # Test all background colors
    bcolors = [
        sista.B_BLACK, sista.B_RED, sista.B_GREEN, sista.B_YELLOW,
        sista.B_BLUE, sista.B_MAGENTA, sista.B_CYAN, sista.B_WHITE
    ]
    
    for i, color in enumerate(bcolors):
        print(f"Background color {i}: {color}")
    
    # Test all attributes
    attrs = [
        sista.A_RESET, sista.A_BRIGHT, sista.A_FAINT, sista.A_ITALIC,
        sista.A_UNDERLINE, sista.A_BLINK, sista.A_BLINK_FAST, sista.A_REVERSE,
        sista.A_HIDDEN, sista.A_STRIKETHROUGH
    ]
    
    for i, attr in enumerate(attrs):
        print(f"Attribute {i}: {attr}")

def test_cursor_functions():
    """Test cursor creation and movement"""
    print("=== Testing Cursor Functions ===")
    
    # Create cursor
    cursor = sista.create_cursor()
    print(f"Created cursor: {cursor}")
    
    # Create coordinates
    coords = sista.create_coordinates(3, 4)
    print(f"Created coordinates for movement: {coords}")
    
    # Move cursor to coordinates
    sista.cursor_go_to_coordinates(cursor, coords)
    print("Moved cursor to specified coordinates")
    
    # Test invalid move
    try:
        sista.cursor_go_to_coordinates(None, coords)
        print("ERROR: Should have failed with None cursor")
    except ValueError:
        print("Correctly rejected None cursor in move_cursor_to_coordinates")
    
    try:
        sista.cursor_go_to_coordinates(cursor, None)
        print("ERROR: Should have failed with None coordinates")
    except ValueError:
        print("Correctly rejected None coordinates in move_cursor_to_coordinates")

def test_version():
    """Test version retrieval"""
    print("=== Testing Version Retrieval ===")
    
    try:
        version = sista.__version__
        print(f"Module version: {version}")
    except Exception as e:
        print(f"Error retrieving version: {e}")

def main():
    """Run all tests"""
    print("Running comprehensive tests for sista Python C extension...")
    
    tests: list[typing.Callable] = [
        test_basic_functionality,
        test_swappable_field,
        test_border_functionality,
        test_coordinates,
        test_pawn_operations,
        test_enum_exposure,
        test_cursor_functions,
        test_version,
    ]

    try:
        for test in tests:
            test()
            time.sleep(1)
        
        print("=== All Tests Completed Successfully ===")
        return 0
        
    except Exception as e:
        print(f"=== Test Failed ===")
        print(f"Error: {e}")
        traceback.print_exc()
        return 1

if __name__ == "__main__":
    sys.exit(main())
