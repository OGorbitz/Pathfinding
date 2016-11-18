#include "maze.h"

void maze_generate_init()
{
	g_print("Generating Maze\n");
	//It's all yours from here, cesar :D

	new_grid();

	w = get_width();
	h = get_height();

	mw = 12;
	mh = 10;

	for(int i = 0; i < mw; i++)
	{
		for(int j = 0; j < mh; j++)
		{
			maze[i][j] = 0;
		}
	}

	srand(time(NULL));
	x = rand() % (mw - 1);
	y = rand() % (mh - 1);
	parent[x][y] = -1;
	set_box(x * 2 + 1, y * 2 + 1, 1);
}

int maze_generate_tick()
{
	maze[x][y] = 1;
	//Decide which directions are valid
	//Create array of valid directions

	int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	int num = 0;
	int dirbuff[4];
	for (int db = 0; db < 4; db++)
	{
		dirbuff[db] = 0;
	}

	if(x + 1 < mw)
	{
		if(maze[x + 1][y] == 0)
		{
			num++;
			dirbuff[0] = 1;
		}
	}
	if(x > 0)
	{
		if(maze[x - 1][y] == 0)
		{
			num++;
			dirbuff[1] = 1;
		}
	}
	if(y + 1 < mh)
	{
		if(maze[x][y + 1] == 0)
		{
			num++;
			dirbuff[2] = 1;
		}
	}
	if(y > 0)
	{
		if(maze[x][y - 1] == 0)
		{
			num++;
			dirbuff[3] = 1;
		}
	}


	if(num > 0)
	{
		//DEBUG: g_print("Moving forward\n");
		//Pick an option

		int dir = (rand() % num);
		int finaldir;
		int n = 0, o = 0;
		while(1 == 1)
		{
			//DEBUG: g_print("dir:%d n:%d o:%d db:%d\n", dir, n, o, dirbuff[n + o]);

			if(n > 4 || o > 4)
				exit(0);

			if(dirbuff[n + o] == 1)
			{
				if(n == dir) {
					finaldir = n + o;
					break;
				} else {
					n++;
				}
			} else {
				o++;
			}
		}

		x += directions[finaldir][0];
		y += directions[finaldir][1];

		maze[x][y] = 1;
		//g_print("Made box (%d, %d) open\n", x*2, y*2);

		set_box((x * 2) + 1, (y * 2) + 1, 2);
		//g_print("Returned box value: %d\n", get_box(x * 2, y * 2));
		set_box((x * 2) + 1 - directions[finaldir][0], (y * 2) + 1 - directions[finaldir][1], 2);
		parent[x][y] = finaldir;

	} else {

		if(parent[x][y] == -1)
		{
			return(1);
		}

		//DEBUG: g_print("Backtracing\n");
		maze[x][y] = 2;

		set_box((x * 2) + 1 - directions[parent[x][y]][0], (y * 2) + 1 - directions[parent[x][y]][1], 1);
		set_box((x * 2) + 1, (y * 2) + 1, 1);
		int tx = x;
		x -= directions[parent[tx][y]][0];
		y -= directions[parent[tx][y]][1];
	}
	return(0);
}
