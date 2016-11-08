#include <stdio.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include <semaphore.h>

#include "pathfind.h"
#include "grid.h"
#include "draw.h"
#include "maze.h"

long aps = 1;
gboolean pathfinding = FALSE;
GtkWidget *start_button, *stop_button, *reset_button;
pthread_t loopthread;

static void activate(GtkApplication* app, gpointer user_data);
gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data);

int main(int argc, char **argv);
void * pf_loop(void *param);
