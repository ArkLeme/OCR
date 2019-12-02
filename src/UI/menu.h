#ifndef H_MENU
#define H_MENU

#include <glib.h>

/**
 * \file menu.h
 * \brief header of menu.c
 * \author Alexandre.L
 */

/*
 * Create menu widget to add it to the main window.
 * gpointer : Text view widget.
 * return GtkMenuBar
 */

GtkMenuBar *menu_new (gpointer);

#endif
