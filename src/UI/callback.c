#include "callback.h"
#include "error.h"
#include "document.h"

static void open_file (const gchar *);
static void set_title (void);
static gboolean close_all (void);

void cb_ocr(GtkWidget *s_widget, gpointer user_data)
{
    g_print("OCR");

    (void) s_widget;
    (void) user_data;
}

void cb_edit(GtkWidget *s_widget,gpointer user_data)
{
    gtk_widget_show_all(GTK_WIDGET(user_data));


    (void) s_widget;
    (void) user_data;
}


void cb_new (GtkWidget *p_widget, gpointer user_data)
{
  document_t *new = NULL;

  new = g_malloc (sizeof (*new));
  new->chemin = NULL;
  /* Le document vient d'etre ouvert, il n'est donc pas modifie */
  new->sauve = TRUE;
  docs.tous = g_list_append (docs.tous, new);
  {
    gint index = 0;
    GtkWidget *p_scrolled_window = NULL;

    p_scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (p_scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    new->p_text_view = GTK_TEXT_VIEW (gtk_text_view_new ());
    {
      GtkTextBuffer *p_buffer = NULL;

      p_buffer = gtk_text_view_get_buffer (new->p_text_view);
      g_signal_connect (G_OBJECT (p_buffer), "changed", G_CALLBACK (cb_modif), NULL);
    }
    gtk_container_add (GTK_CONTAINER (p_scrolled_window), GTK_WIDGET (new->p_text_view));
    index = gtk_notebook_append_page (docs.p_notebook, p_scrolled_window, GTK_WIDGET (gtk_label_new
		("New file")));
    gtk_widget_show_all (p_scrolled_window);
    gtk_notebook_set_current_page (docs.p_notebook, index);
    set_title();
  }

  /* parametres inutilises */
  (void)p_widget;
  (void)user_data;
}

void cb_page_change (GtkNotebook *notebook, guint page_num, gpointer user_data)
{
  docs.actif = g_list_nth_data (docs.tous, page_num);

  /* parametres inutilises */
  (void)notebook;
  (void)user_data;
}
/*void cb_new (GtkWidget *p_widget, gpointer user_data)
{
    if (docs.actif)
    {
	cb_close(p_widget,user_data);
    }
    docs.actif = g_malloc (sizeof (*docs.actif));
    docs.actif->chemin = NULL;
  
    docs.actif->p_text_view = GTK_TEXT_VIEW (user_data);
  
    docs.actif->sauve = TRUE;
    gtk_widget_set_sensitive (GTK_WIDGET (docs.actif->p_text_view), TRUE);
  
     Unused parameter 
    (void)p_widget;
}*/


void cb_open (GtkWidget *p_widget, gpointer user_data)
{
    GtkWidget *p_dialog = NULL;
    
    p_dialog = gtk_file_chooser_dialog_new ("Open a file", NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          ("Cancel"), GTK_RESPONSE_CANCEL,
                                          ("Open"), GTK_RESPONSE_ACCEPT,
                                          NULL);
    
    if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
    {
	gchar *file_name = NULL;
	
	file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
	open_file (file_name);
	
	g_free (file_name), file_name = NULL;
    }

    gtk_widget_destroy (p_dialog);

    /* Unused parameter */
    (void)p_widget;
    (void)user_data;
}

void cb_close (GtkWidget *p_widget, gpointer user_data)
{
    if (docs.actif)
    {
	if (!docs.actif->sauve)
	{
	    GtkWidget *p_dialog = NULL;
	    GtkWidget *p_label = NULL;
	    
	    p_dialog = gtk_dialog_new_with_buttons ("Save changes ?",
						docs.p_main_window,
						GTK_DIALOG_MODAL,
						"Yes",GTK_RESPONSE_YES,
						"No",GTK_RESPONSE_NO,
						"Cancel",GTK_RESPONSE_CANCEL, NULL);
	    p_label = gtk_label_new ("Save changes ?");
	    gtk_box_pack_start (GTK_BOX (p_dialog), p_label, TRUE, FALSE, 10);
	    gtk_widget_show_all (p_dialog);
	    switch (gtk_dialog_run (GTK_DIALOG (p_dialog)))
	    {
		case GTK_RESPONSE_YES:
		     cb_save (p_widget, user_data);
		     break;
		case GTK_RESPONSE_NO:
		     break;
		case GTK_RESPONSE_CANCEL:
		     gtk_widget_destroy (p_dialog);
		     return;
		break;
	    }
	    gtk_widget_destroy (p_dialog);
	}
	{
      	docs.tous = g_list_remove (docs.tous, docs.actif);
      	g_free (docs.actif->chemin), docs.actif->chemin = NULL;
      	g_free (docs.actif), docs.actif = NULL;
      	gtk_notebook_remove_page (docs.p_notebook, gtk_notebook_get_current_page (docs.p_notebook));
      if (gtk_notebook_get_n_pages (docs.p_notebook) > 0)
      {
        docs.actif = g_list_nth_data (docs.tous, gtk_notebook_get_current_page (docs.p_notebook));
      }
      else
      {
        docs.actif = NULL;
      }
    }
  }
  else
  {
     print_warning ("No file open");
  }
 
}

void cb_quit (GtkWidget *p_widget, gpointer user_data)
{
  if (close_all ())
  {
    
    gtk_main_quit();
  }

  /* parametres inutilises */
  (void)p_widget;
  (void)user_data;
}

/*void cb_quit (GtkWidget *p_widget, gpointer user_data)
{
    if (docs.actif)
    {
	cb_close (p_widget, user_data);
    }

    if (!docs.actif)
    {
	gtk_main_quit();
    }
     Unused parameter 
    (void)p_widget;
    (void)user_data;
}*/

void cb_modif (GtkWidget *p_widget, gpointer user_data)
{
    if (docs.actif)
    {
	docs.actif->sauve = FALSE;
	set_title();
    }

    /* Unused parameter */
    (void) p_widget;
    (void) user_data;
}

void cb_save (GtkWidget *p_widget, gpointer user_data)
{
    if (docs.actif)
    {
	if (!docs.actif->sauve)
	{
	    /* File is not save */
	    if (!docs.actif->chemin)
	    {
		GtkWidget *p_dialog = NULL;
		p_dialog = gtk_file_chooser_dialog_new ("Save file ", NULL,
                                                GTK_FILE_CHOOSER_ACTION_SAVE,
                                                "Cancel", GTK_RESPONSE_CANCEL,
                                                "Save", GTK_RESPONSE_ACCEPT,
                                                NULL);
		if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
		{
		    docs.actif->chemin = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
		}
		gtk_widget_destroy (p_dialog);
	    }
	    /* File is already save or user give a new adress */
	    if (docs.actif->chemin)
	    {
		FILE *fichier = NULL;

		fichier = fopen (docs.actif->chemin, "w");

		if (fichier)
		{
		    gchar *contents = NULL;
		    gchar *locale = NULL;
		    GtkTextIter start;
		    GtkTextIter end;
		    GtkTextBuffer *p_text_buffer = NULL;

		    p_text_buffer = gtk_text_view_get_buffer (docs.actif->p_text_view);
		    gtk_text_buffer_get_bounds (p_text_buffer, &start, &end);
		    contents = gtk_text_buffer_get_text (p_text_buffer, &start, &end, FALSE);
		    locale = g_locale_from_utf8 (contents, -1, NULL, NULL, NULL);

		    g_free (contents), contents = NULL;
		
		    fprintf (fichier, "%s", locale);

		    g_free (locale), locale = NULL;
		    fclose (fichier), fichier = NULL;

		    docs.actif->sauve = TRUE;
		    set_title ();
		}
		else
		{
		    print_warning ("Impossible to save file %s", docs.actif->chemin);
		}
	    }
	}
    }
    else
    {
	print_warning ("No file open");
    }

    /* Unused parameter */
    (void)p_widget;
    (void)user_data;
}

void cb_saveas (GtkWidget *p_widget, gpointer user_data)
{
    if (docs.actif)
    {
	document_t tmp = *docs.actif;

	docs.actif->chemin = NULL;
	docs.actif->sauve = FALSE;
	cb_save (p_widget, user_data);
	if (!docs.actif->sauve)
	{
	    (*docs.actif) = tmp;
	}
    }
    else
    {
	print_warning ("No file open");
    }
}

static void open_file (const gchar *file_name)
{
    g_return_if_fail (file_name);
    {
	gchar *contents = NULL;

	if (g_file_get_contents (file_name, &contents, NULL, NULL))
	{
	    /* Copie of contents in GtkTextView */
	    gchar *utf8 = NULL;
	    GtkTextIter iter;
	    GtkTextBuffer *p_text_buffer = NULL;

	    cb_new(NULL, NULL);
	    docs.actif->chemin = g_strdup (file_name);
	    //gtk_widget_set_sensitive (GTK_WIDGET (docs.actif -> p_text_view), TRUE);

	    /* Get buffer of GtkTextView to change text */
	    p_text_buffer = gtk_text_view_get_buffer (docs.actif->p_text_view);
	    gtk_text_buffer_get_iter_at_line (p_text_buffer, &iter, 0);
	    utf8 = g_locale_to_utf8(contents,-1,NULL,NULL,NULL);
	    g_free (contents), contents = NULL;
	    gtk_text_buffer_insert (p_text_buffer, &iter, utf8, -1);
	    g_free (utf8), utf8 = NULL;
	    
	    docs.actif ->sauve = TRUE;
	    set_title();
	}
	else
	{
	   print_warning ("Failed to open %s\n", file_name);
	}
    }
}
static void set_title (void)
{
  if (docs.actif)
  {
    gchar *title = NULL;
    gchar *tmp = NULL;

    if (docs.actif->chemin)
    {
      tmp = g_path_get_basename (docs.actif->chemin);
    }
    else
    {
      tmp = g_strdup ("New file");
    }
    if (docs.actif->sauve)
    {
      title = g_strdup (tmp);
    }
    else
    {
      title = g_strdup_printf ("%s *", tmp);
    }
    g_free (tmp), tmp = NULL;
    {
      gint index = 0;
      GtkWidget *p_child = NULL;
      GtkLabel *p_label = NULL;

      index = gtk_notebook_get_current_page (docs.p_notebook);
      p_child = gtk_notebook_get_nth_page (docs.p_notebook, index);
      p_label = GTK_LABEL (gtk_notebook_get_tab_label (docs.p_notebook, p_child));
      gtk_label_set_text (p_label, title);
    }
    g_free (title), title = NULL;
  }
}

static gboolean close_all (void)
{
  gboolean ret = TRUE;

  while (docs.actif)
  {
    gint tmp = gtk_notebook_get_n_pages (docs.p_notebook);

    gtk_notebook_set_current_page (docs.p_notebook, 0);
    cb_close (NULL, NULL);
    if (gtk_notebook_get_n_pages (docs.p_notebook) >= tmp)
    {
      ret = FALSE;
      break;
    }
  }
  return ret;
}
