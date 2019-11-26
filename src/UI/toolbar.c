#include <gtk/gtk.h>
#include "callback.h"
#include "toolbar.h"

static void toolbar_item_new (GtkToolbar *, const gchar *, GCallback, gpointer);

GtkToolbar *toolbar_new (gpointer user_data)
{
  GtkWidget *p_toolbar = NULL;

  p_toolbar = gtk_toolbar_new ();
  gtk_toolbar_set_style (GTK_TOOLBAR (p_toolbar), GTK_TOOLBAR_ICONS);
  toolbar_item_new (GTK_TOOLBAR (p_toolbar),
	  "./image_data/UI/icon/png/file.png", G_CALLBACK (cb_new), user_data);
  /*toolbar_item_new (GTK_TOOLBAR (p_toolbar), "document-open", G_CALLBACK (cb_open), user_data);
  toolbar_item_new (GTK_TOOLBAR (p_toolbar), "document-save", G_CALLBACK (cb_save), user_data);
  toolbar_item_new (GTK_TOOLBAR (p_toolbar), "document-save-as", G_CALLBACK (cb_saveas), user_data);
  toolbar_item_new (GTK_TOOLBAR (p_toolbar), "window-close", G_CALLBACK (cb_close), user_data);
  toolbar_item_new (GTK_TOOLBAR (p_toolbar), "application-exit", G_CALLBACK (cb_quit), user_data);*/
  return GTK_TOOLBAR (p_toolbar);
}

static void toolbar_item_new (GtkToolbar *p_toolbar, const gchar *stock_id, GCallback callback, gpointer user_data)
{
  GtkToolItem *p_tool_item = NULL;
  GtkWidget *image = gtk_image_new_from_file (stock_id);
  GtkWidget *button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(button),image);
  gtk_widget_set_size_request(button,20,20);
  
  p_tool_item = gtk_tool_button_new (button,NULL);
  g_signal_connect (G_OBJECT (p_tool_item), "clicked", callback, user_data);
  gtk_toolbar_insert (p_toolbar, p_tool_item, -1);
}
