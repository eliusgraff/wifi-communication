import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('',1234))
s.listen(5)

while True:
  clientsocket, address = s.accept()
  print("connection from ", address," has been established!")
  clientsocket.send(bytes("Welcome to Dynamic Securities Server!", "utf-8"))
