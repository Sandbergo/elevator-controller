#include <stdio.h>

#include "elev.h"
#include "func.h"
#include "orders.h"

// update matrix
//lamp_channel_matrix[N_FLOORS][N_BUTTONS];
//button_channel_matrix[N_FLOORS][N_BUTTONS];

void setOrdersHigh() {
	int updatedLight = 0;
	for(int button = 0; button <= BUTTON_COMMAND; button++) {
		for(int floorNum = 0; floorNum < N_FLOORS; floorNum++) {
			if (elev_get_button_signal(button, floorNum)) {
				//lamp_channel_matrix[button][floorNum] = 1;
				//button_channel_matrix[button][floorNum] = 1;
				elev_set_button_lamp(button, floorNum, 1);
				if(!updatedLight) {
					printf("%s%d%s%d\n", "Order for:", button
					       , " - ", floorNum);
				}
				updatedLight = 1;
			}
		}
	}
}
