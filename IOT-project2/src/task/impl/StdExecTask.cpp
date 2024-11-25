#include "task/api/StdExecTask.h"


StdExecTask ::StdExecTask(){
    this->type = STD_EXEC;
    this->state = READY;
}

void StdExecTask ::tick(){
    switch (state)
    {
    case READY:
        // TODO: implement
        break;
    case OPENING:
        // TODO: implement
        break;
    case OPEN:
        // TODO: implement
        break;
    case CLOSING:
        // TODO: implement
        break;
    }
}

void StdExecTask ::reset(){
    state = READY;
}