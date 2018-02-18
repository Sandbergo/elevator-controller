#include "elev.h"
#include "func.h"
#include "orders.h"

// update matrix
static int ROWS = 3;
static int COLS = 4;
int orderMatrix[ROWS][COLS] =  {{0}};

void updateOrders() {
	for(int i = 0; i <= ROWS; i++) {
		for(int i = 0; j <= COLS; i++) {
			getOrderValue(i, j);
		}
	}
}

void setOrder(row, col, value){
	orderMatrix(row, col) = value;
}

int getOrderValue(row, col){
	return 0;
}
