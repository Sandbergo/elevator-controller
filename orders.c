#include <stdio.h>

#include "elev.h"
#include "states.h"
#include "orders.h"
#include "channels.h"
//!!!!!! button, floor??!!!!!!!!!!!!!!!!!!!!!!!!!!!
int orderMatrix[N_BUTTONS][N_FLOORS] = {{0}};

void setOrdersHigh() {
	for(int button = 0; button <= BUTTON_COMMAND; button++) {
		for(int floorNum = 0; floorNum < N_FLOORS; floorNum++) {
			if (elev_get_button_signal(button, floorNum)) {
				orderMatrix[button][floorNum] = 1;
				elev_set_button_lamp(button, floorNum, 1); //flytt til egen funksjon
			}
		}
	}
}

void updateLights() {

}

//fjern alle ordre når emergency
void flushOrders(){
	for(int button = 0; button <= BUTTON_COMMAND; button++) {
		for(int floorNum = 0; floorNum < N_FLOORS; floorNum++) {
			orderMatrix[button][floorNum] = 0;
			elev_set_button_lamp(button, floorNum, 0);//flytt til egen funksjon
		}
	}
}


void printOrderMatrix(){
	printf("\n");
	for (int button = 0; button < N_BUTTONS; button++)
	{
		for(int floorNum = 0; floorNum < N_FLOORS; floorNum++)
			printf("%d     ", orderMatrix[button][floorNum]);
		printf("\n");
	}
	printf("\n");
}

int isButtonPressed(){
	for (int button = 0; button < N_BUTTONS; button++) {
		for (int floorNum = 0; floorNum < N_FLOORS; floorNum++) {
			if(orderMatrix[button][floorNum] == 1 ) {
				return 1;
			}
		}
	}
	return 0;
}


void setDir(int currentFloor){
	int upOrders = 0;
	int downOrders = 0;
	for(int floorNum = 0; floorNum < N_FLOORS; floorNum++) {
		if(orderMatrix[2][floorNum] == 1) {
			if(currentFloor < floorNum) {
				upOrders++;
			}
			else{
				downOrders++;
			}
		}
	}
	if(!upOrders && !downOrders) {
		return;
	}
	else if(upOrders > downOrders) {
		elev_set_motor_direction(1);
	}
	else{
		elev_set_motor_direction(-1);
	}

}

int floorIsOrdered(int floorNum){
	for (int button = 0; button < N_BUTTONS; button++) {
		if (orderMatrix[button][floorNum] == 1) {
			return 1;
		}
	}
	return 0;

}

void removeFromOrderMatrix(int floorNum){
	for (int button = 0; button < N_BUTTONS; button++) {
		orderMatrix[button][floorNum] = 0;
		elev_set_button_lamp(button, floorNum, 0);
	}
}
