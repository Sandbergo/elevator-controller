#include <stdio.h>
#include <unistd.h>
#include "elev.h"
#include "states.h"
#include "orders.h"

//----------------VARIABLES-------------

static elevState currentState;


//-------------Other------------------

void init() {
	currentState = RUN;
	if (elev_get_floor_sensor_signal() == -1) {
		elev_set_motor_direction(1);
		while(elev_get_floor_sensor_signal() == -1) {
		}
	}
	elev_set_motor_direction(0);
}

int emStop(){
	switch(currentState) {

	case INIT:
		return 0;

	case IDLE:
		currentState = EMERGENCY;
		elev_set_stop_lamp(1);
		elev_set_motor_direction(0);
	
		break;
	case RUN:
	
		currentState = EMERGENCY;
		elev_set_stop_lamp(1);
		elev_set_motor_direction(0);

		if(elev_get_floor_sensor_signal() != -1) {
			elev_set_door_open_lamp(1);
		}
	
		else {
			currentState = IDLE;
		}
		break;
	case STOP:
	
		currentState = EMERGENCY;
		elev_set_stop_lamp(1);

		currentState = IDLE;
		break;

	case EMERGENCY:
	    flushOrders();	
		elev_set_motor_direction(0);
		while(elev_get_stop_signal()) {
		}

		elev_set_stop_lamp(0);
		
		if(elev_get_floor_sensor_signal() == -1) {
			currentState = IDLE;
			elev_set_door_open_lamp(0);
			return -1;	
		}
		else{
			elev_set_stop_lamp(0);
			currentState = STOP;
			elev_set_door_open_lamp(1);
			return 1;
		}
	}
	return -1; // safety
}