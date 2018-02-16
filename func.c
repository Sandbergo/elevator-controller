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

void doorOpenClose(){
	elev_set_door_open_lamp(1);
	printf("%s\n","Door Open!");
	sleep(3);
	elev_set_door_open_lamp(0);
	printf("%s\n","Door Closed!");
}

void emStop(){
	printf("%s\n","The elevator is in ''Emergency Stop Mode!''");
	elev_set_motor_direction(0);
	elev_set_stop_lamp(1);
	while(!elev_get_stop_signal()){
	printf("%s\n", "DO NOT PANIC!");
	}
	elev_set_stop_lamp(0);
}

void update(){
	if(currentFloor != previousFloor){
	    setPreviousFloor(elev_get_floor_sensor_signal());
	    printf("%s%d\n", "Previous: ", previousFloor);
            printf("%s%d\n\n", "MotorDir: ", getMotorDir());
	}
}
