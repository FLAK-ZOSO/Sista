from setuptools import setup, Extension
import platform

is_windows = platform.system() == "Windows"

sista_ext = Extension(
    "sista._sista",
    sources=["src/sistamodule.c"],
    include_dirs=[
        "/usr/local/include", 
        "/usr/include"
    ] if not is_windows else [
        r"C:\Program Files\Sista\include"
    ],
    library_dirs=[
        "/usr/local/lib", 
        "/usr/lib"
    ] if not is_windows else [
        r"C:\Program Files\Sista\lib"
    ],
    language="c",
    libraries=["Sista_api", "Sista"],
    extra_link_args=[
        "-Wl,-rpath,/usr/local/lib",
        "-Wl,-rpath,/usr/lib",
        "-lstdc++"
    ] if not is_windows else []
)

# Only provide build-time things here (extensions). Project metadata lives in pyproject.toml
setup(
    ext_modules=[sista_ext],
)
