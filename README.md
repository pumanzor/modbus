##Modbus Protocol

El protocolo Modbus se usa principalmente sobre dos tipos de comunicaciones:

- Modbus sobre lineas seriales
- Modbus sobre TCP/IP

Campo Address Field.

El campo de direccion de un frame modbus contiene 2 caracteres (ASCII) o 0 bits (RTU). En un sub-controller slave
las direciones validas son en el rango de 1 a 247 decimal.

Cuando un Maestro envia un mensaje hacia un esclave, el frame que proviene desde el maestro debe incluir en el campo "Address Field" el ID del esclavo.

Cuando el Esclavo envia la respuesta, pone en el campo Address Field su propio ID para dejar saber al Maestro que esclavo es el que esta respondiendo.
