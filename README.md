##Modbus Protocol

###Introduccion

  Modbus es un protocolo de solicitud-respuesta implementado usando una relación maestro-esclavo. En una relación maestro-esclavo, la comunicación siempre se produce en pares, un dispositivo debe iniciar una solicitud y luego esperar una respuesta y el dispositivo de inicio (el maestro) es responsable de iniciar cada interacción. Por lo general, el maestro es una interfaz humano-máquina (HMI) o sistema SCADA y el esclavo es un sensor, controlador lógico programable (PLC) o controlador de automatización programable (PAC). El contenido de estas solicitudes y respuestas, y las capas de la red a través de las cuales se envían estos mensajes, son definidas por las diferentes capas del protocolo


###Protocolo

El protocolo Modbus se usa principalmente sobre dos tipos de comunicaciones:

- Modbus sobre lineas seriales
- Modbus sobre TCP/IP

Campo Address Field.

El campo de direccion de un frame modbus contiene 2 caracteres (ASCII) o 8 bits (RTU). En un sub-controller slave
las direcciones validas van en el rango de 1 a 247.

Cuando un Maestro envia un mensaje hacia un esclavo, el frame que proviene desde el maestro debe incluir en el campo "Address Field" el ID del esclavo.

Cuando el Esclavo Recibe el request, enviara la respuesta de vuelta al maestro y pone en el campo Address Field su propio ID.
