# Xillybusでデータをやり取りするためのPython関数たち
import os

class Xillybus32:
    def __init__(self, dev_path_w='/dev/xillybus_write_32', dev_path_r='/dev/xillybus_read_32'):
        self.fd_w = os.open(dev_path_w, os.O_WRONLY)
        self.fd_r = os.open(dev_path_r, os.O_RDONLY)

    def write(self, data):
        bytes_w = data.to_bytes(4, 'little')
        os.write(self.fd_w, bytes_w)

    def read(self):
        byte_r = os.read(self.fd_r, 4)
        return int.from_bytes(byte_r, 'little')

class Xillybus8:
    def __init__(self, dev_path_w='/dev/xillybus_write_8', dev_path_r='/dev/xillybus_read_8'):
        self.fd_w = os.open(dev_path_w, os.O_WRONLY)
        self.fd_r = os.open(dev_path_r, os.O_RDONLY)

    def write(self, data):
        bytes_w = data.to_bytes(1, 'little')
        os.write(self.fd_w, bytes_w)

    def read(self):
        byte_r = os.read(self.fd_r, 1)
        return int.from_bytes(byte_r, 'little')