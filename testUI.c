#include <stdio.h> 
#include <string.h>
#include <time.h> 
#include <stdlib.h>
#include <gtk/gtk.h>
#include "src/UI/callback.h"
#include "src/UI/document.h"
#include "src/UI/menu.h"
#include "src/UI/toolbar.h"


docs_t docs = {NULL, NULL, NULL,NULL};

int main(int argc,char **argv)
{
    GtkWidget *s_window = NULL;
    GtkWidget *s_main_box = NULL;
    GtkWidget *s_button_box = NULL;
    
    GtkWidget *p_window = NULL;
    GtkWidget *p_main_box = NULL;
    GtkWidget *p_text_view = NULL;
    

    g_resource_load ("image_data/UI/icon/png",NULL);
    /* Init GTK+ */
    gtk_init(&argc,&argv);

    /* Create start window */
    s_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(s_window), "OCR");
    gtk_window_resize (GTK_WINDOW(s_window),300,300);
    
    /* Create main window */
    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(p_window), "OCR");
    gtk_window_maximize (GTK_WINDOW(p_window));

    docs.p_main_window = p_window;
    docs.s_start_window = s_window;
    
    /* Callback quit if window is destroy */
    
    g_signal_connect(G_OBJECT(p_window), "destroy", G_CALLBACK(cb_quit), NULL); 
    g_signal_connect(G_OBJECT(s_window), "destroy", G_CALLBACK(cb_quit), NULL);

    /* Create start box container */

    s_main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_container_add(GTK_CONTAINER(s_window),s_main_box);

    /* Create main box container */
    p_main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add (GTK_CONTAINER (p_window), p_main_box);

    
    p_text_view = gtk_text_view_new ();
   
    /* Create the menu */
    gtk_box_pack_start (GTK_BOX (p_main_box), GTK_WIDGET (menu_new (p_text_view)), FALSE, FALSE, 0);

    /* Create toolbar */
    gtk_box_pack_start (GTK_BOX (p_main_box), GTK_WIDGET (toolbar_new (p_text_view)), FALSE, FALSE, 0);

    
    /* Create the text area */
    {
	GtkTextBuffer *p_text_buffer = NULL;
	GtkWidget *p_scrolled_window = NULL;
	
	p_scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (p_scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start (GTK_BOX (p_main_box), p_scrolled_window, TRUE, TRUE, 0);
	p_text_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (p_text_view));
	g_signal_connect (G_OBJECT (p_text_buffer), "changed", G_CALLBACK (cb_modif), NULL);
	gtk_widget_set_sensitive (p_text_view, FALSE);
	gtk_container_add (GTK_CONTAINER (p_scrolled_window), p_text_view);
    }


    GtkWidget *image = NULL;
    srand(time(0));
    float nb = rand()%2;
    char image_path[25];
    sprintf(image_path, "./image_data/UI/%i.png",(int)nb);
    
    image = gtk_image_new_from_file(image_path);
    gtk_box_pack_start(GTK_BOX(s_main_box), image, FALSE,FALSE, 0);
    
    /* Create button box container */
    s_button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    gtk_button_box_set_layout (GTK_BUTTON_BOX(s_button_box),GTK_BUTTONBOX_EXPAND);
    gtk_box_pack_start (GTK_BOX(s_main_box), s_button_box, TRUE, FALSE, 0);
    
    
    /* Button ocr config */
    {
	GtkWidget *s_button = NULL;
	GtkWidget *image = NULL;
	image = gtk_image_new_from_file("./image_data/UI/icon/png/ocr.png");
	s_button = gtk_button_new_with_label("Launch OCR");
	gtk_button_set_always_show_image (GTK_BUTTON(s_button),TRUE);
	gtk_button_set_image(GTK_BUTTON(s_button),image);
	gtk_button_set_image_position (GTK_BUTTON(s_button),GTK_POS_TOP);
	g_signal_connect (G_OBJECT (s_button), "clicked", G_CALLBACK (cb_ocr), p_text_view);
	gtk_box_pack_start (GTK_BOX (s_button_box), s_button, FALSE, FALSE, 10);
    }

    /* Button edit text config */
    {
	GtkWidget *s_button = NULL;
	GtkWidget *image = NULL;

	image = gtk_image_new_from_file("./image_data/UI/icon/png/edit.png");
	s_button = gtk_button_new_with_label("Edit text");
	gtk_button_set_always_show_image (GTK_BUTTON(s_button),TRUE);
	gtk_button_set_image(GTK_BUTTON(s_button),image);
	gtk_button_set_image_position (GTK_BUTTON(s_button),GTK_POS_TOP);

	g_signal_connect (G_OBJECT (s_button), "clicked", G_CALLBACK (cb_edit), s_window);
	gtk_box_pack_start (GTK_BOX (s_button_box), s_button, FALSE, FALSE, 10);
    }

    /* Button quit config */
 
    {
	GtkWidget *s_button = NULL;
	GtkWidget *image = NULL;

	image = gtk_image_new_from_file("./image_data/UI/icon/png/door.png");
	s_button = gtk_button_new_with_label("Quit");
	gtk_button_set_always_show_image (GTK_BUTTON(s_button),TRUE);
	gtk_button_set_image(GTK_BUTTON(s_button),image);
	gtk_button_set_image_position (GTK_BUTTON(s_button),GTK_POS_TOP);

	g_signal_connect (G_OBJECT (s_button), "clicked", G_CALLBACK (cb_quit), NULL);
	gtk_box_pack_start (GTK_BOX (s_button_box), s_button, FALSE, FALSE, 10);
    }

    /* Display window */
    gtk_widget_show_all(s_window);

    /* Exec gtk main loop */
    gtk_main();
    
    return EXIT_SUCCESS;
}
