#include "timer.h"
#include <stdio.h>
#include <time.h>

static clock_t timerStarted; 
static int timerActive = 0;
static double duration;

void startTimer(double length)
{
	timerStarted = clock(); 
	duration = length;
	timerActive = 1;
}


int getTimerStatus()
{
	long double deltaTime = (long double)(clock() - timerStarted) / (CLOCKS_PER_SEC);
	if (deltaTime >= duration && timerActive)
	{
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