#include <stdio.h>
#include <gtk/gtk.h>

#include "pathfind.h"
#include "grid.h"
#include "draw.h"

static void activate(GtkApplication* app, gpointer user_data);
gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data);

int main(int argc, char **argv);
