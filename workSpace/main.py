import socket

HOST = '10.0.0.220'
PORT = 123

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

while True:
  msg = s.recv(1024)
  print(msg.decode("utf-8"))


