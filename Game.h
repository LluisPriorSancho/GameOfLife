#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/* Define Functions */
// Creates Array of Cells with dynamic memory allocation
array_cells initCellArray();

// Add cell to array by expanding memory by one
void addCellToArray(array_cells *, cell);

// Remove cell from array
void removeCellFromArray(array_cells *, int);

// Delete Array of Cells from the memory
void freeMemory(array_cells *);

// Function to process the LifeList and generate NeighborList and NonNeighborList
void game(array_cells *, array_cells *, array_cells *);

// Function to generate a list of dead cells around a given point and identify them
void generateAndIdentifyDeadCells(cell, array_cells *, array_cells *);

void removeDuplicates(array_cells *);

// Function to calculate the number of neighbors for a point (x, y)
void calculateNeighbors(array_cells *, array_cells *, int);

void rules( array_cells *, array_cells *, array_cells *);

#endif
