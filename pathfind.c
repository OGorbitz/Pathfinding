#include "pathfind.h"

void pathfinding_init(void)
{
	for(int i = 0; i < 25; i++)
	{
		for(int j = 0; j < 21; j++)
		{
			set_status(i, j, 0);
		}
	}

	set_status(1, 1, 1);
	set_box(1, 1, 3);
	set_box(23, 18, 4);
}

int pathfinding_cycle(void)
{
	//g_print("One cycle\n");
	//Do your thing joey

	int gx = 23, gy = 18;

	int min = 25 + 21;
	int xm, ym;
	for(int i = 0; i < 25, i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (get_status(i, j) == 1)
			{
				int d = get_totaldist(i, j);
				if (d < min)
				{
					xm = i;
					ym = j;
				}
			}
		}
	}
	set_status(xm, ym, 2);
	int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	for(int n = 0; n < 4; n++)
	{
		int xn = xm + dirs[n][0];
		int yn = ym + dirs[n][1];
		if(get_box(xn, yn) == 4)
		{
			//REACHED FINISH; BACKTRACE
		} else if(get_box(xn, yn) == 1) {
			if(get_status(xn, yn) == 1)
			{
				//ADD TO OPEN LIST AND COMPUTE SCORE
				set_status(xn, yn, 1);
				set_startdist(xn, yn, get_startdist(xm, ym) + 1);
				set_heuristic(xn, yn, (gx - xn) + (gy - yn));
			} else if(get_status(xn, yn) == 1) {
				//UPDATE SCORE IF NECESSARY
				int sd = get_startdist(xm + dirs[n][0], ym + dirs[n][1]);
				if(sd > get_startdist(xm, ym) + 1)
				{
					set_startdist(xn, yn, get_startdist(xm, ym) + 1);
				}
			}
		}
	}
}

int pathfinding_reset(void)
{
	g_print("Pathfinding reset\n");
	//Reset the data here, restart the pathfinding
}
