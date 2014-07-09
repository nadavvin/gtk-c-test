/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2014 Nadav vinik <nadavvin@gmail.com>
 * 
 */

#include <config.h>
#include <gtk/gtk.h>


#include <glib/gi18n.h>



static GdkWindow*
create_window (void)
{
	//GtkWidget *window;
	GdkWindow *window;
	GdkWindowAttr attr;
	//attr.window_type = GTK_WINDOW_TOPLEVEL;
	attr.window_type = GDK_WINDOW_TOPLEVEL;
	attr.wclass = GDK_INPUT_OUTPUT;
	attr.event_mask = GDK_KEY_PRESS_MASK | GDK_STRUCTURE_MASK | GDK_EXPOSURE_MASK;
	attr.width = 400;
    attr.height = 300;
	attr.title = "gtk-foobar";

	//window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	window = gdk_window_new (NULL, &attr, 0);
	//gtk_window_set_title (GTK_WINDOW (window), "gtk-foobar");

	//gtk_window_set_keep_above (GTK_WINDOW (window), TRUE);
	gdk_window_set_keep_above (window, TRUE);
	//gtk_window_fullscreen (GTK_WINDOW (window));

	GError *e = NULL;
	GdkPixbuf *buf;
	//cairo_t *cr = NULL;
	cairo_surface_t *surface;
	cairo_region_t *r;

	//cairo_create (cr);
	buf = gdk_pixbuf_new_from_file ("/home/carmit/nadav/projects/c-gtk-test/src/drawing.svg", &e);
	if(!buf) {
		fprintf(stderr, "%s\n", e->message);
		g_error_free(e);
		return NULL;
	}
	//gdk_cairo_set_source_pixbuf (cr, buf, 0, 0);
	//cairo_paint (cr);
	surface = gdk_cairo_surface_create_from_pixbuf (buf, 1, NULL);
	r = gdk_cairo_region_create_from_surface (surface);
	
	if(!GDK_IS_WINDOW(window)) {
		fprintf(stderr, "window is not a window\n");
		return NULL;
	}
	gdk_window_shape_combine_region (window, r, 0, 0);
	

	/* Exit when the window is closed */
	//g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	
	
	return window;
}

int
main (int argc, char *argv[])
{
 	GdkWindow *window;



#ifdef ENABLE_NLS

	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif
	
	gtk_init (&argc, &argv);

	window = create_window ();
	//gtk_widget_show (window);
	gdk_window_show (window);

	gtk_main ();




	return 0;
}

