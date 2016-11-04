#include "main.h"
#include "draw.h"

static void generate_maze(GtkWidget *widget, gpointer data)
{
	g_print("Generating New Maze\n");
}

static void activate (GtkApplication* app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *button_box;
	GtkWidget *displayarea;
	GtkWidget *grid;
	GtkWidget *frame;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "A* Pathfinding Demo");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	grid = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);
	gtk_container_add(GTK_CONTAINER(window), grid);

	displayarea = gtk_drawing_area_new();
	gtk_widget_set_size_request(displayarea, 501, 401);
	g_signal_connect(G_OBJECT(displayarea), "draw", G_CALLBACK(draw_callback), NULL);
	gtk_grid_attach(GTK_GRID(grid), displayarea, 0, 0, 1, 1);

	frame = gtk_frame_new("Controls");
	gtk_grid_attach(GTK_GRID(grid), frame, 0, 1, 1, 1);

	button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_set_border_width(GTK_CONTAINER(button_box), 10);
	gtk_container_add(GTK_CONTAINER(frame), button_box);

	button = gtk_button_new_with_label("Generate Maze");
	g_signal_connect(button, "clicked", G_CALLBACK(generate_maze), NULL);
	//g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
	gtk_container_add(GTK_CONTAINER(button_box), button);

	gtk_widget_show_all(window);

}

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	guint width, height;
	GdkRGBA color;
	GtkStyleContext *context;

	color.red = .5;
	color.green = 0;
	color.blue = 0;
	color.alpha = 1;

	context = gtk_widget_get_style_context(widget);

	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);

	gtk_render_background(context, cr, 0, 0, width, height);

	draw_lines(10, width, height, cr);

	return (FALSE);
}

int main(int argc, char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.gtk.astar", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return(status);
}
