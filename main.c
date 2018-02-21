
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
					updateOrderList();
					if(isButtonPressed()){
						previousState = RUN;
						setDir();
					}
					//do nuthin', venter på ordre
					break;
				case RUN:
					printf("%s\n", "RUN");
					if(getOrderListZero() == elev_get_floor_sensor_signal() + 1){
						previousState = STOP;	
					}
				
					//set state til stopp viss det skal stoppes
					//sett igang timeren på tre sekunder
					break;
				case STOP:
					elev_set_motor_direction(0);
					removeFromOrderList();
					printOrderList();
					printOrderMatrix();
					startTimer(3);
					if(getTimerStatus()){
						previousState = IDLE;
						timerInterrupt();
					}
					//sjekk timer, om den er gått ut skal state settes til IDLE
					break;
				case EMERGENCY:
					// do nuthin', skal ikke måtte implementeres
					break;
			}
			//---------TODO----------//
		}
		//-----------------------MIDLERTIDIG--------------------------//
		/*if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
			elev_set_motor_direction(DIRN_STOP);
			setMotorDir(0);
			doorOpenClose();
			setPreviousFloor(4);
			elev_set_motor_direction(DIRN_DOWN);
			setMotorDir(-1);
			sleep(1);
		} else if (elev_get_floor_sensor_signal() == 0) {
			elev_set_motor_direction(DIRN_STOP);
			setMotorDir(0);
			//startTimer(3)
			//previousState = STOP
			sleep(3);
			elev_set_motor_direction(DIRN_UP);
			setMotorDir(1);
			sleep(1);
		}*/
		//-----------------------MIDLERTIDIG--------------------------//

		// Stop elevator and exit program if the stop button is pressed
		emStop(elev_get_stop_signal());

		
	}
	return 0;
}
