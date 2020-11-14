#client script
import socket
import pickle

#HOST = '10.0.0.129' 	#	this will need to be adjusted for server's ip address
HOST = socket.gethostname()
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
        msg = s.recv(16)
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
            new_msg = True
            full_msg = b''

