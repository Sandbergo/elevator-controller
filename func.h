#pragma once



//---Variables---


static int currentFloor = -1;
static int previousFloor = -1;
static int motorDir = 0;


//---functions---

int getcurrentFloor();

int getPreviuos();

int getMotorDir();

void setMotorDir(int value);

void setPreviosFloor(int value);

void setCurrentFloor(int value);


