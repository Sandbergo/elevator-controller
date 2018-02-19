#include <stdio.h>

#include "elev.h"
#include "states.h"
#include "orders.h"
//!!!!!! button, floor??!!!!!!!!!!!!!!!!!!!!!!!!!!!
int orderMatrix[N_FLOORS][N_BUTTONS] = {{0}};

void setOrdersHigh() {
	for(int button = 0; button <= BUTTON_COMMAND; button++) {
		for(int floorNum = 0; floorNum < N_FLOORS; floorNum++) {
			if (elev_get_button_signal(button, floorNum)) {
				orderMatrix[floorNum][button] = 1
				                                elev_set_button_lamp(button, floorNum, 1);
			}
		}
	}
}

//updateLight

//removeOrder(int floor) {}

void flushOrders(){
	lamp_channel_matrix[N_FLOORS][N_BUTTONS] = {{0}};
	button_channel_matrix[N_FLOORS][N_BUTTONS] = {{0}};
}


void printOrderMatrix(){
	printf("\n");
	int row,columns;
	for (row = 0; row < 3; row++)
	{
		for(columns = 0; columns< N_FLOORS; columns++)
			printf("%d     ", queue[columns][row]);
		printf("\n");
	}
	printf("\n");
}
