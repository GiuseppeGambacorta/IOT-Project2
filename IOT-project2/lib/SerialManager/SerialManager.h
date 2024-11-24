# pragma once

#include <Arduino.h>

enum class VarType : byte
{
    BYTE,
    INT,
    STRING,
};

enum class MessageType : byte
{
    VAR,
    DEBUG,
};

struct DataHeader
{
    MessageType messageType;
    VarType varType;
    byte size;
    byte *data;
};


class Register {
private:
    static const int MAX_VARIABLES = 10; 
    DataHeader variables[MAX_VARIABLES]; 
    unsigned int variablesCount = 0;
    static const int MAX_DEBUG = 100;
    DataHeader debugMessage[MAX_DEBUG];
    unsigned int debugCount = 0;

public:
    Register() {}

    void addVariable(byte* var, VarType varType) {
        if (variablesCount < MAX_VARIABLES) {
            variables[variablesCount].messageType = MessageType::VAR;
            variables[variablesCount].varType = varType;
            variables[variablesCount].data = var;
            switch (varType) {
                case VarType::BYTE:
                    variables[variablesCount].size = sizeof(byte);
                    break;
                case VarType::INT:
                    variables[variablesCount].size = sizeof(int);
                    break;
            }
            variablesCount++;
        }
    }

    void addVariable(String* string){
        if (variablesCount < MAX_VARIABLES) {
            variables[variablesCount].messageType = MessageType::VAR;
            variables[variablesCount].varType = VarType::STRING;
            variables[variablesCount].data = (byte*)string;
            variables[variablesCount].size = string->length() + 1;
            Serial.println(variables[variablesCount].size);
            variablesCount++;
        }
    }


    void addDebugMessage(const char* message) {
        if (debugCount < MAX_DEBUG) {
            debugMessage[debugCount].messageType = MessageType::DEBUG;
            debugMessage[debugCount].varType = VarType::STRING;
            debugMessage[debugCount].data = (byte*)message;
            debugMessage[debugCount].size = strlen(message) + 1;
            debugCount++;
        }
    }


    void updateStringLength(unsigned int  index, String* string) {
        if (index >= 0 && index < variablesCount && variables[index].varType == VarType::STRING) {
            variables[index].size = string->length() + 1;
        }
    }

    DataHeader* getVariableHeader(unsigned int index) {
        if (index >= 0 && index < variablesCount) {
            return &variables[index];
        } else {
            return nullptr;
        }
    }

    DataHeader* getDebugMessageHeader(unsigned int index) {
        if (index >= 0 && index < variablesCount) {
            return &debugMessage[index];
        } else {
            return nullptr;
        }
    }


    int getVariableCount() {
        return variablesCount;
    }

    int getDebugMessageCount() {
        return debugCount;
    }

    void resetDebugMessages() {
        debugCount = 0;
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

        void addVariableToSend(byte* var, VarType varType) {
            internalRegister.addVariable(var, varType);
        }

        void addVariableToSend(String* string) {
            internalRegister.addVariable(string);
        }

        void addDebugMessage(const char* message) {
            internalRegister.addDebugMessage(message);
        }

        void sendData() {
            byte numberOfVariables = internalRegister.getVariableCount()+ internalRegister.getDebugMessageCount();
            byte header = 255;
            Serial.write(header);
            header = 0;
            Serial.write(header);
            Serial.write((byte*)&numberOfVariables, sizeof(numberOfVariables));
            for (int i = 0; i < internalRegister.getVariableCount(); i++) {
                DataHeader* header = internalRegister.getVariableHeader(i);


                Serial.write((byte*)&header->messageType, sizeof(header->messageType));
                Serial.write((byte*)&header->varType, sizeof(header->varType));

                if (header->varType == VarType::STRING) {
                     internalRegister.updateStringLength(i, (String*)header->data);
                    Serial.write((byte*)&header->size, sizeof(header->size));
                    String* string = (String*)header->data;
                    Serial.write(string->c_str(), header->size);
                } else {

                    Serial.write((byte*)&header->size, sizeof(header->size));
                    Serial.write(header->data, header->size); 
                }
            }
            
            for (int i = 0; i < internalRegister.getDebugMessageCount(); i++) {
                DataHeader* header = internalRegister.getDebugMessageHeader(i);

                Serial.write((byte*)&header->messageType, sizeof(header->messageType));
                Serial.write((byte*)&header->varType, sizeof(header->varType));
                Serial.write((byte*)&header->size, sizeof(header->size));
                Serial.write(header->data, header->size);
               
            }
            
            internalRegister.resetDebugMessages();



            Serial.flush();
        }

};