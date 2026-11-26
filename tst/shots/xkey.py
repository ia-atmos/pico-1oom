# xkey.py KEY...: send key presses to the X display with XTest (keysym names, e.g. Return, Escape, F2, a)
import ctypes, sys, time
x = ctypes.CDLL("libX11.so.6"); t = ctypes.CDLL("libXtst.so.6")
x.XOpenDisplay.restype = ctypes.c_void_p
x.XStringToKeysym.restype = ctypes.c_ulong
d = ctypes.c_void_p(x.XOpenDisplay(None))
for k in sys.argv[1:]:
    kc = x.XKeysymToKeycode(d, ctypes.c_ulong(x.XStringToKeysym(k.encode())))
    t.XTestFakeKeyEvent(d, kc, 1, 0); x.XFlush(d); time.sleep(0.1)
    t.XTestFakeKeyEvent(d, kc, 0, 0); x.XFlush(d); time.sleep(0.4)
x.XCloseDisplay(d)
