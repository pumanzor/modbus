## Modbus Protocol

### Introduccion

  Modbus es un protocolo de solicitud-respuesta utilizandoo una relación maestro-esclavo. En una relación maestro-esclavo, la comunicación siempre se produce en pares, un dispositivo debe iniciar una solicitud y luego esperar una respuesta y el dispositivo de inicio (el maestro) es responsable de iniciar cada interacción. 
  
  Por lo general, el maestro es una interfaz humano-máquina (HMI) o sistema SCADA y el esclavo es un sensor, un dispositivo RTU, controlador lógico programable (PLC) o controlador de automatización programable (PAC). El contenido de estas solicitudes y respuestas, y las capas de la red a través de las cuales se envían estos mensajes, son definidas por las diferentes capas del protocolo.

#### Abreviaciones

- ADU Application Data Unit
- PDU Protocol Data Unit
- MBAP MODBUS Application Protocol
- HMI Human Machine Interface
- MAC Media Access Control
- MB MODBUS Protocol
- PLC Programmable Logic Controller


### Capas del Protocolo Modbus

  En la implementación inicial, Modbus era un solo protocolo construido en base a lineas seriales, por lo que no podía ser dividida en múltiples capas. Con el tiempo, diferentes unidades de datos de aplicación fueron introducidas ya sea para cambiar el formato del paquete utilizado a través de las lineas seriales o para permitir el uso de redes TCP/IP y UDP. 

  Esto llevó a una separación del protocolo principal, el cual define la unidad de datos de protocolo (PDU) y la capa de red que define la unidad de datos de aplicación (ADU).

### Protocolo

El protocolo Modbus se usa principalmente sobre dos tipos de comunicaciones:

- Modbus sobre lineas seriales
- Modbus sobre TCP/IP

En la especificación del protocolo están definidos dos modos de transmisión: ASCII y RTU. Los modos definen la forma como son transmitidos los bytes del mensaje. No es posible utilizar los dos modos de transmisión en la misma red.

### Modbus sobre lineas seriales

Modbus sobre lineas seriales opera en el nivel 2 del modelo OSI. A nivel fisico puede ser implementado en diferentes interfaces tales como TIA/EIA RS485, RS232, RS422. Interfaces de 2 lineas son las mas utilizadas para este protocolo.

La siguiente imagen muestra una representacion general del stack Modbus sobre lineas seriales comparado con el modelo OSI.

