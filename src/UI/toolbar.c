#include <gtk/gtk.h>
#include "callback.h"
#include "toolbar.h"
#include "document.h"

/**
 * \file toolbar.c
 * \brief This file contains all the function use to create the toolbar.
 * \author Alexandre.L
 */

static void toolbar_item_new (GtkToolbar *, gchar *, gchar *,GCallback, gpointer);

/**
 * \fn void *toolbar_new (gpointer user_data)
 * \brief Create toolbar widget to add it to the main window.
 * \param user_data : Text view widget.
 * \return GtkToolbar
 */

GtkToolbar *toolbar_new (gpointer user_data)
{
	GtkWidget *p_toolbar = NULL;

	p_toolbar = gtk_toolbar_new ();
	gtk_toolbar_set_style (GTK_TOOLBAR (p_toolbar), GTK_TOOLBAR_ICONS);
	GtkWidget *p_text_view = GTK_WIDGET(docs.active->p_text_view);
	toolbar_item_new(GTK_TOOLBAR(p_toolbar),"./image_data/UI/icon/png/ocr.png",
						"Apply OCR on a picture", G_CALLBACK(cb_ocr),user_data);
	toolbar_item_new(GTK_TOOLBAR (p_toolbar),"./image_data/UI/icon/png/file.png",
						"Create an empty file",G_CALLBACK (cb_new), p_text_view);
	toolbar_item_new(GTK_TOOLBAR (p_toolbar),"./image_data/UI/icon/png/folder.png",
						"Open a file", G_CALLBACK (cb_open), user_data);
	toolbar_item_new(GTK_TOOLBAR (p_toolbar),"./image_data/UI/icon/png/save.png", 
						"Save file", G_CALLBACK (cb_save), user_data);
	toolbar_item_new(GTK_TOOLBAR (p_toolbar),"./image_data/UI/icon/png/save-1.png",
						"Save as file", G_CALLBACK (cb_saveas), user_data);
	toolbar_item_new(GTK_TOOLBAR (p_toolbar),"./image_data/UI/icon/png/close.png", 
						"Close file", G_CALLBACK (cb_close), user_data);
	toolbar_item_new(GTK_TOOLBAR (p_toolbar),"./image_data/UI/icon/png/door.png",
						"Quit application",G_CALLBACK (cb_quit), user_data);
	return GTK_TOOLBAR (p_toolbar);
}

/**
 * \fn static void toolbar_item_new (GtkToolbar *p_toolbar,gchar *stock_id, 
 gchar *text, GCallback callback, gpointer user_data)
 * \brief Create toolbar item and add it to the toolbar widget.
 * \param *p_toolbar : Toolbar widget.
 * \param *stock_id : Icon path.
 * \param *text : Description of the item.
 * \param callback : Callback function to call when pressing the item.
 * \param user_data : Text view widget.
 * \return void
 */

static void toolbar_item_new (GtkToolbar *p_toolbar, gchar *stock_id, 
gchar *text, GCallback callback, gpointer user_data)
{
  GtkToolItem *p_tool_item = NULL;
  GtkWidget *image = gtk_image_new_from_file (stock_id);
  GtkWidget *button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(button),image);

  gtk_widget_set_tooltip_text(GTK_WIDGET(button),text);
  
  p_tool_item = gtk_tool_button_new (button,NULL);
  g_signal_connect (G_OBJECT (p_tool_item), "clicked", callback, user_data);
  gtk_toolbar_insert (p_toolbar, p_tool_item, -1);
}
