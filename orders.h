#pragma once

void setOrdersHigh();

void printOrderMatrix();

void flushOrders();

int isButtonPressed();

void updateOrderList();

int floorIsOrdered(int floorNum, int motorDir);

void removeFromOrderMatrix(int floorNum);

int setDir(int currentFloor, int direction);