# pragma once

#include <Arduino.h>

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
    byte id;
    Type varType;
    byte size;
    byte *data;
};

struct MessageHeader
{
    MessageType type = MessageType::MESSAGE;
    byte length;
    byte *data;
};


class Register {
private:
    static const int MAX_VARIABLES = 10; 
    DataHeader headers[MAX_VARIABLES]; 
    int count = 0;

public:
    Register() {}

    void addVariable(byte* var, Type varType) {
        if (count < MAX_VARIABLES) {
            headers[count].type = MessageType::DATA;
            headers[count].id = count;
            headers[count].varType = varType;
            headers[count].size = sizeof(int);
            headers[count].data = var;
            count++;
        }
    }

    DataHeader* getHeader(int index) {
        if (index >= 0 && index < count) {
            return &headers[index];
        } else {
            return nullptr;
        }
    }

    int getCount() {
        return count;
    }
};



class SerialManager{

    private:
        Register internalRegister;
        int count = 0;
        unsigned int baudRate;

    public:

        SerialManager(unsigned int baudRate) {
            this->baudRate = baudRate;
        }

        void init() {
            Serial.begin(baudRate);
        }

        bool isSerialAvailable() {
            return Serial;
        }

        void addVariableToSend(byte* var, Type varType) {
            internalRegister.addVariable(var, varType);
        }

        void sendData() {
            for (int i = 0; i < internalRegister.getCount(); i++) {
                DataHeader* header = internalRegister.getHeader(i);
                Serial.write((byte*)&header->type, sizeof(header->type));
                Serial.write((byte*)&header->id, sizeof(header->id));
                Serial.write((byte*)&header->varType, sizeof(header->varType));
                Serial.write((byte*)&header->size, sizeof(header->size));
                Serial.write(header->data, header->size); // for now we assume that the data are only integers
            }
            Serial.flush();
        }

};