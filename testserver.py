#Testing SERVER SCRIPT
import socket
import time

HOST = '10.0.0.220'
PORT = 1235

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST,PORT))
s.listen(5)

print("hosting on ", HOST)
clientsocket, address = s.accept()
print("connection from ", address," has been established!")
clientsocket.send(bytes("Welcome to Dynamic Securities Server!", "utf-8"))

mycount = 0

while True:
    clientsocket.send(bytes(str(mycount), 'utf-8'))
    mycount += 1
    time.sleep(1)