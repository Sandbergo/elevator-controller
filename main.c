#include <stdio.h>
#include "elev.h"
#include "states.h"


int main() {
	
	// Initialize hardware
	
	if (!elev_init()) {
		printf("Unable to initialize elevator hardware!\n");
		return 1;
	}

	//kjør til etasje, sett til IDLE
	initStates();

	//loop
	while (1) {
		stateController();
	}
	return 0;
}