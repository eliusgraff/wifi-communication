#client script
import socket
import pickle
#import sys
#import os


HOST = '10.0.0.129' 	#	this will need to be adjusted for server's ip address
#HOST = socket.gethostname()
PORT = 12345
HEADERSIZE = 3

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST,PORT))
msg = s.recv(50)
print (msg.decode("utf-8")[HEADERSIZE:])

while True:
    full_msg = b''
    new_msg = True

    while True:
        msg = s.recv(24 + HEADERSIZE)
        #print ("recieved msg: ", msg)

        if new_msg:
            msglen = int(msg[:HEADERSIZE])
            #print ("new msg ", msglen, " long")
            new_msg = False

        full_msg += msg

        #print (len(full_msg)-HEADERSIZE, " compare to ", msglen)

        if len(full_msg)-HEADERSIZE == msglen:
            joystick = pickle.loads(full_msg[HEADERSIZE:])
            print(joystick)
            #os.system('cls' if os.name == 'nt' else 'clear')
            new_msg = True
            full_msg = b''

        elif len(full_msg) - HEADERSIZE > msglen:
            #print("dropping message, overflow")
            #exit()
            new_msg = True
            full_msg = b''
