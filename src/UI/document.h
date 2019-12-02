#ifndef DOCUMENT
#define DOCUMENT

#include <gtk/gtk.h>

/**
 * \file document.h
 * \brief Define document and docs structure.
 * \author Alexandre.L
 */

/**
 * \struct Document
 * \brief Document structure.
 * \return new Document structure.
 */

typedef struct
{
	/**
	 * Path of the document.
	 */
	gchar *path;

	/**
	 * Bool of save state.
	 */
	gboolean save;

	/**
	 * Text view widget used by the document.
	 */
	GtkTextView *p_text_view;

} Document;


/**
 * \struc UI
 * \brief UI strucure, contains UI info .
 * \return new UI structure.
 */

typedef struct
{
	/**
	 * Pointer on Document active.
	 */
	Document *active;

	/**
	 * Pointer on Main window widget.
	 */
	GtkWidget *p_main_window;

	/**
	 * Pointer on Start window widget.
	 */
	GtkWidget *s_start_window;
} UI;

/* Global variable */
extern UI docs;

#endif
