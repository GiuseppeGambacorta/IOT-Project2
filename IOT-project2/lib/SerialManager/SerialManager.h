# pragma once

#include <Arduino.h>

enum class Type : byte
{
    BYTE,
    INT
};

struct DataHeader
{
    byte id;
    Type varType;
    byte size;
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
            headers[count].id = count;
            headers[count].varType = varType;
            headers[count].data = var;
            switch (varType) {
                case Type::BYTE:
                    headers[count].size = sizeof(byte);
                    break;
                case Type::INT:
                    headers[count].size = sizeof(int);
                    break;
            }
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
            byte numberOfVariables = internalRegister.getCount();
            Serial.write((byte*)&numberOfVariables, sizeof(numberOfVariables));
            for (int i = 0; i < internalRegister.getCount(); i++) {
                DataHeader* header = internalRegister.getHeader(i);
                Serial.write((byte*)&header->id, sizeof(header->id));
                Serial.write((byte*)&header->varType, sizeof(header->varType));
                Serial.write((byte*)&header->size, sizeof(header->size));
                Serial.write(header->data, header->size); // for now we assume that the data are only integers
            }
            Serial.flush();
        }

};