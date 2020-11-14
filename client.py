#client script
import socket

#HOST = '10.0.0.129' 	#	this will need to be adjusted for server's ip address
HOST = socket.gethostname()
PORT = 1234
HEADERSIZE = 3

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST,PORT))

while True:
    full_msg = ''
    new_msg = True

    while True:
        msg = s.recv(16)
        #print ("recieved msg: ", msg)

        if new_msg:
            msglen = int(msg[:HEADERSIZE])
            #print ("new msg ", msglen, " long")
            new_msg = False

        full_msg += msg.decode("utf-8")
        #print (len(full_msg)-HEADERSIZE, " compare to ", msglen)

        if len(full_msg)-HEADERSIZE == msglen:
            print (full_msg[HEADERSIZE:])
            new_msg = True
            full_msg = ''

