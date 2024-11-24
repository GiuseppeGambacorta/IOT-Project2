# pragma once

#include <Arduino.h>

enum class Type : byte
{
    BYTE,
    INT,
    STRING,
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
    DataHeader variables[MAX_VARIABLES]; 
    int count = 0;

public:
    Register() {}

    void addVariable(byte* var, Type varType) {
        if (count < MAX_VARIABLES) {
            variables[count].id = count;
            variables[count].varType = varType;
            variables[count].data = var;
            switch (varType) {
                case Type::BYTE:
                    variables[count].size = sizeof(byte);
                    break;
                case Type::INT:
                    variables[count].size = sizeof(int);
                    break;
            }
            count++;
        }
    }

    void addVariable(String* string){
        if (count < MAX_VARIABLES) {
            variables[count].id = count;
            variables[count].varType = Type::STRING;
            variables[count].data = (byte*)string;
            variables[count].size = string->length() + 1;
            Serial.println(variables[count].size);
            count++;
        }
    }


    void updateStringLength(int index, String* string) {
        if (index >= 0 && index < count && variables[index].varType == Type::STRING) {
            variables[index].size = string->length() + 1;
        }
    }

    DataHeader* getHeader(int index) {
        if (index >= 0 && index < count) {
            return &variables[index];
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

        void addVariableToSend(String* string) {
            internalRegister.addVariable(string);
        }

        void sendData() {
            byte numberOfVariables = internalRegister.getCount();
            Serial.write((byte*)&numberOfVariables, sizeof(numberOfVariables));
            for (int i = 0; i < internalRegister.getCount(); i++) {
                DataHeader* header = internalRegister.getHeader(i);


                Serial.write((byte*)&header->id, sizeof(header->id));
                Serial.write((byte*)&header->varType, sizeof(header->varType));

                if (header->varType == Type::STRING) {
                     internalRegister.updateStringLength(i, (String*)header->data);
                    Serial.write((byte*)&header->size, sizeof(header->size));
                    String* string = (String*)header->data;
                    Serial.write(string->c_str(), header->size);
                } else {

                    Serial.write((byte*)&header->size, sizeof(header->size));
                    Serial.write(header->data, header->size); 
                }
            }
            Serial.flush();
        }

};