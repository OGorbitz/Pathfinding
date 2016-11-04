#include "draw.h"

void draw_lines(int size, guint width, guint height, cairo_t *cr)
{
	GdkRGBA color;
	color.red = .1;
	color.green = .1;
	color.green = .1;
	color.alpha = 1;
	cairo_set_source_rgba(cr, color.red, color.green, color.blue, color.alpha);
	int x = (size / width) + 1;
	int y = (size / height) + 1;

	cairo_set_line_width(cr, 0.5);

	for (int i = 0; i <= width; i += size)
	{
		cairo_move_to(cr, i, 0);
		cairo_line_to(cr, i, height);
	}
	for (int i = 0; i <= height; i += size)
	{
		cairo_move_to(cr, 0, i);
		cairo_line_to(cr, width, i);
	}

	cairo_stroke(cr);
}
