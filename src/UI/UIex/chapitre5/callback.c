#include "callback.h"
#include "error.h"

#define DEFAULT_FILE "main.c"

static void open_file (const gchar *, GtkTextView *);

void cb_open (GtkWidget *p_widget, gpointer user_data)
{
  open_file (DEFAULT_FILE, GTK_TEXT_VIEW (user_data));

  /* Parametre inutilise */
  (void)p_widget;
}

void cb_quit (GtkWidget *p_widget, gpointer user_data)
{
  gtk_main_quit();

  /* Parametres inutilises */
  (void)p_widget;
  (void)user_data;
}

static void open_file (const gchar *file_name, GtkTextView *p_text_view)
{
  g_return_if_fail (file_name && p_text_view);
  {
    gchar *contents = NULL;

    if (g_file_get_contents (file_name, &contents, NULL, NULL))
    {
      /* Copie de contents dans le GtkTextView */
      gchar *utf8 = NULL;
      GtkTextIter iter;
      GtkTextBuffer *p_text_buffer = NULL;

      p_text_buffer = gtk_text_view_get_buffer (p_text_view);
      gtk_text_buffer_get_iter_at_line (p_text_buffer, &iter, 0);
      utf8 = g_locale_to_utf8 (contents, -1, NULL, NULL, NULL);
      g_free (contents), contents = NULL;
      gtk_text_buffer_insert (p_text_buffer, &iter, utf8, -1);
      g_free (utf8), utf8 = NULL;
    }
    else
    {
    	print_warning ("Impossible d'ouvrir le fichier %s\n", file_name);
    }
  }
}
