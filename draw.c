#include "draw.h"

void draw_cell(int x, int y, GdkRGBA c, cairo_t *cr)
{
	draw_rectangle(c, x * d_cellsize, y * d_cellsize, d_cellsize, d_cellsize, cr);
}

void draw_update(guint w, guint h, GtkStyleContext *c, int s)
{
	d_width = w;
	d_height = h;
	d_context = c;
	d_cellsize = s;
}


void clear_canvas(float r, float g, float b, float a, cairo_t *cr)
{
	GdkRGBA color;
	color.red = 0.6;
	color.green = 0.6;
	color.blue = 1;
	color.alpha = 1;
	draw_rectangle(color, 0, 0, d_width, d_height, cr);
}

void draw_rectangle(GdkRGBA color, int x1, int y1, int x2, int y2, cairo_t *cr)
{
	cairo_set_source_rgba(cr, color.red, color.green, color.blue, color.alpha);
	cairo_rectangle(cr, x1, y1, x2, y2);
	cairo_fill(cr);
}

void draw_lines(cairo_t *cr)
{

	GdkRGBA color;
	color.red = 0;
	color.green = 0;
	color.blue = 0;
	color.alpha = 1;
	cairo_set_source_rgba(cr, color.red, color.green, color.blue, color.alpha);
	int x = (d_cellsize / d_width) + 1;
	int y = (d_cellsize / d_height) + 1;

	cairo_set_line_width(cr, 0.5);

	for (int i = 0; i <= d_width; i += d_cellsize)
	{
		cairo_move_to(cr, i, 0);
		cairo_line_to(cr, i, d_height);
	}
	for (int i = 0; i <= d_height; i += d_cellsize)
	{
		cairo_move_to(cr, 0, i);
		cairo_line_to(cr, d_width, i);
	}

	cairo_stroke(cr);
}
