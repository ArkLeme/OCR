#include <gtk/gtk.h>
#include "callback.h"
#include "menu.h"

/**
 * \file menu.c
 * \brief This file contains all the function we need to create a menu.
 * \author Alexandre.L
 */

static void menu_item_new (GtkMenu *, gchar *, GCallback, gpointer);

/**
 * \fn void *menu_new (gpointer user_data)
 * \brief Create menu widget to add it to the main window.
 * \param user_data : Text view widget.
 * \return GtkMenuBar
 */

GtkMenuBar *menu_new (gpointer user_data)
{
	GtkWidget *p_menu_bar = NULL;

	p_menu_bar = gtk_menu_bar_new ();

	{
		GtkWidget *p_menu = NULL;
		GtkWidget *p_help = NULL;
		GtkWidget *p_menu_item_1 = NULL;
		GtkWidget *p_menu_item_2 = NULL;
		
		p_menu = gtk_menu_new ();
		p_menu_item_1 = gtk_menu_item_new_with_mnemonic ("_Menu");
		menu_item_new (GTK_MENU (p_menu), "_OCR", G_CALLBACK (cb_ocr), user_data);
		menu_item_new (GTK_MENU (p_menu), "_New", G_CALLBACK (cb_new), user_data);
		menu_item_new (GTK_MENU (p_menu), "_Open", G_CALLBACK (cb_open), user_data);
		menu_item_new (GTK_MENU (p_menu), "_Save", G_CALLBACK (cb_save), user_data);
		menu_item_new (GTK_MENU (p_menu), "Save _as", G_CALLBACK (cb_saveas), user_data);
		menu_item_new (GTK_MENU (p_menu), "_Close", G_CALLBACK (cb_close), user_data);
		menu_item_new (GTK_MENU (p_menu), "_Quit", G_CALLBACK (cb_quit), user_data);
		gtk_menu_item_set_submenu (GTK_MENU_ITEM (p_menu_item_1), p_menu);
		gtk_menu_shell_append (GTK_MENU_SHELL (p_menu_bar), p_menu_item_1);
	
		p_help = gtk_menu_new ();
		p_menu_item_2 = gtk_menu_item_new_with_mnemonic("_Help");
		menu_item_new (GTK_MENU(p_help), "_Readme",G_CALLBACK(cb_about),user_data);
		menu_item_new (GTK_MENU(p_help), "_Doc", G_CALLBACK(cb_doc),user_data);
		menu_item_new (GTK_MENU(p_help), "_About us", G_CALLBACK(cb_about),user_data);
		gtk_menu_item_set_submenu(GTK_MENU_ITEM(p_menu_item_2),p_help);
		gtk_menu_shell_append(GTK_MENU_SHELL (p_menu_bar), p_menu_item_2);
	}
	return GTK_MENU_BAR (p_menu_bar);
}

/**
 * \fn static void menu_item_new (GtkMenu *p_menu, gchar *title, GCallback callback, gpointer user_data)
 * \brief Create menu item and add it to the menu widget.
 * \param *p_menu : Menu widget.
 * \param *title : Title of the item.
 * \param callback : Callback function to call when pressing the item.
 * \param user_data : Text view widget.
 * \return void
 */

static void menu_item_new (GtkMenu *p_menu, gchar *title, GCallback callback, gpointer user_data)
{
	GtkWidget *p_menu_item = NULL;

	p_menu_item = gtk_menu_item_new_with_mnemonic (title);
	gtk_menu_shell_append (GTK_MENU_SHELL (p_menu), p_menu_item);
	g_signal_connect (G_OBJECT (p_menu_item), "activate", callback, user_data);
}
