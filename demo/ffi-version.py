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

sista_api.sista_getVersion.argtypes = []
sista_api.sista_getVersion.restype = ctypes.c_char_p

print(sista_api.sista_getVersion())
