#ifndef CALLBACK
#define CALLBACK
#include <gtk/gtk.h>

void cb_open (GtkWidget *, gpointer);
void cb_quit (GtkWidget *, gpointer);
void cb_modif (GtkWidget*,gpointer);
void cb_save (GtkWidget*,gpointer);
void cb_saveas (GtkWidget*,gpointer);

#endif
