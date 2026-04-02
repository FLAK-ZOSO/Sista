# Sista Python C Extension

This directory contains the Python C extension module for the Sista library, which exposes the C API functionality to Python.

## Features

- Full access to Sista C API functions
- Enum values exposed for foreground colors, background colors, and text attributes
- Automatic memory management through Python capsules and objects
- Pythonic exception-based error handling (no status-code checking on success paths)

## Installation

### Just use pip to install [from PyPI](https://pypi.org/project/sista/)

```bash
pip install sista
```

## Building the Extension

### Prerequisites

Before building the extension, ensure you have:

1. Python development headers installed
2. C++ compiler (g++, clang++, etc.)
3. The Sista C++ library built and available

### Building Process

#### Option 1: Using setup.py (Recommended)

```bash
# Navigate to the project root directory
cd python

# Install required Python packages
pip install setuptools wheel

# Build the extension
python setup.py build_ext --inplace
```

## Installing the Extension

Once built, the extension can be installed in your Python environment:

```bash
# Install in development mode
pip install -e .

# Or simply copy the built .so file to your Python site-packages directory
```

## Using the Extension

After successful compilation and installation, you can use the module in Python:

```python
import sista

# Access enum values
print(sista.F_BLACK)    # 30
print(sista.F_RED)      # 31
print(sista.B_WHITE)    # 47
print(sista.A_BRIGHT)  # 1

field = sista.Field(10, 5)
settings = sista.create_ansi_settings(sista.F_RED, sista.B_BLACK, sista.A_BLINK)
pawn = field.create_pawn('P', settings, sista.create_coordinates(0, 0))
border = sista.create_border('#', sista.create_ansi_settings(sista.F_CYAN, sista.B_BLACK, sista.A_BRIGHT))

sista.clear_screen(True)
field.print_with_border(border)

field.move_pawn(pawn, 1, 1)
field.print_with_border(border)
```

## Error Handling (Exceptions)

The Python API raises exceptions for failures reported by the C layer.

- `ValueError`: invalid handles or invalid user-provided objects.
- `IndexError`: out-of-bounds coordinates.
- `MemoryError`: allocation failures.
- `RuntimeError`: other Sista API errors.

Example:

```python
import sista

field = sista.Field(2, 2)
settings = sista.create_ansi_settings(sista.F_WHITE, sista.B_BLACK, sista.A_RESET)
pawn = field.create_pawn('P', settings, sista.create_coordinates(0, 0))

try:
    field.move_pawn(pawn, 99, 99)
except IndexError as exc:
    print(f"Move failed as expected: {exc}")
```

See the demos in [`demo/`](demo/) for more examples.

## Testing

You can test the extension with the provided test script:

```bash
python demo/test_comprehensive.py
```

This verifies core API behavior, including exception paths.

## Troubleshooting

### Common Issues

1. **Python.h not found**: Install Python development headers
   - Ubuntu/Debian: `sudo apt-get install python3-dev`
   - CentOS/RHEL: `sudo yum install python3-devel`
   - macOS: `brew install python`

2. **Library linking errors**: Make sure the Sista libraries are built and in your library path

3. **Permission denied**: Run with appropriate permissions or use virtual environments

## License

This Python extension is licensed under the same license as the Sista project (GNU General Public License v3.0).
