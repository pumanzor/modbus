##Modbus Protocol

###Introduccion

  Modbus es un protocolo de solicitud-respuesta implementado usando una relación maestro-esclavo. En una relación maestro-esclavo, la comunicación siempre se produce en pares, un dispositivo debe iniciar una solicitud y luego esperar una respuesta y el dispositivo de inicio (el maestro) es responsable de iniciar cada interacción. 
  
  Por lo general, el maestro es una interfaz humano-máquina (HMI) o sistema SCADA y el esclavo es un sensor, un dispositivo RTU, controlador lógico programable (PLC) o controlador de automatización programable (PAC). El contenido de estas solicitudes y respuestas, y las capas de la red a través de las cuales se envían estos mensajes, son definidas por las diferentes capas del protocolo.

##Abreviaciones

- ADU Application Data Unit
- HDLC High level Data Link Control
- HMI Human Machine Interface
- MAC Media Access Control
- MB MODBUS Protocol
- MBAP MODBUS Application Protocol
- PDU Protocol Data Unit
- PLC Programmable Logic Controller

###Protocolo

El protocolo Modbus se usa principalmente sobre dos tipos de comunicaciones:

- Modbus sobre lineas seriales
- Modbus sobre TCP/IP

##Modbus sobre lineas seriales

Modbus sobre lineas seriales opera en el nivel 2 del modelo OSI. A nivel fisico puede ser implementado en diferentes interfaces tales como TIA/EIA RS485, RS232, RS422. Interfaces de 2 lineas son las mas utilizadas para este protocolo.

###Principio de funcionamiento

El principio Maestro/Esclavo tiene las siguientes caracteristicas:

- Solo 1 master puede ser conectado en la red
- Uno o mas slaves pueden ser conectados al mismo tiempo en la red.
- Solo y unicamente el master puede iniciar la comunicacion, ejemplo envio de requests a los slaves
- En una comunicacion modbus, el maestro sólo puede iniciar una transacción de forma simultánea.
- El Esclavo solo puede responder requests que provienen desde el maestro.
- A los esclavos no se les permite iniciar la comunicación con el maestro o con cualquier otro esclavo.
- En una comunicacion Modbus los esclavos generan un mensaje de error y lo envían como respuesta al maestro si se ha producido un error en la recepción de un mensaje o si el esclavo no puede realizar la acción solicitada.




Campo Address Field.

El campo de direccion de un frame modbus contiene 2 caracteres (ASCII) o 8 bits (RTU). En un sub-controller slave
las direcciones validas van en el rango de 1 a 247.

Cuando un Maestro envia un mensaje hacia un esclavo, el frame que proviene desde el maestro debe incluir en el campo "Address Field" el ID del esclavo.

Cuando el Esclavo Recibe el request, enviara la respuesta de vuelta al maestro y pone en el campo Address Field su propio ID.
