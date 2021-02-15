#SERVER SCRIPT
import socket
import struct
from gpiozero import PWMLED, MCP3008
from time import sleep
import pickle

yinput = MCP3008(0)
xinput = MCP3008(1)
HOST = '192.168.14.92'	#	use ifconfig -a to get local and global IP addresss --- used hostname -I for school IP
#HOST = socket.gethostname()
PORT = 1234
HEADERSIZE = 3
print("hosting on ", HOST)

myServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
myServer.bind((HOST,PORT))
myServer.listen(1)

address = False

while True:
	client, address = myServer.accept()
	print("connection from", address, " has been established!")

	msg = "Welcome to Dynamic Securities server!"
	msg = f'{len(msg):<{HEADERSIZE}}'+ msg
	client.send(bytes(msg,"utf-8"))

	while True:
		sleep(0.1)
		joystickpos = (xinput.value, yinput.value)
		msg = pickle.dumps (joystickpos)
		
		msg = bytes(f'{len(msg):<{HEADERSIZE}}', "utf-8") + msg
		client.send(msg)


	print("connection with ", address, " closed")
	client.close()
	msg = input("enter y to listen again or n to close server: ")
	if msg == 'n':
		break
