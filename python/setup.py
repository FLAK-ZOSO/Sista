from setuptools import setup, Extension
import platform

sista_ext = Extension(
    "sista",
    sources=["sistamodule.c"],
    include_dirs=["/usr/local/include", "/usr/include"],
    library_dirs=["/usr/local/lib", "/usr/lib"],
    language="c",
    libraries=["Sista_api"],
    extra_link_args=[
        "-Wl,-rpath,/usr/local/lib",
        "-Wl,-rpath,/usr/lib"
    ] if not platform.platform().lower().startswith("win") else []
)

setup(
    name="sista",
    version="3.0.0",
    ext_modules=[sista_ext],
)
