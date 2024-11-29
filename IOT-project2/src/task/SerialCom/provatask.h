#pragma once

#include <../Services/Services.h>
#include "./task/Task.h"


class ProvaTask : public Task {

private:
   
    int i = 530;
    String s = "gambacorta";
    int i2 = 1;
    bool start = false;
    SerialManager& serialManager = ServiceLocator::getSerialManagerInstance();
    bool toggle = false;
    
public:
    ProvaTask()  {
            serialManager.addVariableToSend((byte *)&i, VarType::INT);
            serialManager.addVariableToSend((byte *)&i2, VarType::INT);
            serialManager.addVariableToSend(&s);


    }

    void tick() override {
        int* restore = serialManager.getvar(0);
        if (*restore == 1) {
            serialManager.addEventMessage("restore arrivato");
            *restore = 0;
        }

        int* empty = serialManager.getvar(1);
        if (*empty == 1) {
            serialManager.addEventMessage("svuota arrivato");
            *empty = 0;
        }

        s = "gambacorta " + String(i2);
        delay(100);
        
        
        //serialManager.addDebugMessage("prova debug seriale");
        //serialManager.addDebugMessage("prova debug seriale");
        serialManager.addEventMessage("prova evento seriale");
        toggle = !toggle;
        if (toggle)
        {
            //serialManager.addDebugMessage("prova debug seriale che capita ogni tanto");
        }

        digitalWrite(2, !start);

        if (i2 % 10 == 0)
        {
            serialManager.addDebugMessage("prova debug seriale che capita ogni 10");
        } else if (i2 % 5 == 0)
        {
            serialManager.addDebugMessage("prova debug seriale che capita ogni 5");
        }
        {
            
        }
        i += 5;
        i2 += 1;
    }
    void reset() override {
        ;
    }
};
