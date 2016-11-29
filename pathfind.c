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
	set_startdist(1, 1, 0);
	set_heuristic(1, 1, (23 - 1) + (19 - 1));

}

int pathfinding_cycle(void)
{
	//g_print("One cycle\n");
	//Do your thing joey

	int gx = 23, gy = 19;

	int min = 1000;
	int xm = 0, ym = 0;
	for(int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (get_status(i, j) == 1)
			{
				//g_print("Open box %d,%d new best\n", i, j);
				int d = get_totaldist(i, j);
				if (d < min)
				{
					xm = i;
					ym = j;
				}
			}
		}
	}
	//g_print("Checking %d,%d\n", xm, ym);
	set_status(xm, ym, 2);
	int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	for(int n = 0; n < 4; n++)
	{
		int xn = xm + dirs[n][0];
		int yn = ym + dirs[n][1];

		if(xn > get_width() - 1) {
			continue;
		}
		if(xn < 0) {
			continue;
		}
		if(yn > get_height() - 1) {
			continue;
		}
		if(yn < 0) {
			continue;
		}


		//g_print("x:%d y:%d t:%d\n", xn, yn, get_box(xn, yn));

		if(get_box(xn, yn) == 4)
		{
			g_print("Finish reached\n");
			//REACHED FINISH; BACKTRACE
			while(1 == 1)
			{
				int min = 1000;
				int mxm, mym;
				for(int m = 0; m < 4; m++)
				{
					int mxn = xn + dirs[m][0];
					int myn = yn + dirs[m][1];

					if(get_box(mxn, myn) == 3)
					{
						set_status(xn, yn, 5);
						return(0);
					}
					if(get_box(mxn, myn) == 1)
					{
						if(get_status(mxn,myn) == 2)
						{
							if(get_startdist(mxn, myn) < min)
							{
								min = get_startdist(mxn, myn);
								mxm = mxn;
								mym = myn;
							}
						}
					}
				}
				xn = mxm;
				yn = mym;
				set_status(xn, yn, 5);
			}
		} else if(get_box(xn, yn) == 1 || get_box(xn, yn) == 3) {
			if(get_status(xn, yn) == 0)
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
	return(1);
}

int pathfinding_reset(void)
{
	g_print("Pathfinding reset\n");
	//Reset the data here, restart the pathfinding
}
