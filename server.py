#SERVER SCRIPT
import socket
from gpiozero import PWMLED, MCP3008
from time import sleep

yinput = MCP3008(0)
xinput = MCP3008(1)
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
<<<<<<< HEAD

	while True:
		msg = yinput.value
		#if msg == "break":
		#	break

		msg = f'{len(msg):<{HEADERSIZE}}'+msg
		client.send(bytes(msg, "utf-8"))

		msg = xinput.value
		
		msg = f'{len(msg):<{HEADERSIZE}}'+msg
		client.send(bytes(msg, "utf-8"))


		sleep(0.05)

	print("connection with ", address, " closed")
	client.close()
	msg = input("enter y to listen again or n to close server: ")
	if msg == 'n':
		break
=======
>>>>>>> parent of b527534... Set up stream