![alt tag](https://github.com/pumanzor/modbus/blob/master/img/mbus1.png)

> El protocolo de mensajería de capa de aplicación Modbus (MODBUS application layer messaging protocol) que se encuentra posicionado en el nivel 7 del modelo OSI, proporciona una comunicación cliente / servidor entre los dispositivos conectados en los buses o redes. 

> En Modbus sobre líneas seriales el rol de cliente es proporcionada por el maestro y los nodos esclavos actúan como servidores.

### Principio de funcionamiento

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

### Reglas de direccionamiento en Modbus

El espacio de direccionamiento en modbus es de 256 direcciones diferentes.

![alt tag](https://github.com/pumanzor/modbus/blob/master/img/addrmodbus.png)

La direccion 0 esta reservada para el broadcast y todos los esclavos deben reconocerla.

el Nodo Master no tiene una direccion especifica, solo los nodos esclavos deben poser una direccion la cual debe ser unica dentro del bus serial Modbus. 

### MODBUS frame description 

El protocolo MODBUS define un protocolo data unit (PDU) independiente de las capas de comunicación subyacentes. 

El mapeo del protocolo en red tipo bus o en redes especificas introduce algunos campos adicionales en el application data unit (ADU).

![alt tag](https://github.com/pumanzor/modbus/blob/master/img/modbusframe.png)

El ADU es construido por el cliente (Master) que inicia una transaccion MODBUS. la funcion indica al servidor(Slave) que tipo de accion debe realizar. 

El campo function code del frame MODBUS es codificado en 1 byte. Los codigos validos estan en el rango desde 1 al 255 decimal. El rango 128 al 255 esta reservado para respuestas de excepcion). 

Cuando un mensaje es enviado desde un cliente a un servidor el campo function code le dice al servidor que tipo de accion debe realizar. El function code "0" no es valido.

### Códigos de Función Estándares

  La definición de cada código de función estándar está en la especificación. Incluso para los códigos de función más comunes, existen discrepancias inevitables entre las funciones habilitadas en el maestro y lo que el esclavo puede manejar. Para solucionar esto, las versiones anteriores de la especificación Modbus TCP definen tres clases de conformidad. La Especificación de Pruebas de Compatibilidad Modbus oficial no hace referencia a estas clases y en su lugar define la compatibilidad en cada función; sin embargo, puede ser conveniente para comprenderlo. Se recomienda que cualquier documento siga la especificación de pruebas y determine su compatibilidad con los códigos que soportan, en lugar de con las clasificaciones de legado.

#### Códigos Clase 0

  Los códigos Clase 0 generalmente son considerados el mínimo para un dispositivo Modbus útil, ya que dan a un maestro la habilidad de leer o escribir en el modelo de datos.
  
![alt tag](https://github.com/pumanzor/modbus/blob/master/img/cod0.png)

#### Códigos Clase 1

  Los códigos de función Clase 1 consisten en los otros códigos necesarios para tener acceso a todos los tipos del modelo de datos. En la definición original, esta lista incluye el código de función 7 (leer excepción). Sin embargo, este código es definido por la especificación actual como un código para serial únicamente.
  
![alt tag](https://github.com/pumanzor/modbus/blob/master/img/cod1.png)


#### Códigos Clase 2

  Los códigos de función Clase 2 son funciones más especializadas que son implementadas con menos frecuencia. Por ejemplo, Leer/Escribir Múltiples Registros puede ayudar a reducir el número total de ciclos de solicitud-respuesta, pero el comportamiento aún puede ser implementado con códigos Clase 0.
  
![alt tag](https://github.com/pumanzor/modbus/blob/master/img/cod2.png)

#### Interfaz Modbus Encapsulada

  El código de Interfaz Modbus Encapsulada (MEI), función 43, es usado para encapsular otros datos en un paquete Modbus. En la actualidad, dos números MEI están disponibles, 13 (CANopen) y 14 (identificación de dispositivos).

  La Función 43/14 (identificación de dispositivos) es útil, ya que permite la transferencia de hasta 256 objetos únicos. Algunos de estos objetos son predefinidos y reservados, como el nombre del proveedor y el código de producto, pero las aplicaciones pueden definir otros objetos a transferir como conjuntos de datos genéricos.

Este código no es implementado comúnmente.

### Excepciones
  Los esclavos utilizan excepciones para indicar un número de condiciones de error, desde una solicitud malformada hasta entradas incorrectas. Sin embargo, las excepciones también se pueden generar como una respuesta a nivel de la aplicación para una solicitud válida. Los esclavos no responden a las solicitudes emitidas con una excepción. En cambio, el esclavo ignora solicitudes incompletas o alteradas y comienza a esperar un nuevo mensaje entrante.

  Las excepciones son reportadas en un formato de paquete definido. Primero, un código de función se regresa al maestro que solicita igual al código de función original, excepto con su conjunto de bits más significativo. Esto es equivalente a añadir 0x80 al valor del código de función original. En lugar de los datos normales asociados con una respuesta de función determinada, las respuestas de excepción incluyen un solo código de excepción.

  Dentro del estándar, los cuatro códigos de excepción más comunes son 01, 02, 03 y 04. Estos se muestran en la siguiente tabla  con significados estándares para cada función.
  
  
![alt tag](https://github.com/pumanzor/modbus/blob/master/img/codex.png)

#### Data field

El campo data de un mensaje enviado desde el cliente al servidor contiene informacion adicional que el servidor usa para tomar una accion definda en el campo function code. Esto puede incluir items como direcciones de registros, la cantidad de items a ser manejados y otros datos importantes.

Este campo puede ser inexistente (de longitud cero) en ciertos tipos de solicitudes, en este caso el servidor no requiere 
ninguna informacion adicional.

Si no ocurren errores relacionados con la funcion MODBUS requerida en un ADU modbus correctamente recibida el campo  de una respuesta desde el servidor a un cliente; contendra los datos solicitados.

Si ocurre un error relacionado con la función MODBUS solicitada, este campo contiene un código de excepción que la aplicación de servidor puede utilizar para determinar la siguiente acción a tomar.

Por ejemplo un cliente puede leer el estado ON/OFF de un grupo de salidas o entradas discretas o puede leer/escribir el contenido de un grupo de registros. 

Cuando el servidor responde a un cliente, usa el campo function code para indicar una respuesta normal (error-free) o que algun tipo de error ha ocurrido (respuesta de excepción). Para una respuesta normal, el servidor simplemente se hace eco de la solicitud del código de función original.


![alt tag](https://github.com/pumanzor/modbus/blob/master/img/modbusdatafield.png)

El tamaño de la PDU en Modbus está limitado por la restricción de tamaño heredado de la primera aplicación Modbus en redes de línea serial (máx. RS485 ADU = 256 bytes).

Por lo tanto:
- MODBUS PDU para comunicaciones seriales = 256 - Direccion Server (1 byte) - CRC (2 bytes) = 253 bytes.

Consecuentemente:
- RS232 / RS485 ADU = 253 bytes + Direccion Server (1 byte) + CRC (2 bytes) = 256 bytes.

- TCP MODBUS ADU = 253 bytes + MBAP (7 bytes) = 260 bytes.

##Modbus sobre TCP/IP

###Arquitectura general de la comunicacion

  Un sistema de comunicacion MODBUS sobre TCP/IP puede incluir diferentes tipos de dispositivos:

  - Dispositivos MODBUS TCP/IP cliente y servidor conectados en una red TCP/IP.
  - Dispositivos de interconexión como bridges, routers o gateways para interconexión entre una red TCP / IP y una sub-red de línea serial, que permite conexiones de clientes Modbus en líneas de seriales.
    
![alt tag](https://github.com/pumanzor/modbus/blob/master/img/modbustcpip1.png)

#### MODBUS sobre TCP/IP Application Data Unit

 A continuacion se describe la encapsulacion de un request o response MODBU cuando es transportado sobre un red TCP/IP.
 
![alt tag](https://github.com/pumanzor/modbus/blob/master/img/modbustcpip2.png)

Como se puede apreciar en la imagen se agrega un header en el frame TCP/IP el cual se denomina MBAP Header (MODBUS Application Protocol header).

Este header provee algunas diferencias comparadas con el ADU de MODBUS RTU usado en lineas seriales

  Por ejemplo el campo "slave adress" en Modbus RTU sobre lineas seriales es reemplazado por un solo byte denominado "Unit Identifier" dentro del header MBAP. 

  Este campo se utiliza para comunicarse a traves de dispositivos tales como router, bridges o gateways que utilizan una única dirección IP para soportar múltiples unidades finales MODBUS independientes.

  Todas las solicitudes y las respuestas estan diseñadas de tal manera que el destinatario pueda verificar que un mensaje ha finalizado. Para codigos de funcion en que el PDU Modbus tiene una longitud fija, el codigo de funcion por si sola es suficiente
  
  Para códigos de función que llevan una cantidad variable de datos en la solicitud o respuesta, el campo de datos incluye una cuenta de bytes.
  
  Cuando MODBUS opera sobre TCP, la información de longitud adicional se realiza en la cabecera MBAP para que el destinatario reconozca límites de mensaje incluso si el mensaje se ha dividido en varios paquetes para la transmisión. 
  
  La existencia de normas de longitud explícitos e implícitos y el uso de un código de comprobación de errores CRC-32 (en Ethernet) se traduce en una probabilidad infinitesimal de la corrupción no detectada a un mensaje de petición o respuesta.
  
#### Diferencia entre el paquete Modbus TCP/IP y Modbus RTU

![alt tag](https://github.com/pumanzor/modbus/blob/master/img/modbustcpvsrtu.png)
  
###MBAP Header description

El header MBAP es de 7 bytes de longitud y contiene los siguiente campos:

* Transaction Identifier (2 bytes) - se utiliza para el emparejamiento de transacciones, el server MODBUS copia en la respuesta el identificador de transaccion en el requerimiento

* Protocol Identifier (2 bytes) - se utiliza para multiplexacion interna del sistema El protocolo MOBBUS es identificado con el valor 0.

* Longitud (2 bytes) - El campo longitud es una cuenta de bytes de los siguientes campos, incluyendo el Unit Identifier y los campos de data. 

*  Unit Identifier (1 byte) - Este campo se utiliza para propósitos de enrutamiento intra-sistema. Se suele utilizar para comunicarse con  MODBUS+ o Modbus slave sobre lineas seriales a través de un gateway entre una red Ethernet TCP-IP y una línea serie Modbus.

  Este campo se establece por el cliente Modbus en la solicitud y debe ser devuelto con el mismo valor en la respuesta del servidor.
  
En la siguiente imagen se puede apreciar una captura mediante wireshark en donde se muestran los campos antes descritos  

![alt tag](https://github.com/pumanzor/modbus/blob/master/img/wiresharkmbap.png)


