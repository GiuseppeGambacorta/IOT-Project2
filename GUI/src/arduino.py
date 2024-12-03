import serial
import struct
from enum import Enum
from serial.tools import list_ports


class MessageType(Enum):
    VAR = 0
    DEBUG = 1
    EVENT = 2

class VarType(Enum):
    BYTE = 0
    INT = 1
    STRING = 2
    FLOAT = 3
    

class DataHeader:
    def __init__(self, message_type, var_type, id, size, data):
        self.message_type = message_type
        self.var_type = var_type
        self.id = id
        self.size = size
        self.data = data


class Protocol:
    def __init__(self, serial_connection):
        self.serial_connection = serial_connection

    def handshake(self):
        response = None
        while response != 10: 
            print("Aspetto che Arduino si connetta...")
            value_to_send = 255
            self.serial_connection.write(value_to_send.to_bytes(1, 'big'))
            response = self.serial_connection.read(1)  
            if not response:
                continue
            response = struct.unpack('B', response)[0]
            print(f"Ricevuto: {response}")
        print("Arduino connesso!")

    def read_communication_data(self):
        starthead = self.serial_connection.read(1)
        if not starthead:
            return None
        
        starthead = struct.unpack('B', starthead)[0]
        if starthead != 255:
            print("Errore di sincronizzazione.")
            return None
        
        starthead = self.serial_connection.read(1)
        if not starthead:
            return None
        starthead = struct.unpack('B', starthead)[0]
        if starthead != 0:
            print("Errore di sincronizzazione.")
            return None

        number_of_messages = self.serial_connection.read(1)
    
        if not number_of_messages:
            return None
        number_of_messages = struct.unpack('B', number_of_messages)[0]
        return number_of_messages

    def read_message(self):
        message_type_data = self.serial_connection.read(1)
        if not message_type_data:
            return None
        message_type = struct.unpack('B', message_type_data)[0]

        var_type_data = self.serial_connection.read(1)
        if not var_type_data:
            return None
        var_type = struct.unpack('B', var_type_data)[0]

        id_data = self.serial_connection.read(1)
        if not id_data:
            return None
        id = struct.unpack('B', id_data)[0]

        size_data = self.serial_connection.read(1)
        if not size_data:
            return None
        size = struct.unpack('B', size_data)[0]

        data = self.serial_connection.read(size)
        if not data or len(data) != size:
            return None

        if var_type == VarType.INT.value:
            value = struct.unpack('<h', data)[0]  # '<h' per short int (little-endian)
        elif var_type == VarType.STRING.value:
            value = data.decode('utf-8')
        elif var_type == VarType.FLOAT.value:
            value = struct.unpack('<f', data)[0]  # '<f' per float (little-endian)
            print(f'valore letto {value}')
        else:
            # Tipo non riconosciuto
            return None

        return DataHeader(message_type, var_type, id, data, value)


    def write_data(self, value, id):
        self.serial_connection.write((255).to_bytes(1, 'big'))
        self.serial_connection.write((0).to_bytes(1, 'big'))

        message_type = MessageType.VAR.value.to_bytes(1, 'big')
        var_type = VarType.INT.value.to_bytes(1, 'big')
        id = id.to_bytes(1, 'big')
        size = (2).to_bytes(1, 'big')
        value = value.to_bytes(2, 'big')
        self.serial_connection.write(message_type)
        self.serial_connection.write(var_type)
        self.serial_connection.write(id)
        self.serial_connection.write(size)
        self.serial_connection.write(value)


class ArduinoReader:
    def __init__(self, baudrate=9600, timeout=1):
        self.baudrate = baudrate
        self.timeout = timeout
        self.serial_connection = None
        self.protocol = None

        self.variables = []
        self.debugs = []
        self.events = []

    # Connect to the Arduino, check for handshake and wait for the connection
    def connect(self):
        try:
            self.port = self._find_arduino_port()
            if self.port is None:
                raise Exception("Nessuna porta Arduino trovata.")
           
            self.serial_connection = serial.Serial(self.port, self.baudrate, timeout=self.timeout)
            self.protocol = Protocol(self.serial_connection)
            print(f"Connesso ad Arduino su {self.port} a {self.baudrate} baud.")
            self.serial_connection.reset_input_buffer()
            self.serial_connection.reset_output_buffer()
            self.protocol.handshake()

        except Exception as e:
            print(f"Errore nella connessione: {e}")

    def _find_arduino_port(self):
        ports = list_ports.comports()
        
        return ports[0].device if ports else None

    # Read the data from the serial connection, first read the number of messages and then read the messages, , divide them by type and store them in the respective lists
    def read_data(self):
        if self.serial_connection and self.serial_connection.is_open:
            self.variables.clear()
            self.debugs.clear()
            self.events.clear()

            try:

                number_of_messages = self.protocol.read_communication_data()   
                if number_of_messages is None:
                    print("Errore di lettura. niente dal leggere")
                    return None

                for i in range(number_of_messages):
                    temp_message = self.protocol.read_message()
                    if temp_message is None:
                        print("Errore di lettura.")
                        return None
                    if temp_message.message_type == MessageType.VAR.value:
                        print(f'value: {temp_message.data}')
                        self.variables.append(temp_message)
                    elif temp_message.message_type == MessageType.DEBUG.value:
                        self.debugs.append(temp_message)
                    elif temp_message.message_type == MessageType.EVENT.value:
                        self.events.append(temp_message)
                
                self.serial_connection.reset_input_buffer()

                return self.variables.copy(), self.debugs.copy(), self.events.copy()
            except serial.SerialException as e:
                    print(f"Errore di lettura: {e}")
                    return None
        else:
            print("Connessione seriale non aperta.")
            return None
    

    def is_connected(self):
        return self.serial_connection and self.serial_connection.is_open
    
    # Write data to the serial connection. before writing the data an handshake is made
    def write_data(self, value, id):
        if self.serial_connection and self.serial_connection.is_open:
            try:
                self.protocol.write_data(value, id)
            except serial.SerialException as e:
                print(f"Errore di scrittura: {e}")
        else:
            print("Connessione seriale non aperta.")

  
    def close(self):
        if self.serial_connection and self.serial_connection.is_open:
            self.serial_connection.close()
            print("Connessione chiusa.")

# Esempio di utilizzo
if __name__ == "__main__":
    arduino = ArduinoReader(port='COM3')  # Sostituisci 'COM3' con la porta corretta
    arduino.connect()
    try:
        while True:
            message = arduino.read_data()
            if message:
                print(f"ID del messaggio: {message.id}")
                print(f"Tipo di variabile: {message.var_type}")
                print(f"Dimensione del messaggio: {message.size}")
                print(f"Dati ricevuti: {message.data}")
    except KeyboardInterrupt:
        print("Interruzione da tastiera rilevata. Chiudo la connessione...")
    finally:
        arduino.close()