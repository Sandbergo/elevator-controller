#pragma once

void setOrdersHigh(); // iterer gjennom knappene og sett matriseverdi høy viss en knapp er trykket inn

void flushOrders(); // fjern alle ordre og skru av lys

int isButtonPressed(); // returner 1 om en av ordreknappene er trykket, 0 ellers

int floorIsOrdered(int floorNum, int motorDir); // sjekk om vi skal stoppe i etasjen, returner 1 for ja

void removeFromOrderMatrix(int floorNum); // fjern etasje fra ordrelista, skru av lys

int setDirection(int currentFloor, int direction); // bestem hvilken retning som skal kjøres