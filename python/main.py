#!/usr/bin/python3

import NTRU as ntru
import TCPManager

num = 167

port = 60006

m = TCPManager.TCPManager('127.0.0.1', port)
id = m.add_connection('127.0.0.1', port)
m.listen()

m.send_bytes(id, bytearray("hoho", "UTF-8"))

res = m.get_queue().get()

print(res)

del(m)

