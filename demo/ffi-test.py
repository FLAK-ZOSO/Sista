#!/usr/bin/env python3
import ctypes
import time

try:
    ctypes.cdll.LoadLibrary('libSista_api.so')
    sista_api = ctypes.CDLL('libSista_api.so')
except OSError | FileNotFoundError:
    try:
        ctypes.cdll.LoadLibrary('libSista_api.dylib')
        sista_api = ctypes.CDLL('libSista_api.dylib')
    except OSError | FileNotFoundError:
        ctypes.cdll.LoadLibrary('libSista_api.dll')
        sista_api = ctypes.CDLL('libSista_api.dll')

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
print(field)
time.sleep(2)
if (field != ctypes.c_size_t(0)):
    sista_api.sista_printField(field, ctypes.c_char(b'#'))

time.sleep(2)
sista_api.sista_destroySwappableField(field)
