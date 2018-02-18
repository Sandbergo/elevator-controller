#include "timer.h"
#include <stdio.h>

static clock_t timerStarted; 
static int timerActive = 0;
static long double duration;

void startTimer(double length)
{
	timerStarted = clock(); 
	duration = length;
	timerActive = true;
}


int getTimerStatus()
{
	long double deltaTime = (long double)(clock() - timerStarted) / (CLOCKS_PER_SEC);
	if (deltaTime >= duration && timerActive)
	{
		return true;
	}
	return false;
