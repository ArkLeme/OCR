#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"
#include "document.h"

docs_t docs = {NULL, NULL};

int main(int argc,char **argv)
{
    GtkWidget *p_window = NULL;
    GtkWidget *p_main_box = NULL;
    GtkWidget *p_text_view = NULL;
    GtkWidget *p_button_box = NULL;

    /* Init GTK+ */
    gtk_init(&argc,&argv);

    /* Create main window */
    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(p_window), "UI OCR");
    gtk_window_maximize (GTK_WINDOW(p_window));

    /* Callback quit if window is destroy */
    g_signal_connect(G_OBJECT(p_window), "destroy", G_CALLBACK(cb_quit), NULL);
    
    /* Create main box container */
    p_main_box = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

    /* Create the text area */
    {
	GtkTextBuffer *p_text_buffer = NULL;
	
	p_text_view = gtk_text_view_new ();
	p_text_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (p_text_view));

	g_signal_connect (G_OBJECT (p_text_buffer), "changed", G_CALLBACK (cb_modif), NULL);
	gtk_box_pack_start (GTK_BOX (p_main_box), p_text_view, TRUE, TRUE, 0);

    }

    /* Create button box container */
    p_button_box = gtk_hbutton_box_new ();
    gtk_box_pack_start (GTK_BOX (p_main_box), p_button_box, FALSE, FALSE, 0);
    
    /* Button open config */
    {
	GtkWidget *p_button = NULL;

	p_button = gtk_button_new_from_stock (GTK_STOCK_OPEN);
	g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_open), p_text_view);
	gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
    }

    /* Button save config */
    {
	GtkWidget *p_button = NULL;

	p_button = gtk_button_new_from_stock (GTK_STOCK_SAVE);
	g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_save), NULL);
	gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
    }

    /* Button saveAs config */
    {
	GtkWidget *p_button = NULL;

	p_button = gtk_button_new_from_stock (GTK_STOCK_SAVE_AS);
	g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_saveas), NULL);
	gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
    }

     /* Button quit config */
    {
	GtkWidget *p_button = NULL;

	p_button = gtk_button_new_from_stock (GTK_STOCK_QUIT);
	g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_quit), NULL);
	gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
    }

    /* Display window */
    gtk_widget_show_all(p_window);

    /* Exec gtk main loop */
    gtk_main();

    return EXIT_SUCCESS;
}

