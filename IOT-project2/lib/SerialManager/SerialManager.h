#pragma once

#include <Arduino.h>
#include "Protocol.h"








class SerialManager
{

private:
    Register internalRegister;
    int count = 0;
    unsigned int baudRate;
    bool connectionEstablished = false;


    SerialManager(unsigned int baudRate) : baudRate(baudRate) {}

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
    static SerialManager& getInstance(unsigned int baudRate = 9600) {
        static SerialManager* instance;
        if (instance == nullptr) {
            instance = new SerialManager(baudRate);
        }
        return *instance;
    }

    void operator=(SerialManager const&) = delete; // serial = serial1; NO

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
                connectionEstablished = true;
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
