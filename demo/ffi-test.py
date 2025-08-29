#!/usr/bin/env python3
import ctypes, ctypes.util
import platform
import time
import os

match platform.system():
    case "Linux":
        sista_api_lib_path = ctypes.util.find_library("Sista_api")
        ctypes.cdll.LoadLibrary(sista_api_lib_path)
        sista_api = ctypes.CDLL(sista_api_lib_path)
    case "Darwin":
        sista_api_lib_path = ctypes.util.find_library("Sista_api")
        ctypes.cdll.LoadLibrary(sista_api_lib_path)
        sista_api = ctypes.CDLL(sista_api_lib_path)
    case "Windows":
        print(os.environ["PATH"])
        sista_lib_path = ctypes.util.find_library("Sista")
        ctypes.windll.LoadLibrary(sista_lib_path)
        sista = ctypes.WinDLL(sista_lib_path)
        sista_api_lib_path = ctypes.util.find_library("Sista_api")
        ctypes.windll.LoadLibrary(sista_api_lib_path)
        sista_api = ctypes.WinDLL(sista_api_lib_path)

match platform.system():
    case "Windows":
        libc_path = ctypes.util.find_library("msvcrt")
        ctypes.windll.LoadLibrary(libc_path)
        libc = ctypes.WinDLL(libc_path)
    case "Darwin" | "Linux":
        libc_path = ctypes.util.find_library("c")
        ctypes.cdll.LoadLibrary(libc_path)
        libc = ctypes.CDLL(libc_path)

sista_api.sista_setForegroundColor.argtypes = [ctypes.c_int]
sista_api.sista_setForegroundColor.restype = None

class sista_SwappableField(ctypes.Structure):
    ...

sista_api.sista_createSwappableField.argtypes = [
    ctypes.c_size_t, ctypes.c_size_t
]
sista_api.sista_createSwappableField.restype = ctypes.POINTER(
    sista_SwappableField
)
field = sista_api.sista_createSwappableField(
    ctypes.c_size_t(42),
    ctypes.c_size_t(42//2)
)
libc.puts(str(field).encode())
time.sleep(2)
if (field != ctypes.c_size_t(0)):
    sista_api.sista_printField(field, ctypes.c_char(b'#'))

time.sleep(2)
sista_api.sista_destroySwappableField(field)

sista_api.sista_setForegroundColor(31)
libc.puts(b"This text is in red, foreground color number 31 for ANSI")
sista_api.sista_resetAnsi()
libc.puts(b"This text instead is in the default ANSI style settings")
time.sleep(1)
