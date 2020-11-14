#SERVER SCRIPT
import socket
import struct
from gpiozero import PWMLED, MCP3008
from time import sleep

yinput = MCP3008(0)
xinput = MCP3008(1)
#HOST = '10.0.0.129'	#	use ifconfig -a to get local and global IP addresss
HOST = socket.gethostname()
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
		sleep(0.5)
		msg = str(xinput.value)
		#print("xval ", msg)
		
		msg = f'{len(msg):<{HEADERSIZE}}' + msg
		#print(msg)
		#print("bytes look like: ", bytes(msg, "utf-8"))
		client.send(bytes(msg, "utf-8"))


	print("connection with ", address, " closed")
	client.close()
	msg = input("enter y to listen again or n to close server: ")
	if msg == 'n':
		break
