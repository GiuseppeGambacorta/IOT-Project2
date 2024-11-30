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
    Register();

    void addVariable(byte *var, VarType varType);
    void addVariable(String *string);
    void addDebugMessage(const char *message);
    void addEventMessage(const char *message);
    void updateStringLength(unsigned int index, String *string);
    DataHeader *getVariableHeader(unsigned int index);
    DataHeader *getDebugMessageHeader(unsigned int index);
    DataHeader *getEventMessageHeader(unsigned int index);
    int *getIncomingDataHeader(unsigned int index);
    unsigned int getVariableCount();
    unsigned int getDebugMessageCount();
    unsigned int getEventMessageCount();
    void resetDebugMessages();
    void resetEventMessages();
};



class Protocol
{
private:
    Register& internalRegister;
    bool connectionEstablished = false;

public:
    Protocol(Register& reg) : internalRegister(reg) {}

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

    bool doHandshake()
    {
        if (Serial.available() > 0)
        {
            byte received = (short unsigned int)Serial.read(); //convert because i want to check a number not a char or a byte
            if (received == 255)
            {
                Serial.write(10);
                connectionEstablished = true;
            }
        }
        return connectionEstablished;
    }

    bool isConnectionEstablished()
    {
        return connectionEstablished;
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
};