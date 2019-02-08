#include <assert.h>
#include "elev.h"
#include "orders.h"


int orderMatrix[N_BUTTONS][N_FLOORS] = {{0}}; // ordrematrise


void setOrdersHigh() {
	for(int button = 0; button <= BUTTON_COMMAND; button++) {
		for(int floorNum = 0; floorNum < N_FLOORS; floorNum++) {
			if (elev_get_button_signal(button, floorNum)) {
				orderMatrix[button][floorNum] = 1; // sett en bestillingscelle logisk høy
				elev_set_button_lamp(button, floorNum, 1); // lys opp knapper
			}
		}
	}
}


void flushOrders(){ 
	for(int button = 0; button <= BUTTON_COMMAND; button++) {
		for(int floorNum = 0; floorNum < N_FLOORS; floorNum++) {
			orderMatrix[button][floorNum] = 0; // sett bestillingscelle logisk false
			elev_set_button_lamp(button, floorNum, 0); // skru av lys
		}
	}
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


int setDirection(int currentFloor, int lastDirection){
	
	assert(currentFloor >= 0);
    assert(currentFloor < N_FLOORS);
	
	//viss vi er mellom etasjer etter emergency stop, 
	//regner vi ut en float som tilsvarer en mellomposisjon
	if(elev_get_floor_sensor_signal() == -1){ 
		(float) currentFloor;
		currentFloor = currentFloor + lastDirection/2.0;
	}

	int upOrders = 0;
	int downOrders = 0;
	
	//sjekker om bestillingen er over eller under posisjonen
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

	//sammenligner og gjør en prioritering
	if(upOrders > downOrders) {
		return 1;
	}
	else{ // default er å kjøre ned 
		return -1;
	}
}


int floorIsOrdered(int floorNum, int motorDir){
	
	int floorBeyond;
	// heispanelbestillinger utføres uansett
	if (orderMatrix[2][floorNum] == 1) {
		return 1;
	}
	//viss heisen står i ro
	if(motorDir == 0){
		if((orderMatrix[0][floorNum] == 1 ) || (orderMatrix[1][floorNum] == 1))  {
			return 1;
		}
	}

	//viss heisen kjører opp
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
	
	//viss heisen kjører ned
	if(motorDir == -1){
		floorBeyond = 0; // om det er bestillinger forbi etasjen den er i
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