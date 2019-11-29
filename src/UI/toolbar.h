#ifndef H_TOOLBAR
#define H_TOOLBAR

#include <glib.h>

/**
 * \file toolbar.h
 * \brief header of toolbar.c
 * \author Alexandre.L
 */

/*
 * Create toolbar widget to add it to the main window.
 * gpointer : Text view widget.
 * return GtkToolbar
 */

GtkToolbar *toolbar_new (gpointer);

#endif
