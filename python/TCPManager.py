import socket, os, signal
from multiprocessing import Process, Queue

TIMEOUT = 30
BUFFER_SIZE = 65536

class TCPManager:
    def __init__(self, ip, srcp):

        # Local connection server settings
        self.ip = ip
        self.src_port = srcp

        self.egress = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.ingress = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.ingress.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.ingress.bind(('localhost', srcp))
        self.ingress.listen()

        self.queue = Queue()
        self.peers = {}
        self.id = 0
        self.proc = None

    def send_bytes(self, peer, msg):
        self.egress.connect((self.peers[peer]['ip'], self.peers[peer]['port']))
        self.egress.sendall(msg)
        self.egress.close()

    def listen(self):

        if self.proc is not None:
            os.kill(self.proc.pid, signal.SIGTERM)
        ip_dict = {}
        for key in self.peers.keys():
            ip_dict[self.peers[key]['ip']] = key
        self.proc = Process(target=__listen__, args=(self.ingress,
                                                          self.queue,
                                                          ip_dict))
        # self.proc.daemon = True
        self.proc.start()
        return self.proc.pid

    def add_connection(self, ip, port):
        self.id += 1
        self.peers[self.id] = {'ip': ip, 'port': port}
        return self.id

    def get_peers(self):
        return self.peers

    def get_queue(self):
        return self.queue

    def __del__(self):
        self.ingress.shutdown(socket.SHUT_RDWR)
        self.ingress.close()
        print(self.proc.pid)
        os.kill(self.proc.pid, signal.SIGTERM)


def __listen__(sock, queue, ids):
    while True:
        conn, addr = sock.accept()
        conn.setblocking(False)

        data = bytearray()
        tmp = None
        while tmp is None or len(tmp) == BUFFER_SIZE:
            tmp = conn.recv(BUFFER_SIZE)
            data.extend(tmp)
        conn.close()
        queue.put((ids[addr[0]], data))
