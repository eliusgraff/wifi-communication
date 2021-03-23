Elius Graff
Dynamic Securities
Seattle Pacific University

This repo contains both the client and server scripts for the Bird's Eye secutiry camera

# 2.2 #

The original client and server scripts have been kept for potential future use. While using the Pies as a access point and station, I ran into some
issues that I couldn't easily solve. This latest commit indicates most recent pivot away from the Raspberry Pies and toward the ESP8266 modules.


ESP Server:
Rather than using sockets, the ESPs have a 'esp-now' feature which will be how the server will be communicating with the motor controllers. The server
sets itself up as the master for the ESP-Now connection and waits for another ESP module with the hard-coded MAC address to connect wih it. Once that
connection is established, the server sends that secondary device the user-input data it reads from a MCP3008 chip (connected to a joystick).

Future development involves adding 2 more secondary devices for the user-input to control motors in various parts of the project. This will also 
involve adding another joystick to the UI.

ESP Client:
Each client is meant to be placed along the x/y axes of the suspension system. Based on which spot the processor is at, it will be programmed to read
the correct value from the user-input object sent to it. The user-input value will be processed and apropriate motor control signals will be sent to 
drive the motors used for moving the cross beam/trolley around. Presently they are both 12V dc motors but one of those might be replaced.
