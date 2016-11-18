#include <gtk/gtk.h>

#include "grid.h"

void new_grid(void)
{
	width = 25;
	height = 21;
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			grid[i][j][0] = 0;
		}
	}
}

int get_box(int x, int y)
{
	//DEBUG: g_print("Box value: %d  x:%d y:%d\n", grid[x][y][0], x, y);

	if ((x < width) && (y < height))
	{
		return(grid[x][y][0]);
	}
}

void set_box(int x, int y, int val)
{
	//DEBUG: g_print("Setting box to %d\n", val);

	if ((x < width) && (y < height))
	{
		grid[x][y][0] = val;
	}
}

int get_width()
{
	return(width);
}

int get_height()
{
	return(height);
}

int get_startdist(int x, int y)
{
	if ((x < width) && (y < height))
	{
		return(grid[x][y][2]);
	}
	return(100);
}

int get_heuristic(int x, int y)
{
	if ((x < width) && (y < height))
	{
		return(grid[x][y][3]);
	}
	return(100);
}

int get_totaldist(int x, int y)
{
	if ((x < width) && (y < height))
	{
		return(get_heuristic(x, y) + get_startdist(x, y));
	}
	return(100);
}

int get_status(int x, int y)
{
	if ((x < width) && (y < height))
	{
		return(grid[x][y][1]);
	}
	return(0);
}

void set_startdist(int x, int y, int val)
{
	if ((x < width) && (y < height))
	{
		grid[x][y][2] = val;
	}
}

void set_heuristic(int x, int y, int val)
{
	if ((x < width) && (y < height))
	{
		grid[x][y][3] = val;
	}
}

void set_status(int x, int y, int val)
{
	if ((x < width) && (y < height))
	{
		grid[x][y][1] = val;
	}
}
