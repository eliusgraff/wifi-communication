#SERVER SCRIPT
import socket
#from gpiozero import PWMLED, MCP3008
from time import sleep

#yinput = MCP3008(0)
#xinput = MCP3008(1)
HOST = socket.gethostname()
PORT = 1234
HEADERSIZE = 10
print("hosting on ", HOST)

myServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
myServer.bind((HOST,PORT))
myServer.listen(1)

#saddress = False

while True:
	client, address = myServer.accept()
	print("connection from", address, " has been established!")

	msg = "Welcome to Dynamic Securities server!"
	msg = f'{len(msg):<{HEADERSIZE}}'+msg
	client.send(bytes(msg,"utf-8"))

	while True:

		msg = random.random()
		msg = f'{len(msg):<{HEADERSIZE}}' + msg
		client.send(msg)

		sleep(0.1)

'''
	print("connection with ", address, " closed")
	client.close()
	msg = input("enter y to listen again or n to close server: ")
	if msg == 'n':
		break
'''