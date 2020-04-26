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
