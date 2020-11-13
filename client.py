#client script
import socket

HOST = '10.0.0.129' 	#	this will need to be adjusted for server's ip address
PORT = 12345
HEADERSIZE = 10

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST,PORT))

while True:
    full_msg = ''
    new_msg = True
    while True:
        msg = s.recv(16)
        if new_msg:
            #print(f"new message length: {msg[:HEADERSIZE]}")
            msglen = int(msg[:HEADERSIZE])
            new_msg = False

        full_msg += msg.decode("utf-8")

        if len(full_msg)-HEADERSIZE == msglen:
            #print("full message recieved:")
            yval = full_msg[HEADERSIZE:]
            print(full_msg[HEADERSIZE:])
            new_msg = True
            full_msg = ''

            msg = s.recv(16)
        if new_msg:
            #print(f"new message length: {msg[:HEADERSIZE]}")
            msglen = int(msg[:HEADERSIZE])
            new_msg = False

        full_msg += msg.decode("utf-8")

        if len(full_msg)-HEADERSIZE == msglen:
            #print("full message recieved:")
            xval = full_msg[HEADERSIZE:]
            print(full_msg[HEADERSIZE:])
            new_msg = True
            full_msg = ''

        print("x value:", xval, "  y value:", yval)

    print(full_msg)
    print(msg)
