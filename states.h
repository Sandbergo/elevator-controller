#pragma once

//-----------STATE-----------

typedef enum {

        INIT = 0,
        IDLE = 1,
        RUN = 2,
        STOP = 3,
        EMERGENCY = -1,
} elevState;


//---functions--------

void init();

int emStop();