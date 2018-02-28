#pragma once

void startTimer(double length);

int getTimerStatus(); // returnerer 1 om timeren er gått ut

void timerDeactivate(); // avbryt timer

int isTimerActive(); // returner 1 om timeren er aktivert