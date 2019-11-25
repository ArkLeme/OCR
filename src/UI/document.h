#ifndef DOCUMENT
#define DOCUMENT

#include <gtk/gtk.h>

// Struct of document
typedef struct
{
  gchar *chemin;
  gboolean sauve;
  GtkTextView *p_text_view;
} document_t;

// Chain list of document_t
typedef struct
{
  GList *tous;
  document_t *actif;
  GtkWindow *p_main_window;
  GtkWindow *s_start_window;
} docs_t;

/* Global variable */
extern docs_t docs;

#endif
