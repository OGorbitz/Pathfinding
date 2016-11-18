#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "grid.h"

int w, h, mw, mh, x, y;
int maze[12][10], parent[12][10], mazecon[12][10];

void maze_generate_init();
int maze_generate_tick();
