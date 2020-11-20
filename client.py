#client script
import socket
import pickle
from gpiozero import PWMLED
#import sys
#import os

upled = PWMLED(19)
downled = PWMLED(26)
rightled = PWMLED(6)
leftled = PWMLED(13)


def LightLed(joystick):
	print(joystick)
	#left and right movement
	if (joystick[0] < 0.54 and joystick[0] > 0.46): #joystick in middle
		rightled.value = 0
		leftled.value = 0

	elif (joystick[0] < 0.5):			#joystick pointed left
		rightled.value = 0
		leftled.value = (0.5 - joystick[0])

	else:						#joystick pointed right
		rightled.value = (joystick[0] - 0.5)
		leftled.value = 0

	#up and down movement
	if(joystick[1] < 0.54 and joystick[1] > 0.46):	#joystick in middle
		upled.value = 0
		downled.value = 0

	elif(joystick[1] < 0.5):			#joystick pointed up
		upled.value = (0.5 - joystick[1])
		downled.value = 0

	else:						#joystick pointed down
		downled.value = (joystick[1] - 0.5)
		upled.value = 0


HOST = '192.168.15.192' 	#	this will need to be adjusted for server's ip address
#HOST = socket.gethostname()
PORT = 1234
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
            #print(joystick)


            LightLed(joystick) ##

            #os.system('cls' if os.name == 'nt' else 'clear')
            new_msg = True
            full_msg = b''

        elif len(full_msg) - HEADERSIZE > msglen:
            #print("dropping message, overflow")
            #exit()
            new_msg = True
            full_msg = b''
