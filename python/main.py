#!/usr/bin/python3

import NTRU as ntru
import sys, os, random, time
from NTRU import *

num = 167

if len(sys.argv) == 2 and sys.argv[1] == 'decrypt':
    dec = NTRU(num, ntru.DEC)
    key = dec.getKey()
    fk = open('key.txt', 'wb')
    fk.write(bytes(key))
    fk.close()

    while True:
        try:
            fo = open('emes.txt', 'rb')
            fw = open('output.txt', 'wb')

            s = bytearray(fo.read(num * 8))
            while len(s) != 2:
                txt = dec.action(s)
                fw.write(bytes(txt))
                s = bytearray(fo.read(num * 8))

            count = s[0] + s[1] * 256
            fw.truncate(fw.tell() - count)
            fw.close()
            fo.close()
            os.remove('emes.txt')
            print("decrypted")
        except KeyboardInterrupt:
            del dec
        except FileNotFoundError:
            time.sleep(1)

elif len(sys.argv) == 2 and sys.argv[1] == 'encrypt':
    fk = open('key.txt', 'rb')
    key = bytearray(fk.read())
    enc = NTRU(num, ntru.ENC, key=key)
    fk.close()

    fo = open('input.txt', 'rb')
    fw = open('emest.txt', 'wb')

    s = bytearray(fo.read(num))
    count = 0
    random.seed(time.time())
    while len(s) != 0:
        while len(s) != num:
            s.append(random.randint(0,255))
            count += 1
        txt = enc.action(s)
        fw.write(bytes(txt))
        s = bytearray(fo.read(num))
    s = bytearray(2)
    s[0] = count % 256
    s[1] = count // 256
    fw.write(bytes(s))
    fw.close()
    fo.close()
    os.rename('emest.txt', 'emes.txt')

