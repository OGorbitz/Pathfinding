#include <stdio.h>
#include "pathfind.h"


int grid[][];		//DO NOT DIRECTLY ACCESS THIS ARRAY! USE THE FUNCTIONS BELOW!
int width, height;	//DO NOT DIRECTLY ACCESS THIS ARRAY! USE THE FUNCTIONS BELOW!

void newGrid(int w, int h);			//Used to clear the grid and setup a new one
int getBox(int x, int y);			//Used to get the value of a certain position on the grid
void setBox(int x, int y, int val);		//Used to set the value of a certain position on the grid
int getWidth();					//Returns width of grid
int getHeight();				//Returns height of grid
