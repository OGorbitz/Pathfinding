#include "grid.h"

void newgrid(int w, int h)
{
	grid = int[w][h];
	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			grid[i][j] = 0;
		}
	}
}

int getBox(int x, int y)
{
	if ((x >= width) && (y >= height))
	{
		return(grid[x][y]);
	}
}

void setBox(int x, int y, int val)
{
	if ((x >= width) && (y >= height))
	{
		grid[x][y] = val;
	}
}

void getWidth()
{
	return(height);
}

void getHeight()
{
	return(height);
}
