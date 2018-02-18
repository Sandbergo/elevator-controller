#include "elev.h"
#include "func.h"
#include "orders.h"

// update matrix
//lamp_channel_matrix[N_FLOORS][N_BUTTONS];
//button_channel_matrix[N_FLOORS][N_BUTTONS];

void setOrdersHigh() {
	for(int button = BUTTON_CALL_UP; button <= BUTTON_COMMAND; button++) {
		for(int floorNum = 0; floorNum <= N_FLOORS; floorNum++) {
			if (elev_get_button_signal(button, floorNum)) {
				//lamp_channel_matrix[button][floorNum] = 1;
				//button_channel_matrix[button][floorNum] = 1;
				elev_set_button_lamp(button, floorNum, 1);
				printf("%d%s%d\n", button, " : ", floorNum);
			}
		}
	}
}
