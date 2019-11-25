#include "callback.h"
#include "error.h"
#include "document.h"

static void open_file (const gchar *, GtkTextView *);
static void open_ocr(gchar *, GtkTextView *);
static gchar* ocr(gchar *);

void cb_ocr(GtkWidget *s_widget, gpointer user_data)
{
    GtkWidget *p_dialog = NULL;

    p_dialog = gtk_file_chooser_dialog_new ("Choose picture", NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          ("Cancel"), GTK_RESPONSE_CANCEL,
                                          ("Launch OCR"), GTK_RESPONSE_ACCEPT,
                                          NULL);

    if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
    {
	gchar *file_name = NULL;
	
	file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
	open_ocr (file_name,user_data);
	
	g_free (file_name), file_name = NULL;
    }
    gtk_widget_destroy (p_dialog);
    
    gtk_widget_hide(GTK_WIDGET(docs.s_start_window));
    gtk_widget_show_all(GTK_WIDGET(docs.p_main_window));

    (void) s_widget;
    (void) user_data;
}

void cb_edit(GtkWidget *s_widget,gpointer user_data)
{

    gtk_widget_hide(GTK_WIDGET(user_data));
    gtk_widget_show_all(GTK_WIDGET(docs.p_main_window));

    (void) s_widget;
}



void cb_new (GtkWidget *p_widget, gpointer user_data)
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

    /* Unused parameter */
    (void)p_widget;
}


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
	open_file (file_name, GTK_TEXT_VIEW (user_data));
	
	g_free (file_name), file_name = NULL;
    }
    gtk_widget_destroy (p_dialog);
    /* Unused parameter */
    (void)p_widget;
}

void cb_close (GtkWidget *p_widget, gpointer user_data)
{
    if (docs.actif)
    {
	if (!docs.actif->sauve)
	{
	    GtkWidget *p_dialog = NULL;
	    GtkWidget *p_label = NULL;

	    p_dialog = gtk_dialog_new_with_buttons ("Save",
						docs.p_main_window,
						GTK_DIALOG_MODAL,
						"Yes",GTK_RESPONSE_YES,
						"No",GTK_RESPONSE_NO,
						"Cancel",GTK_RESPONSE_CANCEL, NULL);
	    p_label = gtk_label_new ("Save changes ?");
	    gtk_box_pack_start (GTK_BOX (p_dialog), p_label, TRUE, TRUE, 0);
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
	GtkTextIter start;
	GtkTextIter end;
	GtkTextBuffer *p_text_buffer = NULL;

	p_text_buffer = gtk_text_view_get_buffer (docs.actif->p_text_view);
	gtk_text_buffer_get_bounds (p_text_buffer, &start, &end);
	gtk_text_buffer_delete (p_text_buffer, &start, &end);
	gtk_widget_set_sensitive (GTK_WIDGET (docs.actif->p_text_view), FALSE);

	g_free (docs.actif->chemin), docs.actif->chemin = NULL;
	docs.actif->p_text_view = NULL;
	g_free (docs.actif), docs.actif = NULL;

    }
    else
    {
	print_warning ("No file open");
    }
}

void cb_quit (GtkWidget *p_widget, gpointer user_data)
{
    gtk_main_quit();
    if (docs.actif)
    {
	cb_close (p_widget, user_data);
    }

    if (!docs.actif)
    {
	gtk_main_quit();
    }
    /* Unused parameter */
    (void)p_widget;
    (void)user_data;
}
void cb_modif (GtkWidget *p_widget, gpointer user_data)
{
    if (docs.actif)
    {
	docs.actif->sauve = FALSE;
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

		p_dialog = gtk_file_chooser_dialog_new ("Save file", NULL,
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

static void open_file (const gchar *file_name, GtkTextView *p_text_view)
{
    g_return_if_fail (file_name && p_text_view);
    {
	gchar *contents = NULL;

	if (g_file_get_contents (file_name, &contents, NULL, NULL))
	{
	    docs.actif = g_malloc (sizeof (*docs.actif));
	    docs.actif->chemin = g_strdup (file_name);

	    docs.actif->p_text_view = p_text_view;
	    docs.actif->sauve = TRUE;

	    /* Copie of contents in GtkTextView */
	    gchar *utf8 = NULL;
	    GtkTextIter iter;
	    GtkTextBuffer *p_text_buffer = NULL;

	    cb_new(NULL, p_text_view);
	    gtk_widget_set_sensitive (GTK_WIDGET (docs.actif -> p_text_view), TRUE);

	    /* Get buffer of GtkTextView to change text */
	    p_text_buffer = gtk_text_view_get_buffer (p_text_view);
	    gtk_text_buffer_get_iter_at_line (p_text_buffer, &iter, 0);

	    /* To avoid error with char encoding */
	    utf8 = g_locale_to_utf8 (contents, -1, NULL, NULL, NULL);
	    g_free (contents) ,contents = NULL;
	    gtk_text_buffer_insert (p_text_buffer, &iter, utf8, -1);
	    g_free (utf8);
	    utf8 = NULL;
	    gtk_text_buffer_insert (p_text_buffer, &iter, contents, -1);
	    docs.actif ->sauve = TRUE;
	}
	else
	{
	   print_warning ("Failed to open %s\n", file_name);
	}
    }
}

static void open_ocr(gchar *file_name, GtkTextView *p_text_view)
{
    g_return_if_fail (file_name && p_text_view);
    {
	gchar *contents = ocr(file_name);
	docs.actif = g_malloc (sizeof (*docs.actif));
	docs.actif->chemin = g_strdup ("temp.txt");

	docs.actif->p_text_view = p_text_view;
	docs.actif->sauve = TRUE;

	/* Copie of contents in GtkTextView */
	gchar *utf8 = NULL;
	GtkTextIter iter;
	GtkTextBuffer *p_text_buffer = NULL;

	cb_new(NULL, p_text_view);
	gtk_widget_set_sensitive (GTK_WIDGET (docs.actif -> p_text_view), TRUE);

	/* Get buffer of GtkTextView to change text */
	p_text_buffer = gtk_text_view_get_buffer (p_text_view);
	gtk_text_buffer_get_iter_at_line (p_text_buffer, &iter, 0);

	/* To avoid error with char encoding */
	utf8 = g_locale_to_utf8 (contents, -1, NULL, NULL, NULL);
	//g_free (contents) , contents = NULL;
	gtk_text_buffer_insert (p_text_buffer, &iter, utf8, -1);
	g_free (utf8);
	utf8 = NULL;
	gtk_text_buffer_insert (p_text_buffer, &iter, contents, -1);
	
	docs.actif ->sauve = FALSE;
    }
} 

static gchar* ocr(gchar *file_name)
{
    gchar *texte = file_name;
    return texte;
}
