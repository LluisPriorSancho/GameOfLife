#ifndef COMMON_H
#define COMMON_H

// Define the struct of a cell, it has x and y that tells the location of the cell
typedef struct
{
  int x;
  int y;
  int alive_neighbor;
} cell;

// Define the struct of the array of cells.
typedef struct
{
  cell   *array;
  size_t array_length;
  size_t memory_length;
} array_cells;

#endif