#include <stdio.h>
#include <unistd.h>
#include "elev.h"
#include "states.h"
#include "orders.h"

//----------------VARIABLES-------------

static elevState currentState;

//initialisering, kanskje overflødig
int currentFloor = -1;

int previousFloor = -1;

int motorDir = 0;


//------------GET FUNCTIONS--------------

int getCurrentFloor(){
	return currentFloor;
}

int getPreviousFloor(){
	return previousFloor;
}

int getMotorDir(){
	return motorDir;
}


//------------SET FUNCTIONS--------------


void setMotorDir(int value){
	motorDir = value;
}

void setCurrentFloor(int value){
	currentFloor = value;
}

void setPreviousFloor(int value){
	previousFloor = value;

}


//-------------Other------------------

void init() {
	currentState = RUN;
}

void doorOpenClose(){
	elev_set_door_open_lamp(1);
	printf("%s\n","Door Open!");
	sleep(3);
	elev_set_door_open_lamp(0);
	printf("%s\n","Door Closed!");
}

void emStop(int isPushed){
	switch(currentState) {

	case INIT:
		return;

	case IDLE:
		if(isPushed) {
			currentState = EMERGENCY;
			elev_set_stop_lamp(1);
			elev_set_motor_direction(0);
			//clearOrders
		}
		break;
	case RUN:
		if(isPushed) {
			currentState = EMERGENCY;
			elev_set_stop_lamp(1);
			elev_set_motor_direction(0);

			if(elev_get_floor_sensor_signal() != -1) {
				elev_set_door_open_lamp(1);
				printf("%s\n", "Door Open!\n");
			}
		}
		break;
	case STOP:
		if(isPushed) {
			currentState = EMERGENCY;
			elev_set_stop_lamp(1);
		}

	case EMERGENCY:
		if(isPushed) {
			return;
		}
		else{
			if(elev_get_floor_sensor_signal() == -1) {
				currentState = IDLE;
				elev_set_door_open_lamp(0);
			}
			else{
				elev_set_stop_lamp(0);
				currentState = STOP;
				elev_set_door_open_lamp(1);
			}
			//flushOrders();
		}
	}
}

void update(){
	if(currentFloor != previousFloor) {
		setPreviousFloor(elev_get_floor_sensor_signal());
		printOrderMatrix(); //hjelpeprinting
		printf("%s%d\n", "Previous: ", previousFloor);
		printf("%s%d\n\n", "MotorDir: ", getMotorDir());

	}
}
