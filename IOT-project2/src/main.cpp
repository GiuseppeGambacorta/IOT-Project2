#include <Arduino.h>
#include "ArduinoStandardLibrary.h"
//#include "scheduler/api/Scheduler.h"

enum class MessageType : byte
{
    DATA,
    MESSAGE
};

enum class Type : byte
{
    BYTE,
    INT
};

struct DataHeader
{
    MessageType type = MessageType::DATA;
    Type varType;
    byte *data;
};

struct MessageHeader
{
    MessageType type = MessageType::MESSAGE;
    byte length;
    byte *data;
};

//Scheduler scheduler;
int i = 530;
int i2 =1000;

void setup() {
    Serial.begin(9600);

    // conto del tempo ottimale per i task
    // scheduler.init(10); //inserire tempo ricavato opportunamente
}

void loop() {
    while (!Serial) {
        Serial.println("Waiting for serial connection...");
        delay(1000);
    }

    //scheduler.schedule();

    DataHeader header;
    header.type = MessageType::DATA;
    header.varType = Type::INT;
    header.data = (byte*) &i;

    Serial.write((byte*)&header.type, sizeof(header.type));
    Serial.write((byte*)&header.varType, sizeof(header.varType));
    Serial.write(header.data, 2); // Assumendo che la lunghezza dei dati sia 1 byte


    header.data = (byte*) &i2;

    //Serial.write((byte*)&header.type, sizeof(header.type));
    //Serial.write((byte*)&header.varType, sizeof(header.varType));
    //Serial.write(header.data, 2); // Assumendo che la lunghezza dei dati sia 1 byte

    i+=5;
    i2++;
    //Serial.flush();
    //delay(5000);
}