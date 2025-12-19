from setuptools import setup, Extension
import ctypes.util
import os
import glob
import sys
from pathlib import Path

def find_shared_lib(name, search_dirs=None):
    """
    Try to locate a linkable file for `name` across platforms.
    Returns absolute path to a single file appropriate for linking (e.g. .so/.dylib/.lib),
    or None if not found.
    """
    if not name:
        return None

    # platform specific candidate suffixes (order = preference)
    if sys.platform == "darwin":
        suffixes = ["", ".dylib", ".dylib.*"]
        prefixes = ["lib", ""]
    elif sys.platform.startswith("win"):
        # prefer import library (.lib) for linker; dll is not a linker input unless you have an import lib
        suffixes = [".lib", ".dll"]
        prefixes = ["", "lib"]
    else:
        suffixes = ["", ".so", ".so.*"]
        prefixes = ["lib", ""]

    # try ctypes.find_library first (may return basename or soname)
    found = ctypes.util.find_library(name)
    candidates = []
    if found:
        candidates.append(found)

    # build candidate patterns
    base = name
    for p in prefixes:
        for s in suffixes:
            candidates.append(f"{p}{base}{s}")

    if search_dirs is None:
        search_dirs = ["..", "../lib", "/usr/local/lib", "/usr/lib", "/lib"]

    # if ctypes returned an absolute path, prefer it
    if found and os.path.isabs(found) and os.path.exists(found):
        return os.path.abspath(found)

    # glob search in dirs
    for d in search_dirs:
        for pattern in candidates:
            # skip empty pattern
            if not pattern:
                continue
            for p in glob.glob(os.path.join(d, pattern)):
                return os.path.abspath(p)
    return None

# try to find a linkable Sista_api file
libsista_api_soname = ctypes.util.find_library("Sista_api")  # may be "libSista_api.so.3" or similar
libsista_api_path = find_shared_lib(libsista_api_soname, search_dirs=["..", "../lib", "/usr/local/lib", "/usr/lib", "/lib"])

# If we found a usable file, pass it via extra_objects (so the .so/.dylib/.lib soname is recorded).
# Otherwise fall back to -lSista_api so the normal linker search will try library_dirs.
extra_objects = [libsista_api_path] if libsista_api_path else []
libraries = [] if libsista_api_path else ["Sista_api"]

# platform rpath/link flags
extra_link_args = []
if sys.platform == "darwin":
    # keep system /usr/local rpath and also allow @loader_path usage if needed
    extra_link_args += ["-Wl,-rpath,/usr/local/lib", "-Wl,-rpath,/usr/lib"]
elif sys.platform.startswith("win"):
    # no rpath concept; nothing to add
    extra_link_args += []
else:
    extra_link_args += ["-Wl,-rpath,/usr/local/lib", "-Wl,-rpath,/usr/lib"]

# Print discovered path during build so build logs show what was picked.
if libsista_api_path:
    print(libsista_api_path)

sista_ext = Extension(
    "sista",
    sources=["sistamodule.c"],
    include_dirs=["..", "../include", "/usr/local/include", "/usr/include"],
    library_dirs=["..", "../lib", "/usr/local/lib", "/usr/lib"],
    language="c",
    extra_objects=extra_objects,
    libraries=libraries,
    extra_link_args=extra_link_args,
)

setup(
    name="sista",
    version="3.0.0",
    ext_modules=[sista_ext],
)
