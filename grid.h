#include <stdio.h>
#include "pathfind.h"

int grid[25][20][4];		//DO NOT DIRECTLY ACCESS THIS ARRAY! USE THE FUNCTIONS BELOW!

int width, height;	//DO NOT DIRECTLY ACCESS THIS ARRAY! USE THE FUNCTIONS BELOW!

void new_grid(void);			//Used to clear the grid and setup a new one
int get_box(int x, int y);			//Used to get the value of a certain position on the grid
void set_box(int x, int y, int val);		//Used to set the value of a certain position on the grid
int get_width();					//Returns width of grid
int get_height();				//Returns height of grid


//A* Stuff here:
int get_startdist(int x, int y);
int get_heuristic(int x, int y);
int get_totaldist(int x, int y);
int get_status(int x, int y);		//1 is open, 2 is closed, 0 is unknown
