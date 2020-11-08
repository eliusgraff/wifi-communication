#SERVER SCRIPT
import socket

HOST = socket.gethostname()
PORT = 12345
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

	while True:
		msg = input("data to send: ")
		if msg == "break":
			break

		msg = f'{len(msg):<{HEADERSIZE}}'+msg
		client.send(bytes(msg, "utf-8"))

	print("connection with ", address, " closed")
	client.close()
	msg = input("enter y to listen again or n to close server: ")
	if msg == 'n':
		break