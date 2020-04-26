This is a implementation of RS485 modbus gateway using an USR-TCP232-304 devices together with a pymodbus library to take remote control of RTU slave devices over rs485 bus

The components are:

1.- Linux Machine how modbus syncronous server i.e. Raspberry pi

2.- The Bus using UTP wire

3.- RS485 Reles

4.- A MQTT instance to send and receive messages by an web application to take remote control
