#include "grid.h"

void new_grid(void)
{
	for(int i = 0; i < 25; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			//grid[i][j] = 0;
		}
	}
}

int get_box(int x, int y)
{
	if ((x >= width) && (y >= height))
	{
		return 1;//return(grid[x][y]);
	}
}

void set_box(int x, int y, int val)
{
	if ((x >= width) && (y >= height))
	{
		//grid[x][y] = val;
	}
}

int get_width()
{
	return(height);
}

int get_height()
{
	return(height);
}
