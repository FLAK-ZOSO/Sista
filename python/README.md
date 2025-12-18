# Sista Python C Extension

This directory contains the Python C extension module for the Sista library, which exposes the C API functionality to Python.

## Features

- Full access to Sista C API functions
- Enum values exposed for foreground colors, background colors, and text attributes
- Automatic memory management through Python capsules

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
cd /path/to/sista

# Install required Python packages
pip install setuptools wheel

# Build the extension
python setup.py build_ext --inplace
```

### Alternative: Manual Compilation

If you prefer manual compilation:

```bash
# Compile the extension module
gcc -shared -fPIC -I/usr/include/python3.13 -I../include -I../include/sista \
    -o sista.cpython-313-x86_64-linux-gnu.so sistamodule.c \
    -lSista_api -lSista
```

Replace `python3.x` with your Python version and adjust library paths as needed.

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
print(sista.A_BOLD)     # 1

# Use the API functions
field = sista.create_swappable_field(10, 10)
# ... use the field ...
sista.destroy_swappable_field(field)
```

## Testing

You can test the extension with the provided test script:

```bash
python test_enums.py
```

This should output all the enum values that were successfully exposed.

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