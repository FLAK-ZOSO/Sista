#!/usr/bin/env python3
"""Test script to verify enum exposure in sista module"""

import sys
import os

# Add the current directory to Python path to import the local sista module
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

try:
    import sista
    
    print("Testing enum exposure...")
    
    # Test foreground colors
    print(f"F_BLACK = {sista.F_BLACK}")
    print(f"F_RED = {sista.F_RED}")
    print(f"F_GREEN = {sista.F_GREEN}")
    print(f"F_YELLOW = {sista.F_YELLOW}")
    print(f"F_BLUE = {sista.F_BLUE}")
    print(f"F_MAGENTA = {sista.F_MAGENTA}")
    print(f"F_CYAN = {sista.F_CYAN}")
    print(f"F_WHITE = {sista.F_WHITE}")
    
    # Test background colors
    print(f"B_BLACK = {sista.B_BLACK}")
    print(f"B_RED = {sista.B_RED}")
    print(f"B_GREEN = {sista.B_GREEN}")
    print(f"B_YELLOW = {sista.B_YELLOW}")
    print(f"B_BLUE = {sista.B_BLUE}")
    print(f"B_MAGENTA = {sista.B_MAGENTA}")
    print(f"B_CYAN = {sista.B_CYAN}")
    print(f"B_WHITE = {sista.B_WHITE}")
    
    # Test attributes
    print(f"A_RESET = {sista.A_RESET}")
    print(f"A_BRIGHT = {sista.A_BRIGHT}")
    print(f"A_FAINT = {sista.A_FAINT}")
    print(f"A_ITALIC = {sista.A_ITALIC}")
    print(f"A_UNDERLINE = {sista.A_UNDERLINE}")
    print(f"A_BLINK = {sista.A_BLINK}")
    print(f"A_BLINK_FAST = {sista.A_BLINK_FAST}")
    print(f"A_REVERSE = {sista.A_REVERSE}")
    print(f"A_HIDDEN = {sista.A_HIDDEN}")
    print(f"A_STRIKETHROUGH = {sista.A_STRIKETHROUGH}")
    
    print("\nAll enums successfully exposed!")

    sista.set_foreground_color(sista.F_MAGENTA)
    sista.print("Rather suspicious")
except ImportError as e:
    print(f"Failed to import sista module: {e}")
    sys.exit(1)
except Exception as e:
    print(f"Error testing enums: {e}")
    sys.exit(1)
