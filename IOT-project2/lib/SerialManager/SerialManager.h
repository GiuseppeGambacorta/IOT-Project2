#pragma once

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
    EVENT,
};

struct DataHeader
{
    MessageType messageType;
    VarType varType;
    byte id;
    byte size;
    byte *data;
};

class Register
{
private:
    static const int MAX_VARIABLES = 10;
    DataHeader variables[MAX_VARIABLES];
    unsigned int variablesCount = 0;
    static const int MAX_DEBUG = 50;
    DataHeader debugMessage[MAX_DEBUG];
    unsigned int debugCount = 0;

    static const int MAX_EVENTS = 50;
    DataHeader eventMessage[MAX_EVENTS];
    unsigned int eventCount = 0;

    static const int NUMBER_OF_INCOMING_DATA = 2;
    int datiInArrivo[NUMBER_OF_INCOMING_DATA]; //for now only int are supported

public:
    Register() {}

    void addVariable(byte *var, VarType varType)
    {
        if (variablesCount < MAX_VARIABLES)
        {
            variables[variablesCount].messageType = MessageType::VAR;
            variables[variablesCount].varType = varType;
            variables[variablesCount].id = variablesCount;
            variables[variablesCount].data = var;
            switch (varType)
            {
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

    void addVariable(String *string)
    {
        if (variablesCount < MAX_VARIABLES)
        {
            variables[variablesCount].messageType = MessageType::VAR;
            variables[variablesCount].varType = VarType::STRING;
            variables[variablesCount].id = variablesCount;
            variables[variablesCount].data = (byte *)string;
            variables[variablesCount].size = string->length() + 1;
            variablesCount++;
        }
    }

    void addDebugMessage(const char *message)
    {

        for (unsigned int i = 0; i < debugCount; i++)
        {
            if (strcmp((char *)debugMessage[i].data, message) == 0)
            {
                return;
            }
        }

        if (debugCount < MAX_DEBUG)
        {
            debugMessage[debugCount].messageType = MessageType::DEBUG;
            debugMessage[debugCount].varType = VarType::STRING;
            debugMessage[debugCount].id = 0;
            debugMessage[debugCount].data = (byte *)message;
            debugMessage[debugCount].size = strlen(message) + 1;
            debugCount++;
        }
    }

    void addEventMessage(const char *message)
    {

        for (unsigned int i = 0; i < eventCount; i++)
        {
            if (strcmp((char *)eventMessage[i].data, message) == 0)
            {
                return;
            }
        }

        if (eventCount < MAX_EVENTS)
        {
            eventMessage[eventCount].messageType = MessageType::EVENT;
            eventMessage[eventCount].varType = VarType::STRING;
            eventMessage[eventCount].id = 0;
            eventMessage[eventCount].data = (byte *)message;
            eventMessage[eventCount].size = strlen(message) + 1;
            eventCount++;
        }
    }

    void updateStringLength(unsigned int index, String *string)
    {
        if (index >= 0 && index < variablesCount && variables[index].varType == VarType::STRING)
        {
            variables[index].size = string->length() + 1;
        }
    }

    DataHeader *getVariableHeader(unsigned int index)
    {
        if (index >= 0 && index < variablesCount)
        {
            return &variables[index];
        }
        else
        {
            return nullptr;
        }
    }

    DataHeader *getDebugMessageHeader(unsigned int index)
    {
        if (index >= 0 && index < variablesCount)
        {
            return &debugMessage[index];
        }
        else
        {
            return nullptr;
        }
    }

    DataHeader *getEventMessageHeader(unsigned int index)
    {
        if (index >= 0 && index < variablesCount)
        {
            return &eventMessage[index];
        }
        else
        {
            return nullptr;
        }
    }

    int *getIncomingDataHeader(unsigned int index)
    {
        if (index >= 0 && index < NUMBER_OF_INCOMING_DATA)
        {
            return &datiInArrivo[index];
        }
        else
        {
            return nullptr;
        }
    }

    unsigned int getVariableCount()
    {
        return variablesCount;
    }

    unsigned int getDebugMessageCount()
    {
        return debugCount;
    }

    unsigned int getEventMessageCount()
    {
        return eventCount;
    }

    void resetDebugMessages()
    {
        debugCount = 0;
    }

    void resetEventMessages()
    {
        eventCount = 0;
    }
};

class SerialManager
{

private:
    Register internalRegister;
    int count = 0;
    unsigned int baudRate;
    bool connectionEstablished = false;

    void sendinitCommunicationData()
    {
        byte numberOfVariables = internalRegister.getVariableCount() + internalRegister.getDebugMessageCount() + internalRegister.getEventMessageCount();
        byte header = 255;
        Serial.write(header);
        header = 0;
        Serial.write(header);
        Serial.write((byte *)&numberOfVariables, sizeof(numberOfVariables));
    }

    void sendVariables()
    {
        for (unsigned int i = 0; i < internalRegister.getVariableCount(); i++)
        {
            DataHeader *header = internalRegister.getVariableHeader(i);

            Serial.write((byte *)&header->messageType, sizeof(header->messageType));
            Serial.write((byte *)&header->varType, sizeof(header->varType));
            Serial.write((byte *)&header->id, sizeof(header->id));

            if (header->varType == VarType::STRING)
            {
                internalRegister.updateStringLength(i, (String *)header->data);
                Serial.write((byte *)&header->size, sizeof(header->size));
                String *string = (String *)header->data;
                Serial.write(string->c_str(), header->size);
            }
            else
            {

                Serial.write((byte *)&header->size, sizeof(header->size));
                Serial.write(header->data, header->size);
            }
        }
    }

    void sendDebugMessages()
    {
        for (unsigned int i = 0; i < internalRegister.getDebugMessageCount(); i++)
        {
            DataHeader *header = internalRegister.getDebugMessageHeader(i);

            Serial.write((byte *)&header->messageType, sizeof(header->messageType));
            Serial.write((byte *)&header->varType, sizeof(header->varType));
            Serial.write((byte *)&header->id, sizeof(header->id));
            Serial.write((byte *)&header->size, sizeof(header->size));
            Serial.write(header->data, header->size);
        }
    }

    void sendEventMessages()
    {
        for (unsigned int i = 0; i < internalRegister.getEventMessageCount(); i++)
        {
            DataHeader *header = internalRegister.getEventMessageHeader(i);

            Serial.write((byte *)&header->messageType, sizeof(header->messageType));
            Serial.write((byte *)&header->varType, sizeof(header->varType));
            Serial.write((byte *)&header->id, sizeof(header->id));
            Serial.write((byte *)&header->size, sizeof(header->size));
            Serial.write(header->data, header->size);
        }
    }

public:
    SerialManager(unsigned int baudRate)
    {
        this->baudRate = baudRate;
    }

    void init()
    {
        Serial.begin(baudRate);
    }

    bool isSerialAvailable()
    {
        return Serial;
    }

    void doHandshake()
    {
        
        if (Serial.available() > 0)
        {
            byte received = (short unsigned int)Serial.read(); //convert because i want to check a number not a char or a byte
            if (received == 255)
            {
                Serial.write(10);

                received = (short unsigned int)Serial.read(); 
                if (received == 0){
                    connectionEstablished = true;
                }
            }
        }
        
    }

    bool isConnectionEstablished()
    {
        return this->connectionEstablished && isSerialAvailable();
    }

    void addVariableToSend(byte *var, VarType varType)
    {
        internalRegister.addVariable(var, varType);
    }

    void addVariableToSend(String *string)
    {
        internalRegister.addVariable(string);
    }

    void addDebugMessage(const char *message)
    {
        internalRegister.addDebugMessage(message);
    }

    void addEventMessage(const char *message)
    {
        internalRegister.addEventMessage(message);
    }

    void sendData()
    {
            Serial.flush(); // wait for the transmission of outgoing serial data to complete, before sending new data
            sendinitCommunicationData();
            sendVariables();
            sendDebugMessages();
            sendEventMessages();

            internalRegister.resetDebugMessages();
            internalRegister.resetEventMessages();
   
    }

    void getData()
    {
        if (Serial.available() > 0)
        {

            byte header = Serial.read();
            if (header == 255)
            {
                byte command = Serial.read();
                if (command == 0)
                {
                    byte message_type = Serial.read();
                    byte var_type = Serial.read();
                    byte id = Serial.read();
                    byte size = Serial.read();
                    byte buffer[size];
                    Serial.readBytes(buffer, size);
                    int *var = internalRegister.getIncomingDataHeader(int(id));
                    if (var != nullptr)
                    {
                        *var = (int(buffer[0]) << 8) | int(buffer[1]); //for now only int are supported
                    }
                }
            }
        }
    }

    //for now only int are supported
    int* getvar(unsigned int index)
    {
        return internalRegister.getIncomingDataHeader(index);
    }
   
};