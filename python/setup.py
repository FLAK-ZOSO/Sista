from setuptools import setup, Extension

sista_ext = Extension(
    "sista",
    sources=["sistamodule.c"],
    include_dirs=["..", "../include", "/usr/local/include"],
    language="c",  # wrapper is C; runtime will load C++ dylib if the dylib references it
    extra_objects=["/usr/local/lib/libSista_api.dylib"],       # absolute path to the dynamic C API library
    extra_link_args=["-Wl,-rpath,/usr/local/lib"],  # ensure loader finds dylibs in /usr/local/lib at runtime
)

setup(
    name="sista",
    version="3.0.0",
    ext_modules=[sista_ext],
)
