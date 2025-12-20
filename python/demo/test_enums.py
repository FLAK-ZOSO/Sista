#!/usr/bin/env python3
"""Test script to verify enum exposure in sista module"""

import sys

try:
    import sista
    
    print("Testing enum exposure...")
    
    # Test foreground colors
    sista.set_foreground_color(sista.F_BLACK)
    sista.print(f"F_BLACK = {sista.F_BLACK}")
    sista.set_foreground_color(sista.F_RED)
    sista.print(f"F_RED = {sista.F_RED}")
    sista.set_foreground_color(sista.F_GREEN)
    sista.print(f"F_GREEN = {sista.F_GREEN}")
    sista.set_foreground_color(sista.F_YELLOW)
    sista.print(f"F_YELLOW = {sista.F_YELLOW}")
    sista.set_foreground_color(sista.F_BLUE)
    sista.print(f"F_BLUE = {sista.F_BLUE}")
    sista.set_foreground_color(sista.F_MAGENTA)
    sista.print(f"F_MAGENTA = {sista.F_MAGENTA}")
    sista.set_foreground_color(sista.F_CYAN)
    sista.print(f"F_CYAN = {sista.F_CYAN}")
    sista.set_foreground_color(sista.F_WHITE)
    sista.print(f"F_WHITE = {sista.F_WHITE}")
    
    # Test background colors
    sista.set_background_color(sista.B_BLACK)
    sista.print(f"B_BLACK = {sista.B_BLACK}")
    sista.set_background_color(sista.B_RED)
    sista.print(f"B_RED = {sista.B_RED}")
    sista.set_background_color(sista.B_GREEN)
    sista.print(f"B_GREEN = {sista.B_GREEN}")
    sista.set_background_color(sista.B_YELLOW)
    sista.print(f"B_YELLOW = {sista.B_YELLOW}")
    sista.set_background_color(sista.B_BLUE)
    sista.print(f"B_BLUE = {sista.B_BLUE}")
    sista.set_background_color(sista.B_MAGENTA)
    sista.print(f"B_MAGENTA = {sista.B_MAGENTA}")
    sista.set_background_color(sista.B_CYAN)
    sista.print(f"B_CYAN = {sista.B_CYAN}")
    sista.set_background_color(sista.B_WHITE)
    sista.print(f"B_WHITE = {sista.B_WHITE}")
    
    # Test attributes
    sista.set_attribute(sista.A_RESET)
    sista.print(f"A_RESET = {sista.A_RESET}")
    sista.set_attribute(sista.A_BRIGHT)
    sista.print(f"A_BRIGHT = {sista.A_BRIGHT}")
    sista.set_attribute(sista.A_RESET)
    sista.set_attribute(sista.A_FAINT)
    sista.print(f"A_FAINT = {sista.A_FAINT}")
    sista.set_attribute(sista.A_RESET)
    sista.set_attribute(sista.A_ITALIC)
    sista.print(f"A_ITALIC = {sista.A_ITALIC}")
    sista.set_attribute(sista.A_RESET)
    sista.set_attribute(sista.A_UNDERLINE)
    sista.print(f"A_UNDERLINE = {sista.A_UNDERLINE}")
    sista.set_attribute(sista.A_RESET)
    sista.set_attribute(sista.A_BLINK)
    sista.print(f"A_BLINK = {sista.A_BLINK}")
    sista.set_attribute(sista.A_RESET)
    sista.set_attribute(sista.A_BLINK_FAST)
    sista.print(f"A_BLINK_FAST = {sista.A_BLINK_FAST}")
    sista.set_attribute(sista.A_RESET)
    sista.set_attribute(sista.A_REVERSE)
    sista.print(f"A_REVERSE = {sista.A_REVERSE}")
    sista.set_attribute(sista.A_RESET)
    sista.set_attribute(sista.A_HIDDEN)
    sista.print(f"A_HIDDEN = {sista.A_HIDDEN}")
    sista.set_attribute(sista.A_RESET)
    sista.set_attribute(sista.A_STRIKETHROUGH)
    sista.print(f"A_STRIKETHROUGH = {sista.A_STRIKETHROUGH}")
    sista.set_attribute(sista.A_RESET)
    
    sista.print("\nAll enums successfully exposed!")
except ImportError as e:
    print(f"Failed to import sista module: {e}", file=sys.stderr)
    sys.exit(1)
except Exception as e:
    print(f"Error testing enums: {e}")
    sys.exit(1)
