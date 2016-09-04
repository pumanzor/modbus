#!/usr/bin/env python
from pymodbus.client.sync import ModbusTcpClient as ModbusClient
from pymodbus.transaction import ModbusRtuFramer
import sys 
import collections
import textwrap
from optparse import OptionParser
from pymodbus.utilities import computeCRC, computeLRC
from pymodbus.factory import ClientDecoder, ServerDecoder
from pymodbus.transaction import ModbusSocketFramer
from pymodbus.transaction import ModbusBinaryFramer
from pymodbus.transaction import ModbusAsciiFramer


from pymodbus.diag_message import *
from pymodbus.file_message import *
from pymodbus.other_message import *
from pymodbus.mei_message import *



import paho.mqtt.client as mqtt
import paho.mqtt.publish as publish
import json, time
import inspect

client1 = ModbusClient('fatek_ip_address', port=502)
client1.connect()

client2 = ModbusClient('fatek_ip_address', port=502)
client2.connect()



def plcw():
	id1 = float(id) 
	rq = client1.write_registers(200,[id1], unit=1)
	print id1



def on_connect(client, userdata, flags, rc):      
        print("Connected with result code "+str(rc))
        client.subscribe("/uach/data/control/#")                   
        publish_mqtt("11")         
                                                    
def on_message(client, userdata, msg):              
        print("recieved: "+msg.topic+""+str(msg.payload))
        words = msg.payload.split(',') 
	global id           
	id = words[0]
	plcw()  
                                                          
def publish_mqtt(payload):                                
    topic = '/plc1'                                       
    try:                                                  
        publish.single(topic, payload, hostname='broker_ip_address', port=1883, retain=False, qos=0)
    except Exception as err:                                                                     
            print "Couldn't publish :" + str(err)                                                
            pass                                                                                 
                                                                                                 
client = mqtt.Client()                                                                           
client.on_connect = on_connect                                                                   
client.on_message = on_message                                                                   
client.connect("mqtt_broker_ip_address")                                                                 
client.loop_start()       

while True:              
	rr = client2.read_holding_registers(200,1,unit=1)
	rr22 = client2.read_holding_registers(22,1,unit=1)
	rr40 = client2.read_holding_registers(40,1,unit=1)
	rr41 = client2.read_holding_registers(41,1,unit=1)
	rr13 = client2.read_holding_registers(14,1,unit=1)
	rr51 = client2.read_holding_registers(51,1,unit=1)	
	rr61 = client2.read_holding_registers(61,1,unit=1)
	result = rr.registers
	result22 = rr22.registers
	result40 = rr40.registers
	result41 = rr41.registers
	result13 = rr13.registers
	result51 = rr51.registers
	result61 = rr61.registers
	valor = str(result)[1:-1]
	valor22 = str(result22)[1:-1]
	valor40 = str(result40)[1:-1]
	valor41 = str(result41)[1:-1]
	valor13 = str(result13)[1:-1]
	valor51 = str(result51)[1:-1]
	valor61 = str(result61)[1:-1]
	myList = [valor,valor22,valor40,valor41,valor13,valor51,valor61]	
	print valor, valor22 
	str1 = ','.join(myList)
	publish_mqtt(str1)
	time.sleep(1)



client1.close()
client2.close()
