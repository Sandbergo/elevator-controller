#include "timer.h"
#include <time.h>

static clock_t timerStarted; // tidspunkt timeren startes
static int timerActive = 0; //om timeren er aktiv
static double duration; // varighet for timeren


void startTimer(double length) {
	timerStarted = clock(); 
	duration = length;
	timerActive = 1;
}


int getTimerStatus() { // returnerer 1 om timeren er gått ut
	long double deltaTime = (long double)(clock() - timerStarted) / (CLOCKS_PER_SEC); 
	if (deltaTime >= duration && timerActive) {
		return 1;
	}
	return 0;
}


void timerDeactivate() {
	timerActive = 0;
}


int isTimerActive() {
	return timerActive;
}