#include <stdio.h>
#include <unistd.h>
#include "func.h"


int getCurrentFloor(){
								return currentFloor;
}

int getPreviousFloor(){
								return previousFloor;
}

int getMotorDir(){
								return motorDir;
}

void setMotorDir(int value){
								motorDir = value;
}

void setCurrentFloor(int value){
								currentFloor = value;
}

void setPreviousFloor(int value){
								previousFloor = value;
}

void update(){
								if(currentFloor != previousFloor) {
																setPreviousFloor(elev_get_floor_sensor_signal());
																printf("%s%d\n", "Previous: ", previousFloor);
																printf("%s%d\n\n", "MotorDir: ", getMotorDir());
								}
}
