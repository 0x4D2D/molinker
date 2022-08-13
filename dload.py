from ctypes import *

linker = cdll.LoadLibrary("path to dll")
linker.picture() # take a picture