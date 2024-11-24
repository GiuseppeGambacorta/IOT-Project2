import serial
import struct
from enum import Enum

class VarType(Enum):
    BYTE = 0
    INT = 1
    STRING = 2
    # Aggiungi altri tipi di variabili se necessario

class DataHeader:
    def __init__(self, id, var_type, size, data):
        self.id = id
        self.var_type = var_type
        self.size = size
        self.data = data


class ArduinoReader:
    def __init__(self, port, baudrate=9600, timeout=1):
        self.port = port
        self.baudrate = baudrate
        self.timeout = timeout
        self.serial_connection = None

    def connect(self):
        try:
            # Configura la connessione seriale
            self.serial_connection = serial.Serial(self.port, self.baudrate, timeout=self.timeout)
            print(f"Connesso ad Arduino su {self.port} a {self.baudrate} baud.")
            self.serial_connection.reset_input_buffer()
            self.serial_connection.reset_output_buffer()

        
            response = None
            while response != 10:  # Aspetto il byte 0x0A (10 in decimale)
                print("Aspetto che Arduino si connetta...")
                value_to_send = 255
                self.serial_connection.write(value_to_send.to_bytes(1, 'big'))
                response = self.serial_connection.read(1)  # Leggo un byte
                if not response:
                    continue
                response = struct.unpack('B', response)[0]
                print(f"Ricevuto: {response}")
            print("Arduino connesso!")

        except Exception as e:
            print(f"Errore nella connessione: {e}")



    def read_data(self):
        if self.serial_connection and self.serial_connection.is_open:
            data = []
            try:

                starthead = self.serial_connection.read(1)
                if not starthead:
                    return None
                starthead = struct.unpack('B', starthead)[0]
                print(f'header {starthead}')
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
                print(f'lunghezza messaggi {number_of_messages}')
                for i in range(number_of_messages):
                    data.append(self._read_data())
                
                self.serial_connection.reset_input_buffer()
                if data == [] or None in data:
                    print("Errore di lettura.")
                    return None

                for reading in data:
                    print(reading.data)
            
                return data[0]
            except serial.SerialException as e:
                    print(f"Errore di lettura: {e}")
                    return None
        else:
            print("Connessione seriale non aperta.")
            return None

    def _read_data(self):


        id_data = self.serial_connection.read(1)
        if not id_data:
            return None
        id = struct.unpack('B', id_data)[0]

        var_type_data = self.serial_connection.read(1)
        if not var_type_data:
            return None
        var_type = struct.unpack('B', var_type_data)[0]

        size = self.serial_connection.read(1)
        if not size:
            return None
        size = struct.unpack('B', size)[0]



        if var_type == VarType.INT.value:
            data = self.serial_connection.read(size)
            if not data:
                return None
            value = struct.unpack('h', data)[0]
            return DataHeader(id, var_type, data, value)
        
        if var_type == VarType.STRING.value:
            data = self.serial_connection.read(size)
            if not data:
                return None
            value = data.decode('utf-8')
            return DataHeader(id, var_type, data, value)
        
        return None

  
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