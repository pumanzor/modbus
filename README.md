##Modbus Protocol

###Introduccion

  Modbus es un protocolo de solicitud-respuesta implementado usando una relación maestro-esclavo. En una relación maestro-esclavo, la comunicación siempre se produce en pares, un dispositivo debe iniciar una solicitud y luego esperar una respuesta y el dispositivo de inicio (el maestro) es responsable de iniciar cada interacción. 
  
  Por lo general, el maestro es una interfaz humano-máquina (HMI) o sistema SCADA y el esclavo es un sensor, un dispositivo RTU, controlador lógico programable (PLC) o controlador de automatización programable (PAC). El contenido de estas solicitudes y respuestas, y las capas de la red a través de las cuales se envían estos mensajes, son definidas por las diferentes capas del protocolo.

##Abreviaciones

- ADU Application Data Unit
- PDU Protocol Data Unit
- MBAP MODBUS Application Protocol
- HMI Human Machine Interface
- MAC Media Access Control
- MB MODBUS Protocol
- PLC Programmable Logic Controller


##Capas del Protocolo Modbus

  En la implementación inicial, Modbus era un solo protocolo construido en base a lineas seriales, por lo que no podía ser dividida en múltiples capas. Con el tiempo, diferentes unidades de datos de aplicación fueron introducidas ya sea para cambiar el formato del paquete utilizado a través de las lineas seriales o para permitir el uso de redes TCP/IP y UDP. 

  Esto llevó a una separación del protocolo principal, el cual define la unidad de datos de protocolo (PDU) y la capa de red que define la unidad de datos de aplicación (ADU).

###Protocolo

El protocolo Modbus se usa principalmente sobre dos tipos de comunicaciones:

- Modbus sobre lineas seriales
- Modbus sobre TCP/IP

En la especificación del protocolo están definidos dos modos de transmisión: ASCII y RTU. Los modos definen la forma como son transmitidos los bytes del mensaje. No es posible utilizar los dos modos de transmisión en la misma red.

##Modbus sobre lineas seriales

Modbus sobre lineas seriales opera en el nivel 2 del modelo OSI. A nivel fisico puede ser implementado en diferentes interfaces tales como TIA/EIA RS485, RS232, RS422. Interfaces de 2 lineas son las mas utilizadas para este protocolo.

La siguiente imagen muestra una representacion general del stack Modbus sobre lineas seriales comparado con el modelo OSI.

![alt tag](https://github.com/pumanzor/modbus/blob/master/img/mbus1.png)

> El protocolo de mensajería de capa de aplicación Modbus (MODBUS application layer messaging protocol) que se encuentra posicionado en el nivel 7 del modelo OSI, proporciona una comunicación cliente / servidor entre los dispositivos conectados en los buses o redes. 

> En Modbus sobre líneas seriales el rol de cliente es proporcionada por el maestro y los nodos esclavos actúan como servidores.

###Principio de funcionamiento

El principio Maestro/Esclavo tiene las siguientes caracteristicas:

- Solo 1 master puede ser conectado en la red
- Uno o mas slaves pueden ser conectados al mismo tiempo en la red.
- Solo y unicamente el master puede iniciar la comunicacion, ejemplo envio de requests a los slaves
- En una comunicacion modbus, el maestro sólo puede iniciar una transacción de forma simultánea.
- El Esclavo solo puede responder requests que provienen desde el maestro.
- A los esclavos no se les permite iniciar la comunicación con el maestro o con cualquier otro esclavo.
- En una comunicacion Modbus los esclavos generan un mensaje de error y lo envían como respuesta al maestro si se ha producido un error en la recepción de un mensaje o si el esclavo no puede realizar la acción solicitada.

El nodo maestro emite una petición MODBUS a los nodos esclavos en dos modos:

  * Modo unicast, el maestro se dirige a un esclavo individualmente. Después de recibir y procesar la petición, el esclavo devuelve un mensaje (una "respuesta") hacia el maestro.
    * En este modo, una transacción MODBUS consta de 2 mensajes: un request desde el maestro y una respuesta desde el esclavo.
    * Cada nodo esclavo debe tener un direccion unica (desde 1 a 247).
  
  * Modo Broadcast, el maestro puede enviar una petición (request) a todos los esclavos del bus.
    * En este modo, los esclavos no enviaran un mensaje de respuesta al maestro, basicamente el modo broadcast se utiliza para enviar mensajes de escritura a los nodos. 
    * Todos los nodos y dispositivos del bus o red deben aceptar el mensaje de broadcastm, en este caso una funcion de escritura.
    * La direccion utilizada para tal accion en el campo address field del mensaje que se despacha desde el Maestro es la direccion 0
  
![alt tag](https://github.com/pumanzor/modbus/blob/master/img/mbusmode.png)

##Reglas de direccionamiento en Modbus

El espacio de direccionamiento en modbus es de 256 direcciones diferentes.

![alt tag](https://github.com/pumanzor/modbus/blob/master/img/addrmodbus.png)

La direccion 0 esta reservada para el broadcast y todos los esclavos deben reconocerla.

el Nodo Master no tiene una direccion especifica, solo los nodos esclavos deben poser una direccion la cual debe ser unica dentro del bus serial Modbus. 

##MODBUS frame description 

El protocolo MODBUS define un protocolo data unit (PDU) independiente de las capas de comunicación subyacentes. El mapeo del protocolo MODBUS en redes específicos puede introducir algunos campos adicionales application data unit (ADU).


![alt tag](https://github.com/pumanzor/modbus/blob/master/img/modbuspdu.png)


Campo Address Field.

El campo de direccion de un frame modbus contiene 2 caracteres (ASCII) o 8 bits (RTU). 

En un sub-controller slave las direcciones validas van en el rango de 1 a 247.

Cuando un Maestro envia un mensaje hacia un esclavo, el frame que proviene desde el maestro debe incluir en el campo "Address Field" el ID del esclavo.

Cuando el Esclavo Recibe el request, enviara la respuesta de vuelta al maestro y pone en el campo Address Field su propio ID.
