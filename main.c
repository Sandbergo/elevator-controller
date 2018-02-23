
#include <stdio.h>
#include <unistd.h>
#include "elev.h"
#include "states.h"
#include "orders.h"
#include "timer.h"
#include "io.h"

int main() {
	// Initialize hardware

	elevState previousState = INIT; // nødvendig?
	if (!elev_init()) {
		printf("Unable to initialize elevator hardware!\n");
		return 1;
	}

	//elev_set_motor_direction(DIRN_UP);
	//setMotorDir(1);
	init();

	if (elev_get_floor_sensor_signal() == -1) {
		elev_set_motor_direction(1);
		while(elev_get_floor_sensor_signal() == -1) {
		}
	}
	previousState = IDLE;
	int currentFloorLocation = -1;
	int previousMainFloor = -1;
	int emStopState = 0;
	int lastFloorEm = -1;
	elev_set_motor_direction(0);

	while (1) {
		setOrdersHigh(); //oppdater ordre
	
		currentFloorLocation = elev_get_floor_sensor_signal();

		if ((currentFloorLocation != -1) || (lastFloorEm != -1)) {    //sjekk ordre, viss case emergency eller stopp skal alt ignoreres
			if (lastFloorEm != -1) {
				previousMainFloor = lastFloorEm;
			}
			else {
				previousMainFloor = currentFloorLocation;
			}
			
			update();

			switch(previousState) {
			case INIT:

				break;
			case IDLE:
				printf("%s\n", "IDLE");
				if(isButtonPressed()) {
					setDir(previousMainFloor);
					previousState = RUN;
				}
				//do nuthin', venter på ordre
				break;
			case RUN:
				printf("%s\n", "RUN");
				if(floorIsOrdered(previousMainFloor)) {
					previousState = STOP;
				}
				lastFloorEm = -1;
				//set state til stopp viss det skal stoppes
				//sett igang timeren på tre sekunder
				break;
			case STOP:

				printf("%s\n", "STOP");
				elev_set_motor_direction(0);
				printOrderMatrix();
				//printOrderMatrix();
				if(!isTimerActive() && (elev_get_floor_sensor_signal()!=-1)) {
					removeFromOrderMatrix(previousMainFloor);
					startTimer(3);
					elev_set_door_open_lamp(1);
				}
				if(getTimerStatus()) {
					previousState = IDLE;
					timerDeactivate();
					elev_set_door_open_lamp(0);
				}
				//sjekk timer, om den er gått ut skal state settes til IDLE
				break;
			case EMERGENCY:
				// do nuthin', skal ikke måtte implementeres
				break;
			}
		}

		// Stop elevator and exit program if the stop button is pressed
		if(elev_get_stop_signal()){
			emStopState = emStop(1);
			if(emStopState == -1){
				previousState = IDLE;
				lastFloorEm = previousMainFloor;
				
			}
			else {
				previousState = STOP;
			}
			printf("%s\n", "git out");
		}
	}
	return 0;
}
