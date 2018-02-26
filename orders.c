#include <stdio.h>
#include <assert.h>
#include "elev.h"
#include "states.h"
#include "orders.h"
#include "channels.h"

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


void flushOrders(){ //fjern alle ordre når emergency
	for(int button = 0; button <= BUTTON_COMMAND; button++) {
		for(int floorNum = 0; floorNum < N_FLOORS; floorNum++) {
			orderMatrix[button][floorNum] = 0;
			elev_set_button_lamp(button, floorNum, 0);
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


int setDir(int currentFloor, int direction){
	
	assert(currentFloor >= 0);
    assert(currentFloor < N_FLOORS);
	
	int upOrders = 0;
	int downOrders = 0;
	
	for (int button = 0; button < N_BUTTONS; button++) {
		for(int floorNum = 0; floorNum < N_FLOORS; floorNum++) {
			if(orderMatrix[button][floorNum] == 1) {
				if(currentFloor < floorNum) {
					upOrders++;
				}
				else{
					downOrders++;
				}
			}
		}
	}

	if(upOrders > downOrders) {
		return 1;
	}
	else{
		return -1;
	}
}


int floorIsOrdered(int floorNum, int motorDir){
	
	int floorBeyond;
	//uansett
	if (orderMatrix[2][floorNum] == 1) {
		return 1;
	}
	//står i ro
	if(motorDir == 0){
		if((orderMatrix[0][floorNum] == 1 ) || (orderMatrix[1][floorNum] == 1))  {
			return 1;
		}
	}

	//kjører opp
	if(motorDir == 1){
		floorBeyond = 0;
		for (int button = 0; button < 2; button++) {
			for(int i = floorNum + 1; i < N_FLOORS; i++){
				floorBeyond += orderMatrix[button][i];
			}
		}
		if (orderMatrix[0][floorNum] == 1) {
			return 1;
		}
		else if (orderMatrix[1][floorNum] && (floorBeyond == 0)) {
			return 1;
		}
	}
	//kjører ned
	if(motorDir == -1){
		floorBeyond = 0;
		for (int button = 0; button < 2; button++) {
			for(int i = 0; i < floorNum; i++){
				floorBeyond += orderMatrix[button][i];
			}
		}

		if (orderMatrix[1][floorNum] == 1) {
			return 1;
		}
		else if (orderMatrix[0][floorNum] && (floorBeyond == 0)) {
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