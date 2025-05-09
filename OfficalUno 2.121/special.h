#ifndef SPECIAL_H_INCLUDED
#define SPECIAL_H_INCLUDED

#include "graphics.h"

// ai win
bool aiWin[3] = {false};

int timeLeft = 100;
bool backToMenu = false;
int isSkip = 0;
bool showCumText = true;
double arrowY = 210;
bool arrowDown = false;
string tmpColor;
int dd = 60; // khoảng cách 2 mép bài
bool isStacked = false;
bool forcePLay = false;
bool drawToMatch = false;
Uint32 frame;
int delayTime = 50;
int speed = 10;
#endif // SPECIAL_H_INCLUDED
