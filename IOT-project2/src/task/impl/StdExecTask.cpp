#include "task/api/Task.h"

typedef enum {
    READY,
    OPENING,
    OPEN,
    CLOSING
} StdExecState;

class StdExecTask : public Task {
    StdExecState state;

    StdExecTask (){
       state = READY; 
    }

    void tick(){
        switch (state){
            case READY:
                //TODO: implement
                break;
            case OPENING:
                //TODO: implement
                break;
            case OPEN:
                //TODO: implement
                break;
            case CLOSING:
                //TODO: implement
                break;
        }
    }
};