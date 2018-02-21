#include <stdio.h>

#include "elev.h"
#include "states.h"
#include "orders.h"
#include "channels.h"
//!!!!!! button, floor??!!!!!!!!!!!!!!!!!!!!!!!!!!!
int orderMatrix[N_FLOORS][N_BUTTONS] = {{0}};
int orderList [4] = {0,0,0,0};

void setOrdersHigh() {
	for(int button = 0; button <= BUTTON_COMMAND; button++) {
		for(int floorNum = 0; floorNum < N_FLOORS; floorNum++) {
			if (elev_get_button_signal(button, floorNum)) {
				orderMatrix[floorNum][button] = 1;
				elev_set_button_lamp(button, floorNum, 1); //flytt til egen funksjon 
			}
		}
	}
}

//updateLights()

//removeOrder(int floor) {}

void flushOrders(){ //fjern alle ordre når emergency
	for(int button = 0; button <= BUTTON_COMMAND; button++) {
		for(int floorNum = 0; floorNum < N_FLOORS; floorNum++) {
			if (elev_get_button_signal(button, floorNum)) {
				orderMatrix[floorNum][button] = 0;
				elev_set_button_lamp(button, floorNum, 0);//flytt til egen funksjon 
			}
		}
	}

}


void printOrderMatrix(){
	printf("\n");
	int row,columns;
	for (row = 0; row < 3; row++)
	{
		for(columns = 0; columns< N_FLOORS; columns++)
			printf("%d     ", orderMatrix[columns][row]);
		printf("\n");
	}
	printf("\n");
}

int isButtonPressed(){
	for (int i = 0; i < N_FLOORS; i++){
		for (int j = 0; j < N_BUTTONS; j++){
			if(orderMatrix[i][j] == 1 ){
				return 1;
			}
		}
	}
	return 0;
}


int setDir(){
	switch(elev_get_floor_sensor_signal()+1){
		case 0:

			break;
		case 1:
			if(orderList[0]-1 > 0){
				elev_set_motor_direction(1);
			}
			else{
				elev_set_motor_direction(0);
			} 
			break;
		case 2:
			if(orderList[0]-2 > 0){
				elev_set_motor_direction(1);
			}
			else if(orderList[0]-2 < 0){
				elev_set_motor_direction(-1);
			}
			else {
				elev_set_motor_direction(0);
			}
			break;
		case 3:
			if(orderList[0]-3 > 0){
				elev_set_motor_direction(1);
			}
			else if(orderList[0]-3 < 0){
				elev_set_motor_direction(-1);
			}
			else {
				elev_set_motor_direction(0);
			}

			break;
		case 4:
			if(orderList[0]-4 < 0){
				elev_set_motor_direction(-1);
			}
			else{
				elev_set_motor_direction(0);
			} 
			break;
	}
}
int inList(int list[], int number){
	for (int i = 0; i < N_FLOORS; i++){
		if (list[i] == number){
			return 1;
		}
	}
	return 0;

}

void removeFromOrderList(int floor){
	for(int i = 0; i < 4; i++){
		orderList[i] = 0;
	}
	flushOrders();
}

void updateOrderList(){
	for(int i = 0; i < N_FLOORS; i++){
		if(orderMatrix[i][2] == 1 && !inList(orderList, i+1)){
			for(int j = 0; j < 4; j++){
				if(orderList[j] == 0){
					orderList[j] = i+1;
					return;
				}
			}
		}
		
	}

}

void printOrderList(){
	for(int i = 0; i < N_FLOORS; i++){
		printf("%d\t", orderList[i]);
	}
	printf("\n");
}

int getOrderListZero(){
	return orderList[0];
}