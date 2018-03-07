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

void initStates(); // initialiser states og kjør til etasje

int emergencyStopHandler(); // håndterer emergency stopp

void stateController(); // styrer heis basert på nåværende og forrige tilstand
