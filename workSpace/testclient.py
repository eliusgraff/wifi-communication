import socket

HOST = '10.0.0.220'
PORT = 1234

s = socket.socket(socket.AF_INET, socket.SOCKSTREAM)
s.connect((HOST, PORT))

msg = s.recv(1024)
print(msg.decode("utf-8"))
