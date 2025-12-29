"""Memory-safe and OS-agnostic library for making terminal videogames and animations"""
__version__ = '3.0.0-beta.1'

# Do NOT import the compiled extension at import-time (keeps metadata reads safe).
# Lazy-load the private extension module on attribute access.

MODULE_NAME = f"{__name__}._sista"

def _load_ext():
    import importlib
    import importlib.util
    try:
        return importlib.import_module(MODULE_NAME)
    except Exception as e:
        # give useful diagnostics and preserve original error
        spec = importlib.util.find_spec(MODULE_NAME)
        raise ImportError(f"Failed to load compiled extension '{MODULE_NAME}': {e!s} (spec={spec!r})") from e

def __getattr__(name: str):
    # forward lookups to the compiled submodule (constants, functions)
    ext = _load_ext()
    if hasattr(ext, name):
        return getattr(ext, name)
    raise AttributeError(f"module {__name__!r} has no attribute {name!r}")

def __dir__():
    # include extension attributes in dir()
    try:
        ext = _load_ext()
        return sorted(list(globals().keys()) + [a for a in dir(ext) if not a.startswith("__")])
    except Exception:
        return sorted(list(globals().keys()))

# Expose extension symbols to tools like pdoc by populating __all__.
# If the extension cannot be imported at import-time, fall back to a minimal export list.
try:
    _ext = _load_ext()
    _ext_names = [n for n in dir(_ext) if not n.startswith("_")]
except Exception:
    _ext_names = []

__all__ = ["__version__", "MODULE_NAME"] + _ext_names
