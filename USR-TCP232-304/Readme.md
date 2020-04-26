This is a implementation of RS485 modbus gateway using an USR-TCP232-304 device together with a pymodbus library to take remote control of RTU slave devices over rs485 bus

The components are:

1.- Linux Machine acting as modbus syncronous client i.e. Raspberry pi and pymodbus (Ethernet side)

2.- The Bus using UTP wire (RS485 side)

3.- RS485 Reles

4.- The USR-TCP232-304 gateway to interfacing between Ethernet world and rs485 bus

To achieve this on Raspberry pi you must to install pymodbus library

''pip install pymodbus''


