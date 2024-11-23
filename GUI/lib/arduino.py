import serial
import struct

class DataHeader:
    def __init__(self, var_type, data):
        self.type = 0  # MessageType::DATA
        self.var_type = var_type
        self.data = data

class MessageHeader:
    def __init__(self, length, data):
        self.type = 1  # MessageType::MESSAGE
        self.length = length
        self.data = data

class ArduinoReader:
    def __init__(self, port, baudrate=9600, timeout=1):
        self.port = port
        self.baudrate = baudrate
        self.timeout = timeout
        self.serial_connection = None

    def connect(self):
        try:
            self.serial_connection = serial.Serial(self.port, self.baudrate, timeout=self.timeout)
            print(f"Connesso ad Arduino su {self.port} a {self.baudrate} baud.")
        except serial.SerialException as e:
            print(f"Errore di connessione: {e}")

    def read_data(self):
        if self.serial_connection and self.serial_connection.is_open:
            try:
                # Leggi il tipo di messaggio
                type_data = self.serial_connection.read(1)
                if not type_data:
                    return None
                message_type = struct.unpack('B', type_data)[0]

                if message_type == 0:  # MessageType::DATA
                    # Leggi il tipo di variabile
                    var_type_data = self.serial_connection.read(1)
                    if not var_type_data:
                        return None
                    var_type = struct.unpack('B', var_type_data)[0]

                    if var_type == 1:  # Type::INT
                        # Leggi i dati dell'intero
                        data = self.serial_connection.read(2)
                        if not data:
                            return None
                        int_value = struct.unpack('h', data)[0]  # 'h' per short (2 byte)

                        return DataHeader(var_type, int_value)
                else:
                    # Leggi la lunghezza del messaggio
                    length_data = self.serial_connection.read(1)
                    if not length_data:
                        return None
                    length = struct.unpack('B', length_data)[0]

                    # Leggi i dati del messaggio
                    data = self.serial_connection.read(length)
                    if not data:
                        return None

                    return MessageHeader(length, data)
            except serial.SerialException as e:
                print(f"Errore di lettura: {e}")
                return None
        else:
            print("Connessione seriale non aperta.")
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
                print(f"Tipo di messaggio: {message.type}")
                if isinstance(message, DataHeader):
                    print(f"Tipo di variabile: {message.var_type}")
                    print(f"Dati ricevuti: {message.data}")
                elif isinstance(message, MessageHeader):
                    print(f"Lunghezza del messaggio: {message.length}")
                    print(f"Dati ricevuti: {message.data}")
    except KeyboardInterrupt:
        print("Interruzione da tastiera rilevata. Chiudo la connessione...")
    finally:
        arduino.close()