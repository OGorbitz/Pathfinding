#include "main.h"


static void speed_changed(GtkWidget *widget, gpointer *data)
{
	long x = gtk_range_get_value(GTK_RANGE(widget));
	//DEBUG: g_print("Speed set to %ld actions per second\n", x);
	aps = x;
}

static void m_speed_changed(GtkWidget *widget, gpointer *data)
{
	long x = gtk_range_get_value(GTK_RANGE(widget));
	//DEBUG: g_print("Maze generation speed set to %ld actions per second\n", x);
	cps = x;
}

static void start_pathfinding(GtkWidget *widget, gpointer data)
{
	pathfinding = TRUE;
	//DEBUG: g_print("Pathfinding started at %ld aps\n", aps);
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
	//DEBUG: g_print("Pathfinding halted\n");
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


	if(!genthread)
	{
		pthread_create(&genthread, NULL, mg_loop, NULL);
	} else {
		pthread_cancel(genthread);
		pthread_create(&genthread, NULL, mg_loop, NULL);
	}
}

static void activate (GtkApplication* app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *b_genmaze;
	GtkWidget *button_box;
	GtkWidget *display_area;
	GtkWidget *grid;
	GtkWidget *frame_pf, *frame_mg;
	GtkWidget *bb_pf, *bb_mg;
	GtkWidget *scale_speed, *m_scale_speed;
	GtkWidget *label_speed, *m_label_speed;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "A* Pathfinding Demo");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	grid = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);
	gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 20);
	gtk_container_add(GTK_CONTAINER(window), grid);

	display_area = gtk_drawing_area_new();
	displayarea = display_area;
	gtk_widget_set_size_request(display_area, 500, 420);
	g_signal_connect(G_OBJECT(display_area), "draw", G_CALLBACK(draw_callback), NULL);
	gtk_grid_attach(GTK_GRID(grid), display_area, 0, 0, 2, 1);

	frame_pf = gtk_frame_new("Pathfinding");
	//gtk_container_set_padding(GTK_CONTAINER(frame_pf), 20);
	gtk_grid_attach(GTK_GRID(grid), frame_pf, 0, 1, 1, 1);

	bb_pf = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
	gtk_container_set_border_width(GTK_CONTAINER(bb_pf), 10);
	gtk_container_add(GTK_CONTAINER(frame_pf), bb_pf);

	start_button = gtk_button_new_with_label("Start Pathfinding");
	g_signal_connect(start_button, "clicked", G_CALLBACK(start_pathfinding), NULL);
	//g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
	gtk_container_add(GTK_CONTAINER(bb_pf), start_button);

	stop_button = gtk_button_new_with_label("Stop Pathfinding");
	g_signal_connect(stop_button, "clicked", G_CALLBACK(stop_pathfinding), NULL);
	gtk_widget_set_sensitive(stop_button, FALSE);
	gtk_container_add(GTK_CONTAINER(bb_pf), stop_button);

	scale_speed = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 1000, 20);
	g_signal_connect(G_OBJECT(scale_speed), "value_changed", G_CALLBACK(speed_changed), NULL);
	gtk_container_add(GTK_CONTAINER(bb_pf), scale_speed);

	label_speed = gtk_label_new("Cycles per second");
	gtk_container_add(GTK_CONTAINER(bb_pf), label_speed);

	reset_button = gtk_button_new_with_label("Reset Pathfinding");
	g_signal_connect(reset_button, "clicked", G_CALLBACK(reset_pathfinding), NULL);
	gtk_widget_set_sensitive(reset_button, FALSE);
	gtk_container_add(GTK_CONTAINER(bb_pf), reset_button);

	frame_mg = gtk_frame_new("Maze Generation");
	gtk_grid_attach(GTK_GRID(grid), frame_mg, 1, 1, 1, 1);

	bb_mg = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
	gtk_container_set_border_width(GTK_CONTAINER(bb_pf), 10);
	gtk_container_add(GTK_CONTAINER(frame_mg), bb_mg);

	b_genmaze = gtk_button_new_with_label("Generate Maze");
	g_signal_connect(b_genmaze, "clicked", G_CALLBACK(generate_maze), NULL);
	gtk_container_add(GTK_CONTAINER(bb_mg), b_genmaze);

	m_scale_speed = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 1000, 20);
	g_signal_connect(G_OBJECT(m_scale_speed), "value_changed", G_CALLBACK(m_speed_changed), NULL);
	gtk_container_add(GTK_CONTAINER(bb_mg), m_scale_speed);

	m_label_speed = gtk_label_new("Cycles per second");
	gtk_container_add(GTK_CONTAINER(bb_mg), m_label_speed);

	gtk_widget_show_all(window);

}

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	GtkStyleContext *context;
	guint da_width, da_height;

	context = gtk_widget_get_style_context(widget);
	da_width = gtk_widget_get_allocated_width(widget);
	da_height = gtk_widget_get_allocated_height(widget);

	cairo = cr;
	draw_update(da_width, da_height, context, 20);

	GdkRGBA color;
	color.red = 1;
	color.green = .5;
	color.blue = .5;
	color.alpha = 1;

	clear_canvas(.5, 0, 0, 1, cr);

	for (int i = 0; i < get_width(); i++)
	{
		for(int j = 0; j < get_width(); j++)
		{

			if(get_box(i, j) == 0)
			{
				color.red = 0.2;
				color.green = 0.2;
				color.blue = 0.2;
				draw_cell(i, j, color, cr);
			}
			if(get_box(i, j) == 1)
			{
				GdkRGBA cl;
				cl.red = 0.8;
				cl.green = 0.4;
				cl.blue = 0.4;
				cl.alpha = 1;
				draw_cell(i, j, cl, cr);
			}
			if(get_box(i, j) == 2)
			{
				GdkRGBA cl;
				cl.red = 0.4;
				cl.green = 0.8;
				cl.blue = 0.4;
				cl.alpha = 1;
				draw_cell(i, j, cl, cr);
			}
		}
	}

	color.red = 1;
	color.blue = .2;
	color.green = .2;
	draw_cell(0, 0, color, cr);
	draw_lines(cr);
	//DEBUG: g_print("Updated drawarea\n");
	return (FALSE);
}

int main(int argc, char **argv)
{
	GtkApplication *app;
	int status;

	new_grid();

	app = gtk_application_new("org.gtk.astar", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return(status);
}

void request_dpu()
{
	gtk_widget_queue_draw(displayarea);
}

void * pf_loop(void *param)
{
	while (pathfinding == TRUE)
	{
		//Run pathfinding cycle
		pathfinding_cycle();
		usleep(1000000 / aps);
	}
}

void * mg_loop(void *param)
{
	maze_generate_init();

	while (1 == 1)
	{
		usleep(1000000 / cps);
		if (maze_generate_tick())
		{
			g_print("New Maze Generated\n");
			break;
		}
		gtk_widget_queue_draw(displayarea);
	}
}
