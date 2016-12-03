import ctypes as c

ENC = 1
DEC = 2


class NTRU:
    def __init__(self, num, mode, **kwargs):
        self.__num = num
        self.__lib = c.cdll.LoadLibrary("libntru.so.1")

        if mode == ENC:
            self.__id = self.__lib.sessionEncInit(num, c.c_char_p(bytes(kwargs['key'])))
            self.__close = self.__lib.sessionEncClose
            self.__act = self.__lib.encrypt
            self.__mul = 8
        elif mode == DEC:
            self.__id = self.__lib.sessionDecInit(num)
            self.__close = self.__lib.sessionDecClose
            self.__act = self.__lib.decrypt
            self.__mul = 1
        else:
            raise SyntaxError("No such mode")

        self.__act.restype = c.c_void_p
        self.__act.argtypes = [c.c_char_p, c.c_void_p]

        self.__getkey = self.__lib.getPublicKey
        self.__getkey.restype = c.c_void_p
        self.__getkey.argtypes = [c.c_void_p]

        self.__ptrdel = self.__lib.ptrdel
        self.__ptrdel.argtypes = [c.c_void_p]

    def getKey(self):
        tkey = self.__getkey(self.__id)
        key = bytes(bytearray(self.__num * 8))
        c.memmove(c.c_char_p(key), tkey, self.__num * 8)
        self.__ptrdel(c.cast(tkey, c.POINTER(c.c_void_p)))
        return bytearray(key)

    def action(self, data):
        tres = self.__act(c.c_char_p(bytes(data)), self.__id)
        res = bytes(bytearray(self.__num * self.__mul))
        c.memmove(c.c_char_p(res), tres, self.__num * self.__mul)
        self.__ptrdel(c.cast(tres, c.POINTER(c.c_void_p)))
        return bytearray(res)

    def __del__(self):
        self.__close(c.cast(self.__id, c.POINTER(c.c_void_p)))
