#include <stdio.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include <semaphore.h>
#include <X11/Xlib.h>

#include "pathfind.h"
#include "grid.h"
#include "draw.h"
#include "maze.h"

long aps = 1, cps = 1;
gboolean pathfinding = FALSE, pathfind_immediate = FALSE;
GtkWidget *start_button, *stop_button, *reset_button, *b_genmaze;
GtkWidget *displayarea;
pthread_t loopthread, genthread;
cairo_t *cairo;
GtkWidget *dwidget;

static void activate(GtkApplication* app, gpointer user_data);

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data);

int main(int argc, char **argv);
void request_dpu(void);
void * pf_loop(void *param);
void * mg_loop(void *param);
