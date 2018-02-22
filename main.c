
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

	if (elev_get_floor_sensor_signal() == -1){
		elev_set_motor_direction(1);
		while(elev_get_floor_sensor_signal() == -1){
		}
	}
	previousState = IDLE;
	elev_set_motor_direction(0);

	while (1) {
		setOrdersHigh(); //oppdater ordre
		// Change direction when we reach top/bottom floor
				
		
		if (elev_get_floor_sensor_signal() != -1) {    //sjekk ordre, viss case emergency eller stopp skal alt ignoreres
			elev_set_floor_indicator(elev_get_floor_sensor_signal());
			setCurrentFloor(elev_get_floor_sensor_signal());
			update();
			
			//---------TODO----------//
			switch(previousState) {
				case INIT:

					break;
				case IDLE:
					printf("%s\n", "IDLE");
					if(isButtonPressed()){
						setDir(elev_get_floor_sensor_signal());
						previousState = RUN;
					}
					//do nuthin', venter på ordre
					break;
				case RUN:
					printf("%s\n", "RUN");
					if(floorIsOrdered(elev_get_floor_sensor_signal())){
						previousState = STOP;	
					}
				
					//set state til stopp viss det skal stoppes
					//sett igang timeren på tre sekunder
					break;
				case STOP:
					
					printf("%s\n", "STOP");
					elev_set_motor_direction(0);
					printOrderMatrix();
					//printOrderMatrix();
					if(!isTimerActive()){
						removeFromOrderMatrix(elev_get_floor_sensor_signal());
						
						startTimer(3);
					}
					if(getTimerStatus()){
						previousState = IDLE;
						timerDeactivate();
					}
					//sjekk timer, om den er gått ut skal state settes til IDLE
					break;
				case EMERGENCY:
					// do nuthin', skal ikke måtte implementeres
					break;
			}
		}

		// Stop elevator and exit program if the stop button is pressed
		emStop(elev_get_stop_signal());

		
	}
	return 0;
}
