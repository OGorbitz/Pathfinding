#include <stdio.h>

int grid[25][21][5];		//DO NOT DIRECTLY ACCESS THIS ARRAY! USE THE FUNCTIONS BELOW!
//[0]: 0: solid, 1: open, 2: mazegen, 3: start, 4: end, 5: rtnpath
//[1]: Status
//[2]: Dist from start
//[3]: Heuristic
//[4]: Total Distance

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

void set_startdist(int x, int y, int val);
void set_heuristic(int x, int y, int val);
void set_status(int x, int y, int val);
