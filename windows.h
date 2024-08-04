#ifndef WINDOWS_H_INCLUDED
#define WINDOWS_H_INCLUDED

#define X_BORDER        34
#define Y_BORDER        17

//GameOfLife
#include "common.h"


WINDOW *winGame;
WINDOW *winSettings;
WINDOW *winPrev;
unsigned int xWinMax, yWinMax;
array_cells lifeList;
array_cells deadList;
array_cells newGenList;
unsigned int ite;

void initColors();
void plotGeneration(array_cells *, WINDOW *, int, int, unsigned int);
void chargeInfo();
void choosePattern(int, array_cells *);
void restart (array_cells *, array_cells *, array_cells *);

#endif
