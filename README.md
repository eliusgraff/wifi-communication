Elius Graff
Dynamic Securities
Seattle Pacific University

This repo contains both the client and server scripts for the Bird's Eye secutiry camera

# 1.2 #

Server script:
Sets up socket on hard-coded port with IP address given to Pi by local network 
Listens for connection once that socket is opened (currently can only make 1 connection)
A 3-byte header is used to tell client how much data is being sent, this could be changed to accomodate larger variable-length 
messages (not necessary for current implementation)
Reads X and Y joystick data from 3008 chip with PRI class
Pickles the X,Y touple before sending data to client with UTF-8 bytes

Client script:
Sets up socket and tries to connect to hard-coded IP/port combo (should be the same as used to set up server socket)
Once conection is made, recieves 50 byte welcome message
In while loop, listens for 24 byte messages plus the size of message headers (again, header size should be consistent with 
server script). 
*NOTE* Since the 2-value folating point touples are always exactly 24 bytes, the client recieves exactly the 
size of each structure sent, this makes processing a little less complicated. This could be changed to accomodate a variable 
length message though. 
When full message is recieved (this check is for addition of varibale-length messages later on down the road if we want/need to) 
the bytes are un-pickled and sent to the LightLed function.
The LightLed function represents the data sent as directions that motors would be controlled to move to once connected. LEDs are
driven by the PWMLED class from gpiozero library.
After LightLed function is called, the message flags/variables are cleared and begins listening for the next message.

