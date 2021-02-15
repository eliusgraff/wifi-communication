import socket

HOST = '127.0.0.1'
PORT = 8888

print("trying to connect")

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

while True:
  msg = s.recv(1024)
  print(msg.decode("utf-8"))
