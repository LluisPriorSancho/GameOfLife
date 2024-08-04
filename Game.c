#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Game.h"
#include "common.h"

// Creates Array of Cells with dynamic memory allocation
array_cells initCellArray()
{
  array_cells init_array;
  init_array.memory_length = 1; // Start with one slot
  init_array.array_length = 0;
  init_array.array  = malloc(init_array.memory_length * sizeof(cell));
  return init_array;
}

// Add cell to array by expanding memory by one
void addCellToArray(array_cells *arrayCells, cell newCell)
{
  arrayCells->memory_length += 1; //We expand the memory by one each time
  arrayCells->array = realloc(arrayCells->array, arrayCells->memory_length * sizeof(newCell));
  arrayCells->array[arrayCells->array_length++] = newCell;
}

// Remove cell from array
void removeCellFromArray(array_cells *arrayCells, int cellIndex)
{
  unsigned int i = 0;
  if (cellIndex > arrayCells->array_length){
    printf("Error removing cell. Index out of bounds\n");
  }
  else{
    for (i=cellIndex; i < arrayCells->memory_length; i++){
      arrayCells->array[i] = arrayCells->array[i+1];
    }
    arrayCells->memory_length -= 1; //We decrease the memory by one
    arrayCells->array_length -= 1;
    arrayCells->array = realloc(arrayCells->array, arrayCells->memory_length * sizeof(cell));
  }
}

// Delete Array of Cells from the memory
void freeMemory(array_cells *arrayCells)
{
  free(arrayCells->array);
  arrayCells->array  = NULL;
  arrayCells->array_length = 0;
  arrayCells->memory_length = 0;
}

// Function to process the LifeList and generate NeighborList and NonNeighborList
void game(array_cells *lifeList, array_cells *deadList, array_cells *newGenList) {
  unsigned int i=0, deadIndex = 0;
    cell cell_i;
    for (i = 0; i < lifeList->array_length  ; i++) {
        cell_i = lifeList->array[i];
        // Generate dead cells list
        generateAndIdentifyDeadCells(cell_i, lifeList, deadList);
        lifeList->array[i].alive_neighbor = 8 - (deadList->array_length - deadIndex);
        deadIndex = deadList->array_length;
    }

    removeDuplicates(deadList);
    // Calculate neighbors and non-neighbors
    for (i = 0; i < deadList->array_length; i++){
       calculateNeighbors(lifeList, deadList, i);
    }
  rules(lifeList, deadList, newGenList);
}

// Function to generate a list of dead cells around a given point and identify them
void generateAndIdentifyDeadCells(cell cell_i, array_cells *lifeList, array_cells *deadList) {
  unsigned int i = 0;
  int dx = -1;
  int dy = -1;
  cell cell_dead;
  unsigned int isAlive = 0;
  for ( dx = -1; dx <= 1; dx++) {
      for ( dy = -1; dy <= 1; dy++) {
          if (dx == 0 && dy == 0) {
              continue; // Skip the central cell itself
          }
          cell_dead.x = cell_i.x + dx;
          cell_dead.y = cell_i.y + dy;
          cell_dead.alive_neighbor = 0;
          isAlive = 0;
          for (i = 0; i < lifeList->array_length; i++) {
              if (lifeList->array[i].x == cell_dead.x && lifeList->array[i].y == cell_dead.y) {
                  isAlive = 1;
                  break;
              }
          }
          if (!isAlive) {
              addCellToArray(deadList, cell_dead);
          }
      }
  }
}

// Function to delete the repeated elements of a list
void removeDuplicates(array_cells *deadList) {
  unsigned int i = 0;
  unsigned int j = 0;
    for (i = 0; i < deadList->array_length; i++) {
        for (j = i + 1; j < deadList->array_length;j++) {
            if (deadList->array[i].x == deadList->array[j].x && deadList->array[i].y == deadList->array[j].y) {
                  removeCellFromArray(deadList, j);
                  j--;
            }
        }
    }
}

// Function to calculate the number of neighbors for a point (x, y)
void calculateNeighbors(array_cells *lifeList, array_cells *deadList, int indexCell) {
    unsigned int i = 0;
    for (i = 0; i < lifeList->array_length; i++) {

        if (lifeList->array[i].x == deadList->array[indexCell].x && lifeList->array[i].y == deadList->array[indexCell].y) {
            continue; // Skip the central cell itself
        }

        if (abs(deadList->array[indexCell].x - lifeList->array[i].x) <= 1 && abs(deadList->array[indexCell].y - lifeList->array[i].y) <= 1) {
            deadList->array[indexCell].alive_neighbor += 1;
        }
    }
}

void rules( array_cells *lifeList, array_cells *deadList, array_cells *newGenList){
    // life <2 dies
    // life =2, =3 stays
    // life >3 dies
    // dead =3 lives

    unsigned int i = 0;
    for (i = 0; i < lifeList->array_length; i++){
        if (lifeList->array[i].alive_neighbor <2){
            continue;
        }

        if (lifeList->array[i].alive_neighbor == 2 || lifeList->array[i].alive_neighbor == 3){
            addCellToArray(newGenList, lifeList->array[i]);
            continue;
        }

        if (lifeList->array[i].alive_neighbor > 3){
            continue;
        }
    }

    for (i = 0; i < deadList->array_length; i++){
        if (deadList->array[i].alive_neighbor == 3){
          addCellToArray(newGenList, deadList->array[i]);
        }
    }
}