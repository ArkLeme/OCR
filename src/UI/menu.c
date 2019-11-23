#include <gtk/gtk.h>
#include "callback.h"
#include "menu.h"

static void menu_item_new (GtkMenu *, const gchar *, GCallback, gpointer);

GtkMenuBar *menu_new (gpointer user_data)
{
  GtkWidget *p_menu_bar = NULL;

  p_menu_bar = gtk_menu_bar_new ();

  /* Menu "Fichier" */
  {
    GtkWidget *p_menu = NULL;
    GtkWidget *p_menu_item = NULL;

    p_menu = gtk_menu_new ();
    p_menu_item = gtk_menu_item_new_with_mnemonic ("_Fichier");
    menu_item_new (GTK_MENU (p_menu), "_Nouveau", G_CALLBACK (cb_new), user_data);
    menu_item_new (GTK_MENU (p_menu), "_Ouvrir", G_CALLBACK (cb_open), user_data);
    menu_item_new (GTK_MENU (p_menu), "_Enregistrer", G_CALLBACK (cb_save), user_data);
    menu_item_new (GTK_MENU (p_menu), "Enregistrer _sous", G_CALLBACK (cb_saveas), user_data);
    menu_item_new (GTK_MENU (p_menu), "_Fermer", G_CALLBACK (cb_close), user_data);
    menu_item_new (GTK_MENU (p_menu), "_Quitter", G_CALLBACK (cb_quit), user_data);
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (p_menu_item), p_menu);
    gtk_menu_shell_append (GTK_MENU_SHELL (p_menu_bar), p_menu_item);
  }
  return GTK_MENU_BAR (p_menu_bar);
}

static void menu_item_new (GtkMenu *p_menu, const gchar *title, GCallback callback, gpointer user_data)
{
  GtkWidget *p_menu_item = NULL;

  p_menu_item = gtk_menu_item_new_with_mnemonic (title);
  gtk_menu_shell_append (GTK_MENU_SHELL (p_menu), p_menu_item);
  g_signal_connect (G_OBJECT (p_menu_item), "activate", callback, user_data);
}
