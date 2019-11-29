#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "document.h"
#include "error.h"

/**
 * \file error.c
 * \brief This file contains all the error function called when an error occured.
 * \author Alexandre.L
 */

/**
 * \fn static void print_message (GtkMessageType type, gchar *format, va_list va)
 * \brief Main print function called when an info, a warning or an error must 
 * appear in a dialog box to inform the user.
 *
 * \param type : Type of message (Info, Warning or Error).
 * Set the icon of the dialog box.
 * \param format : Message to display.
 * \param va : List of message.
 *
 * \return void
 */

static void print_message (GtkMessageType type,gchar *format, va_list va)
{
	gchar *message = NULL;
	GtkWidget *p_dialog = NULL;

	message = g_strdup_vprintf (format,va);
	p_dialog = gtk_message_dialog_new (GTK_WINDOW(docs.p_main_window), 
	GTK_DIALOG_MODAL, type, GTK_BUTTONS_NONE,message, format,va);
	gtk_dialog_add_button (GTK_DIALOG(p_dialog),"Close",GTK_RESPONSE_CLOSE);
	g_free (message), message = NULL;
	gtk_dialog_run (GTK_DIALOG (p_dialog));
	gtk_widget_destroy (p_dialog);
	va_end(va);
}

/**
 * \fn void print_info (char *format, ...)
 * \brief Print function called when an info must appear in a dialog box to
 * inform the user.
 *
 * \param format : Message to display.
 *
 * \return void
 */
void print_info (char *format, ...)
{
	va_list va;
	va_start (va, format);
	print_message (GTK_MESSAGE_INFO, format, va);
}

/**
 * \fn void print_warning (char *format, ...)
 * \brief Print function called when a warning must appear in a dialog box 
 * to inform the user.
 *
 * \param format : Message to display.
 *
 * \return void
 */

void print_warning (char *format, ...)
{
	va_list va;
	va_start (va, format);
	print_message (GTK_MESSAGE_WARNING, format, va);
}

/**
 * \fn void print_error (char *format, ...)
 * \brief Print function called when an error must appear in a dialog box 
 * to inform the user and close the application.
 *
 * \param format : Message to display.
 *
 * \return void
 */

void print_error (char *format, ...)
{
	va_list va;
	va_start (va, format);
	print_message (GTK_MESSAGE_ERROR, format, va);
	exit (EXIT_FAILURE);
}
