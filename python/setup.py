from setuptools import setup, Extension
import ctypes.util
import os

def find_shared_lib(basename, search_dirs=None):
    # Try ctypes.find_library first (may return a basename like "libSista_api.so.3")
    found = ctypes.util.find_library(basename)
    cand_names = []
    if found:
        cand_names.append(found)
    # common soname forms
    cand_names += [f"lib{basename}.so", f"lib{basename}.so.*", f"lib{basename}.so.3"]
    if search_dirs is None:
        search_dirs = ["..", "../lib", "/usr/local/lib", "/usr/lib", "/lib"]
    for d in search_dirs:
        for name in cand_names:
            # glob-like matching for versioned sonames
            if "*" in name:
                import glob
                for p in glob.glob(os.path.join(d, name)):
                    return os.path.abspath(p)
            p = os.path.join(d, name)
            if os.path.exists(p):
                return os.path.abspath(p)
    return None

lib_path = find_shared_lib("Sista_api", search_dirs=["..", "../lib", "/usr/local/lib", "/usr/lib", "/lib"])
extra_objects = [lib_path] if lib_path else []

sista_ext = Extension(
    "sista",
    sources=["sistamodule.c"],
    include_dirs=["..", "../include", "/usr/local/include", "/usr/include"],
    library_dirs=["..", "../lib", "/usr/local/lib", "/usr/lib"],
    language="c",  # wrapper is C; runtime should load libSista via libSista_api
    # don't rely on -l lookup; give the linker the actual shared object so DT_NEEDED records the soname
    extra_objects=extra_objects,
    extra_link_args=[
        "-Wl,-rpath,/usr/local/lib",
        "-Wl,-rpath,/usr/lib",
    ]
)

setup(
    name="sista",
    version="3.0.0",
    ext_modules=[sista_ext],
)
