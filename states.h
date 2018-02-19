#pragma once

//-----------STATE-----------

typedef enum {

        INIT = 0,
        IDLE = 1,
        RUN = 2,
        STOP = 3,
        EMERGENCY = -1,
} elevState;


//---Variables--------

static int currentFloor = -1;
static int previousFloor = -1;
static int motorDir = 0;


//---functions--------

void init();

int getcurrentFloor();

int getPreviuos();

int getMotorDir();

void setMotorDir(int value);

void setPreviosFloor(int value);

void setCurrentFloor(int value);

void doorOpenClose();

void emStop();
