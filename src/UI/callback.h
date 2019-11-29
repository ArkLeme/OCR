#ifndef CALLBACK
#define CALLBACK

#include <gtk/gtk.h>

/**
 * \file callback.h
 * \brief header of callback.c
 * \author Alexandre.L
 */

/*
 * Callback function for OCR button
 * GtkWidget is the widget from the callback signal
 * gpointer is a widget the function can need.
 * return void
 */
void cb_ocr (GtkWidget *, gpointer);

/*
 * Callback function for Edit text button
 * GtkWidget is the widget from the callback signal
 * gpointer is a widget the function can need.
 * return void
 */
void cb_edit (GtkWidget *, gpointer);

/*
 * Callback function for New file button
 * GtkWidget is the widget from the callback signal
 * gpointer is a widget the function can need.
 * return void
 */
void cb_new (GtkWidget *, gpointer);

/*
 * Callback function for Open file button
 * GtkWidget is the widget from the callback signal
 * gpointer is a widget the function can need.
 * return void
 */
void cb_open (GtkWidget *, gpointer);

/*
 * Callback function for Close button
 * GtkWidget is the widget from the callback signal
 * gpointer is a widget the function can need.
 * return void
 */
void cb_close (GtkWidget *, gpointer);

/*
 * Callback function for Quit button
 * GtkWidget is the widget from the callback signal
 * gpointer is a widget the function can need.
 * return void
 */
void cb_quit (GtkWidget *, gpointer);

/*
 * Callback function used when a file is modify
 * GtkWidget is the widget from the callback signal
 * gpointer is a widget the function can need.
 * return void
 */
void cb_modif (GtkWidget*,gpointer);

/*
 * Callback function for Save button
 * GtkWidget is the widget from the callback signal
 * gpointer is a widget the function can need.
 * return void
 */
void cb_save (GtkWidget*,gpointer);

/*
 * Callback function for Save As button
 * GtkWidget is the widget from the callback signal
 * gpointer is a widget the function can need.
 * return void
 */
void cb_saveas (GtkWidget*,gpointer);

void cb_about (GtkWidget*,gpointer);

#endif
