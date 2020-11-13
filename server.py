#SERVER SCRIPT
import socket
#from gpiozero import PWMLED, MCP3008
from time import sleep

HOST = '10.0.0.129'
PORT = 1234
print(HOST)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST,PORT))
s.listen(4)

while True:
	clientsocket, address = s.accept()
	print("connection from", address, " has been established!")
	clientsocket.send("welcome to the server")
