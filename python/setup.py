from setuptools import setup, Extension
import ctypes.util
import os

sista_ext = Extension(
    "sista",
    sources=["sistamodule.c"],
    include_dirs=["/usr/local/include", "/usr/include"],
    library_dirs=["/usr/local/lib", "/usr/lib"],
    language="c",  # wrapper is C; runtime should load libSista via libSista_api
    # don't rely on -l lookup; give the linker the actual shared object so DT_NEEDED records the soname
    extra_objects=["/usr/lib/libSista_api.so"],
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
