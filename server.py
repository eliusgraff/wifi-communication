#SERVER SCRIPT
import socket

HOST = socket.gethostname()
PORT = 1234
HEADERSIZE = 10
print("hosting on ", HOST)

myServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
myServer.bind((HOST,PORT))
myServer.listen(1)

address = False

while True:
	client, address = myServer.accept()
	print("connection from", address, " has been established!")

	msg = "Welcome to Dynamic Securities server!"
	msg = f'{len(msg):<{HEADERSIZE}}'+msg
	client.send(bytes(msg,"utf-8"))
