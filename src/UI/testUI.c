#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"
#include "document.h"
#include "menu.h"
#include "toolbar.h"


docs_t docs = {NULL, NULL, NULL, NULL};

int main(int argc,char **argv)
{
    GtkWidget *s_window = NULL;
    GtkWidget *s_main_box = NULL;
    GtkWidget *s_button_box = NULL;
    GtkWidget *p_window = NULL;
    GtkWidget *p_main_box = NULL;
    GtkWidget *p_text_view = NULL;
    GtkWidget *p_button_box = NULL;
    
    /* Init GTK+ */
    gtk_init(&argc,&argv);

    /* Create start window */
    s_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(s_window), "OCR");
    gtk_window_maximize (GTK_WINDOW(s_window));
    
    /* Create main window */
    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(p_window), "OCR");
    gtk_window_maximize (GTK_WINDOW(p_window));

    /* Callback quit if window is destroy */
    
    g_signal_connect(G_OBJECT(p_window), "destroy", G_CALLBACK(cb_quit), NULL); 
    g_signal_connect(G_OBJECT(s_window), "destroy", G_CALLBACK(cb_quit), NULL);

    /* Create start box container */

    s_main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_container_add(GTK_CONTAINER(s_window),s_main_box);

    /* Create main box container */
    p_main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

    docs.p_main_window = GTK_WINDOW (p_window);
   
    /* Create the menu */
    gtk_box_pack_start (GTK_BOX (p_main_box), GTK_WIDGET (menu_new (p_text_view)), FALSE, FALSE, 0);

    /* Create toolbar */
    gtk_box_pack_start (GTK_BOX (p_main_box), GTK_WIDGET (toolbar_new (p_text_view)), FALSE, FALSE, 0);

    /* Creation de la page d'onglets */
    {
    	GtkWidget *p_notebook = NULL;

    	p_notebook = gtk_notebook_new ();
    	gtk_container_add (GTK_CONTAINER (p_main_box), p_notebook);
    	g_signal_connect (G_OBJECT (p_notebook), "switch-page", G_CALLBACK (cb_page_change), NULL);
    	docs.p_notebook = GTK_NOTEBOOK (p_notebook);
    }

    /* Create the text area */
    {
	GtkTextBuffer *p_text_buffer = NULL;
	GtkWidget *p_scrolled_window = NULL;
	
	p_text_view = gtk_text_view_new ();
	p_scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (p_scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start (GTK_BOX (p_main_box), p_scrolled_window, TRUE, TRUE, 0);
	p_text_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (p_text_view));
	g_signal_connect (G_OBJECT (p_text_buffer), "changed", G_CALLBACK (cb_modif), NULL);
	gtk_widget_set_sensitive (p_text_view, FALSE);
	gtk_container_add (GTK_CONTAINER (p_scrolled_window), p_text_view);
    }


    /* Create button box container */
    p_button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start (GTK_BOX (p_main_box), p_button_box, FALSE, FALSE, 0);
    s_button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start (GTK_BOX (s_main_box), s_button_box, FALSE, FALSE, 0);
    
    /* Start window button config */

    GtkWidget *image = gtk_image_new_from_file("/home/alexandre/Aled/OCR/image_data/png/lena.png");
    gtk_box_pack_start(GTK_BOX(s_button_box), image, FALSE,FALSE, 100);
    /* Button ocr config */
    {
	GtkWidget *s_button = NULL;

	s_button = gtk_button_new_with_label("Launch OCR");
	g_signal_connect (G_OBJECT (s_button), "clicked", G_CALLBACK (cb_ocr), p_text_view);
	gtk_box_pack_start (GTK_BOX (s_button_box), s_button, FALSE, FALSE, 100);
    }

    /* Button edit text config */
    {
	GtkWidget *s_button = NULL;

	s_button = gtk_button_new_with_label("Edit Text");
	g_signal_connect (G_OBJECT (s_button), "clicked", G_CALLBACK (cb_edit), p_window);
	gtk_box_pack_start (GTK_BOX (s_button_box), s_button, FALSE, FALSE, 100);
    }

    /* Button quit config */
 
    {
	GtkWidget *s_button = NULL;

	s_button = gtk_button_new_with_label("Quit");
	g_signal_connect (G_OBJECT (s_button), "clicked", G_CALLBACK (cb_quit), NULL);
	gtk_box_pack_start (GTK_BOX (s_button_box), s_button, FALSE, FALSE, 100);
    }


    /* Text editor button config */

    /* Button new_file config */
    {
	GtkWidget *p_button = NULL;

	p_button = gtk_button_new_from_icon_name ("document-new",GTK_ICON_SIZE_BUTTON);
	g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_new), p_text_view);
	gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
    }
    /* Button open config */
    {
	GtkWidget *p_button = NULL;

	p_button = gtk_button_new_from_icon_name ("document-open",GTK_ICON_SIZE_BUTTON);
	g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_open), p_text_view);
	gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
    }

    /* Button save config */
    {
	GtkWidget *p_button = NULL;

	p_button = gtk_button_new_from_icon_name ("document-save",GTK_ICON_SIZE_BUTTON);
	g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_save), NULL);
	gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
    }

    /* Button saveAs config */
    {
	GtkWidget *p_button = NULL;

	p_button = gtk_button_new_from_icon_name ("document-save-as",GTK_ICON_SIZE_BUTTON);
	g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_saveas), NULL);
	gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
    }

    /* Button close config */
    {
	GtkWidget *p_button = NULL;

	p_button = gtk_button_new_from_icon_name ("window-close",GTK_ICON_SIZE_BUTTON);
	g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_close), NULL);
	gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
    }


    /* Button quit config */
    {
	GtkWidget *p_button = NULL;

	p_button = gtk_button_new_from_icon_name ("application-exit",GTK_ICON_SIZE_BUTTON);
	g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (cb_quit), NULL);
	gtk_box_pack_start (GTK_BOX (p_button_box), p_button, FALSE, FALSE, 0);
    }

    /* Display window */
    gtk_widget_show_all(p_window);

    /* Exec gtk main loop */
    gtk_main();

    return EXIT_SUCCESS;
}


