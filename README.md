##Modbus Protocol

###Introduccion


###Protocolo

El protocolo Modbus se usa principalmente sobre dos tipos de comunicaciones:

- Modbus sobre lineas seriales
- Modbus sobre TCP/IP

Campo Address Field.

El campo de direccion de un frame modbus contiene 2 caracteres (ASCII) o 8 bits (RTU). En un sub-controller slave
las direcciones validas van en el rango de 1 a 247.

Cuando un Maestro envia un mensaje hacia un esclavo, el frame que proviene desde el maestro debe incluir en el campo "Address Field" el ID del esclavo.

Cuando el Esclavo Recibe el request, enviara la respuesta de vuelta al maestro y pone en el campo Address Field su propio ID.
