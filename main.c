#include "main.h"


static void speed_changed(GtkWidget *widget, gpointer *data)
{
	long x = gtk_range_get_value(GTK_RANGE(widget));
	g_print("Speed set to %ld actions per second\n", x);
	aps = x;
}

static void start_pathfinding(GtkWidget *widget, gpointer data)
{
	pathfinding = TRUE;
	g_print("Pathfinding started at %ld aps\n", aps);
	gtk_widget_set_sensitive(widget, FALSE);
	gtk_widget_set_sensitive(stop_button, TRUE);
	gtk_widget_set_sensitive(reset_button, TRUE);

	if (loopthread)
	{
		pthread_create(&loopthread, NULL, pf_loop, NULL);
	} else {
		pthread_cancel(loopthread);
		pthread_create(&loopthread, NULL, pf_loop, NULL);
	}
}

static void stop_pathfinding(GtkWidget *widget, gpointer data)
{
	pathfinding = FALSE;
	g_print("Pathfinding halted\n");
	gtk_widget_set_sensitive(widget, FALSE);
	gtk_widget_set_sensitive(start_button, TRUE);

	pthread_cancel(loopthread);
}

static void reset_pathfinding(GtkWidget *widget, gpointer data)
{
	if(pathfinding == TRUE)
		stop_pathfinding(stop_button, NULL);
	gtk_widget_set_sensitive(widget, FALSE);
	pathfinding_reset();
}

static void generate_maze(GtkWidget *widget, gpointer data)
{
	if (pathfinding == TRUE)
		stop_pathfinding(stop_button, NULL);
	gtk_widget_set_sensitive(reset_button, FALSE);
	maze_generate(1);
}

static void activate (GtkApplication* app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *b_start, *b_stop, *b_reset, *b_genmaze;
	GtkWidget *button_box;
	GtkWidget *displayarea;
	GtkWidget *grid;
	GtkWidget *frame_pf, *frame_mg;
	GtkWidget *bb_pf, *bb_mg;
	GtkWidget *scale_speed;
	GtkWidget *label_speed;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "A* Pathfinding Demo");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	grid = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);
	gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 20);
	gtk_container_add(GTK_CONTAINER(window), grid);

	displayarea = gtk_drawing_area_new();
	gtk_widget_set_size_request(displayarea, 501, 401);
	g_signal_connect(G_OBJECT(displayarea), "draw", G_CALLBACK(draw_callback), NULL);
	gtk_grid_attach(GTK_GRID(grid), displayarea, 0, 0, 2, 1);

	frame_pf = gtk_frame_new("Pathfinding");
	//gtk_container_set_padding(GTK_CONTAINER(frame_pf), 20);
	gtk_grid_attach(GTK_GRID(grid), frame_pf, 0, 1, 1, 1);

	bb_pf = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
	gtk_container_set_border_width(GTK_CONTAINER(bb_pf), 10);
	gtk_container_add(GTK_CONTAINER(frame_pf), bb_pf);

	b_start = gtk_button_new_with_label("Start Pathfinding");
	start_button = b_start;
	g_signal_connect(b_start, "clicked", G_CALLBACK(start_pathfinding), NULL);
	//g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
	gtk_container_add(GTK_CONTAINER(bb_pf), b_start);

	b_stop = gtk_button_new_with_label("Stop Pathfinding");
	stop_button = b_stop;
	g_signal_connect(b_stop, "clicked", G_CALLBACK(stop_pathfinding), NULL);
	gtk_widget_set_sensitive(b_stop, FALSE);
	gtk_container_add(GTK_CONTAINER(bb_pf), b_stop);

	scale_speed = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 100, 20);
	g_signal_connect(G_OBJECT(scale_speed), "value_changed", G_CALLBACK(speed_changed), NULL);
	gtk_container_add(GTK_CONTAINER(bb_pf), scale_speed);

	label_speed = gtk_label_new("Cycles per second");
	gtk_container_add(GTK_CONTAINER(bb_pf), label_speed);

	b_reset = gtk_button_new_with_label("Reset Pathfinding");
	reset_button = b_reset;
	g_signal_connect(b_reset, "clicked", G_CALLBACK(reset_pathfinding), NULL);
	gtk_widget_set_sensitive(b_reset, FALSE);
	gtk_container_add(GTK_CONTAINER(bb_pf), b_reset);

	frame_mg = gtk_frame_new("Maze Generation");
	gtk_grid_attach(GTK_GRID(grid), frame_mg, 1, 1, 1, 1);

	bb_mg = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
	gtk_container_set_border_width(GTK_CONTAINER(bb_pf), 10);
	gtk_container_add(GTK_CONTAINER(frame_mg), bb_mg);

	b_genmaze = gtk_button_new_with_label("Generate Maze");
	g_signal_connect(b_genmaze, "clicked", G_CALLBACK(generate_maze), NULL);
	gtk_container_add(GTK_CONTAINER(bb_mg), b_genmaze);

	gtk_widget_show_all(window);

}

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	guint width, height;
	GdkRGBA color;
	color.red = 1;
	color.green = .5;
	color.blue = .5;
	color.alpha = 1;

	GtkStyleContext *context;

	context = gtk_widget_get_style_context(widget);
	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);

	draw_update(width, height, context, 20);

	clear_canvas(.5, 0, 0, 1, cr);
	for (int i = 10; i < 20; i++)
	{
		draw_cell(i, 10, color, cr);
	}

	draw_lines(cr);

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

void * pf_loop(void *param)
{
	while (pathfinding == TRUE)
	{
		//Run pathfinding cycle
		pathfinding_cycle();
		sleep(1 / aps);
	}
}
