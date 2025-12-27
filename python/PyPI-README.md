# Sista - Python C extension for Sista C++ Library

This repository contains a Python C extension that provides bindings to the Sista C++ library, enabling Python developers to leverage its functionality for ANSI terminal graphics manipulation, videogame and animation development.

## Features

- Full access to Sista C API functions
- Enum values exposed for foreground colors, background colors, and text attributes
- Automatic memory management through Python capsules and objects

## Dependencies

- [Python 3.9 or higher](https://www.python.org/downloads/)
- [Sista C++ library](https://github.com/FLAK-ZOSO/Sista?tab=readme-ov-file#installation)

## Installation

Since the wheel package is available on PyPI, you can easily install it using pip:

```bash
pip install sista
```

## Usage

After successful installation, you can use the `sista` module in your Python scripts:

```python
import sista
```

## Documentation

- https://flak-zoso.github.io/Sista/sista-python

The documentation is generated with...

```bash
python -m pdoc --html sista --output-dir docs --force
```

...and can be found in the `docs` directory. You can also host it locally using:

```bash
python -m http.server --directory docs
```

Then, open your web browser and navigate to `http://localhost:8000/sista/index.html` to view the documentation.
