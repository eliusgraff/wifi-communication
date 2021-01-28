
#SERVER SCRIPT
import socket
import struct
from gpiozero import PWMLED, MCP3008
from time import sleep
import pickle

HOST = '192.168.14.92'	#	use ifconfig -a to get local and global IP addresss --- used hostname -I for school IP
#HOST = socket.gethostname()
PORT = 55555
HEADERSIZE = 3
print("hosting on ", HOST)

myServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
myServer.bind((HOST,PORT))
myServer.listen(1)

address = False


client, address = myServer.accept()
print("connection from", address, " has been established!")

msg = "Welcome to Dynamic Securities TEST server!"
msg = f'{len(msg):<{HEADERSIZE}}'+ msg
client.send(bytes(msg,"utf-8"))

msgnum = 0

while True:
    sleep(0.5)
    
    teststring = ("Sending msg ", msgnum += 1)

    msg = pickle.dumps (teststring)
    
    msg = bytes(f'{len(msg):<{HEADERSIZE}}', "utf-8") + msg
    client.send(msg)

