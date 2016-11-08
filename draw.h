#include <stdio.h>
#include <gtk/gtk.h>

guint d_width, d_height;
GtkStyleContext *d_context;
int d_cellsize;

void clear_canvas(float r, float g, float b, float a, cairo_t *cr);
void draw_update(guint w, guint h, GtkStyleContext *c, int s);
void draw_lines(cairo_t *cr);
void draw_rectangle(GdkRGBA color, int x1, int y1, int x2, int y2, cairo_t *cr);
void draw_cell(int x, int y, GdkRGBA c, cairo_t *cr);
