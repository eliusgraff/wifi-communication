import socket

HOST = '192.168.14.92'
PORT = 1234

s = socket.socket(socket.AF_INET, socket.SOCKSTREAM)
s.connect((HOST, 1234))

msg = s.recv(1024)
print(msg.decode("utf-8"))
