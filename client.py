#client script
import socket

HOST = '10.0.0.129'
PORT = 1234

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST,PORT))

msg = s.recv(8)
print(msg.decode("utf-8")
