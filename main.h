#include <stdio.h>
#include <gtk/gtk.h>

#include "pathfind.h"
#include "grid.h"
#include "draw.h"

long aps;
gboolean pathfinding = FALSE;
GtkWidget *start_button, *stop_button;

static void activate(GtkApplication* app, gpointer user_data);
gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data);

int main(int argc, char **argv);
