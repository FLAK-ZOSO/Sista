from setuptools import setup, Extension
import platform

sista_ext = Extension(
    "sista._sista",
    sources=["src/sistamodule.c"],
    include_dirs=["/usr/local/include", "/usr/include"],
    library_dirs=["/usr/local/lib", "/usr/lib"],
    language="c",
    libraries=["Sista_api"],
    extra_link_args=[
        "-Wl,-rpath,/usr/local/lib",
        "-Wl,-rpath,/usr/lib"
    ] if not platform.platform().lower().startswith("win") else []
)

# Only provide build-time things here (extensions). Project metadata lives in pyproject.toml
setup(
    ext_modules=[sista_ext],
)
