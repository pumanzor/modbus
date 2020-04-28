This is a implementation of RS485 modbus gateway using an USR-TCP232-304 device together with a pymodbus library to take remote control of RTU slave devices over rs485 bus

The components are:

1.- Linux Machine acting as modbus syncronous client i.e. Raspberry pi and pymodbus (Ethernet side)

2.- The Bus using UTP wire (RS485 side)

3.- RS485 Reles

4.- The USR-TCP232-304 gateway to interfacing between Ethernet world and rs485 bus

To achieve this on Raspberry pi you must to install pymodbus library

#### pip install pymodbus


then use this diagram to connect your USR-TCP-232 , RS485 Rele and your Linux machine



and use this code snipet to switch the channel 1 of rele to ON

```

#!/usr/bin/env python

from pymodbus.client.sync import ModbusTcpClient as ModbusClient
from pymodbus.transaction import ModbusRtuFramer

import pymodbus
import serial
from pymodbus.pdu import ModbusRequest

import logging
FORMAT = ('%(asctime)-15s %(threadName)-15s '
          '%(levelname)-8s %(module)-15s:%(lineno)-8s %(message)s')
logging.basicConfig(format=FORMAT)
log = logging.getLogger()
log.setLevel(logging.DEBUG)

import paho.mqtt.client as mqtt
import paho.mqtt.publish as publish
import json, time
import inspect


client1 = ModbusClient('192.168.1.10', port=502, framer=ModbusRtuFramer)
client1.connect()


rq = client1.write_register(1, 256, unit=3)
rr = client1.read_holding_registers(1, 1, unit=3)
dassert(rq, lambda r: r.function_code < 0x80)
status = rr.registers[0]
print(status)
```


then copy this snipet code in your Linux or raspberry machine where you installed pymodbus

```
#!/usr/bin/env python

from pymodbus.client.sync import ModbusTcpClient as ModbusClient
from pymodbus.transaction import ModbusRtuFramer

import pymodbus
import serial
from pymodbus.pdu import ModbusRequest

import logging
FORMAT = ('%(asctime)-15s %(threadName)-15s '
          '%(levelname)-8s %(module)-15s:%(lineno)-8s %(message)s')
logging.basicConfig(format=FORMAT)
log = logging.getLogger()
log.setLevel(logging.DEBUG)

import json, time
import inspect

client1 = ModbusClient('192.168.1.10', port=502, framer=ModbusRtuFramer)
client1.connect()

#client1.read_holding_registers(A, B , unit=C)
#where A=Address of register(s), B=register number, unit=slave id

rr0 = client1.read_holding_registers(1,1 , unit=1)
print(rr0.registers)

```
