#include "callback.h"
#include "error.h"
#include "document.h"
#include "../process_segmentation/get_list_segmented.h"
#include "../NeuNet/structNet.h"

/**
 * \file callback.c
 * \brief This file contains all the callback function use by UI's buttons
 * \author Alexandre.L
 */


static void open_file (gchar *, GtkTextView *);

static void open_ocr(gchar *,neuNet *network);

/**
 * \fn void cb_ocr(GtkWidget *s_widget, gpointer user_data)
 * \brief Callback function called when pressing OCR button, open a window to
 * select a picture, then a dialog box showing the picture to confirm the 
 * picture choice, and finally call the OCR main function to put Picture's text
 * in the text view box. Hide start window and show the Edit Text's window.
 * 
 * \param s_widget : Widget from the callback signal.
 * \param user_data : Text view widget.
 *
 * \return void
 */

void cb_ocr(GtkWidget* s_widget,gpointer user_data)
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
		file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (p_dialog));
		{
			GtkWidget *test_dialog = NULL;
			GtkWidget *image = NULL;

			test_dialog = gtk_dialog_new_with_buttons ("Use this picture ?",
							GTK_WINDOW(p_dialog),
							GTK_DIALOG_MODAL,
							"Yes",GTK_RESPONSE_YES,
							"No",GTK_RESPONSE_NO,
							NULL);
			GtkWidget *label = gtk_label_new (NULL);
			gtk_label_set_markup (GTK_LABEL (label), "<b> Use this picture ?</b>");
			gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(
							GTK_DIALOG(test_dialog))),
							label, TRUE, TRUE, 5);
			image = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_size(
											file_name,800,600,NULL));
			gtk_box_pack_start (GTK_BOX(gtk_dialog_get_content_area(
						GTK_DIALOG(test_dialog))),image, TRUE, TRUE, 0);

			
			gtk_widget_show_all (test_dialog);
			switch (gtk_dialog_run (GTK_DIALOG (test_dialog)))
			{
				case GTK_RESPONSE_YES:
					break;
				case GTK_RESPONSE_NO:
					gtk_widget_destroy (test_dialog);
					gtk_widget_destroy (p_dialog);
					cb_ocr(s_widget,user_data);
					return;
				break;
			}
			gtk_widget_destroy (test_dialog);
		}

		gtk_widget_destroy (p_dialog);

		gtk_widget_show_all(docs.p_main_window);
		gtk_widget_hide(docs.s_start_window);

		open_ocr (file_name,user_data);

		g_free (file_name);
		file_name = NULL;
	}
	else
	{
		gtk_widget_destroy(p_dialog);
		return;
	}

}


/**
 * \fn void cb_edit(GtkWidget *s_widget, gpointer user_data)
 * \brief Callback function called when pressing Edit Text button, show edit
 * text window and hide start window.
 * \param *s_widget : Widget from the callback signal. (Unused parameter)
 * \param user_data : Start window.
 * \return void
 */

void cb_edit(GtkWidget *s_widget,gpointer user_data)
{
	gtk_widget_hide(GTK_WIDGET(user_data));
	gtk_widget_show_all(GTK_WIDGET(docs.p_main_window));

	/* Unused parameter */
    (void) s_widget;
}


/**
 * \fn void cb_new(GtkWidget *p_widget, gpointer user_data)
 * \brief Callback function called when pressing New file button, set sensitive
 * text view widget and clear its contents if a document is open.
 * \param *p_widget : Widget from the callback signal. (Unused parameter)
 * \param *user_data : Text view widget.
 * \return void
 */

void cb_new (GtkWidget *p_widget, gpointer user_data)
{
	if (docs.active)
	{
		cb_close(p_widget,user_data);
	}
	if(docs.active == NULL)
		docs.active = g_malloc (sizeof (*docs.active));
	docs.active->path = NULL;

	docs.active->p_text_view = GTK_TEXT_VIEW(user_data);
	docs.active->save = TRUE;
	gtk_widget_set_sensitive (GTK_WIDGET (docs.active->p_text_view), TRUE);

	/* Unused parameter */
	(void)p_widget;
}

/**
 * \fn void cb_open(GtkWidget *p_widget, gpointer user_data)
 * \brief Callback function called when pressing Open file button, open a window
 * to select a text file, and load its content in the Text view widget to edit
 * it.
 * \param *p_widget : Widget from the callback signal. (Unused parameter)
 * \param user_data : Text view widget.
 * \return void 
 */


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
		
		if(!docs.active->save)
			cb_close(p_widget,user_data);
		file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
		open_file (file_name, docs.active->p_text_view);
	
		g_free (file_name);
		file_name = NULL;
	}
	
	gtk_widget_destroy (p_dialog);
	
	/* Unused parameter */
	(void)p_widget;
}

/**
 * \fn void cb_close(GtkWidget *p_widget, gpointer user_data)
 * \brief Callback function called when pressing Close file button, clear
 * text view widget content and ask if the user want to save changes before.
 * \param *p_widget : Widget from the callback signal.
 * \param user_data : Text view widget.
 * \return void
 */

void cb_close (GtkWidget *p_widget, gpointer user_data)
{
	if (docs.active)
	{
		if (!docs.active->save)
		{
			GtkWidget *p_dialog = NULL;
			GtkWidget *p_label = NULL;

			p_dialog = gtk_dialog_new_with_buttons ("Save changes",
							GTK_WINDOW(docs.p_main_window),
							GTK_DIALOG_MODAL,
							"Yes",GTK_RESPONSE_YES,
							"No",GTK_RESPONSE_NO,
							"Cancel",GTK_RESPONSE_CANCEL, NULL);
			p_label = gtk_label_new ("Save changes ?");
			gtk_box_pack_start (GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(p_dialog))),
			p_label, TRUE, TRUE , 5);
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

		p_text_buffer = gtk_text_view_get_buffer (docs.active->p_text_view);
		gtk_text_buffer_get_bounds (p_text_buffer, &start, &end);
		gtk_text_buffer_delete (p_text_buffer, &start, &end);
		gtk_widget_set_sensitive (GTK_WIDGET (docs.active->p_text_view), FALSE);

		docs.active->save = TRUE;
	}
	else
	{
		print_warning ("No file open");
	}
}

/**
 * \fn void cb_quit(GtkWidget *p_widget, gpointer user_data)
 * \brief Callback function called when pressing Quit button, call cb_close if
 * a document is open, else close the application.
 * \param *p_widget : Widget from the callback signal. (Unused parameter)
 * \param user_data : Text view widget.
 * \return void
 */

void cb_quit (GtkWidget *p_widget, gpointer user_data)
{
	if (docs.active)
	{
		cb_close (p_widget, user_data);
		docs.active->p_text_view = NULL;
		g_free (docs.active);
		docs.active = NULL;
	}

	if (!docs.active)
	{
		gtk_main_quit();
	}
    
	/* Unused parameter */
	(void)p_widget;
	(void)user_data;
}

/**
 * \fn void cb_modif (GtkWidget *p_widget, gpointer user_data)
 * \brief Callback function called when a file is modify in the text view 
 * widget, to know if we need to save changes or not.
 * \param *p_widget : Widget from the callback signal. (Unused parameter)
 * \param user_data : Text view widget. (Unused parameter)
 * \return void 
 */

void cb_modif (GtkWidget *p_widget, gpointer user_data)
{
	if (docs.active)
	{
		docs.active->save = FALSE;
	}
    
	/* Unused parameter */
    (void) p_widget;
    (void) user_data;
}

/**
 * \fn void cb_save (GtkWidget *p_widget, gpointer user_data)
 * \brief Callback function called when pressing Save button, save the file at
 * its path if it exist, else ask a new path for the file.
 * \param *p_widget : Widget from the callback signal. (Unused parameter)
 * \param user_data : Text view widget. (Unused parameter)
 * \return void
 */

void cb_save (GtkWidget *p_widget, gpointer user_data)
{
	if (docs.active)
	{
		if (!docs.active->save)
		{
			/* File is not save */
			if (!docs.active->path)
			{
				GtkWidget *p_dialog = NULL;

				p_dialog = gtk_file_chooser_dialog_new ("Save file", NULL,
											GTK_FILE_CHOOSER_ACTION_SAVE,
											"Cancel", GTK_RESPONSE_CANCEL,
											"Save", GTK_RESPONSE_ACCEPT,
											NULL);
				if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
				{
					docs.active->path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (p_dialog));
				}
				gtk_widget_destroy (p_dialog);
			}

			/* File is already save or user give a new adress */
			if (docs.active->path)
			{
				FILE *fichier = NULL;
				fichier = fopen (docs.active->path, "w");
				if (fichier)
				{
					gchar *contents = NULL;
					gchar *locale = NULL;
					GtkTextIter start;
					GtkTextIter end;
					GtkTextBuffer *p_text_buffer = NULL;

					p_text_buffer = gtk_text_view_get_buffer (docs.active->p_text_view);
					gtk_text_buffer_get_bounds (p_text_buffer, &start, &end);
					contents = gtk_text_buffer_get_text (p_text_buffer, &start, &end, FALSE);
					locale = g_locale_from_utf8 (contents, -1, NULL, NULL, NULL);
					g_free (contents), contents = NULL;

					fprintf (fichier, "%s", locale);
					g_free (locale), locale = NULL;
					fclose (fichier), fichier = NULL;
					docs.active->save = TRUE;
				}
				else
				{
					print_warning("Impossible to save file %s",docs.active->path);
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

/**
 * \fn void cb_saveas (GtkWidget *p_widget, gpointer user_data)
 * \brief Callback function called when pressing Save As button, save the file 
 * at a choose path.
 * \param *p_widget : Widget from the callback signal.
 * \param user_data : Text view widget.
 * \return void
 */

void cb_saveas (GtkWidget *p_widget, gpointer user_data)
{
	if (docs.active)
	{
		Document tmp = *docs.active;
		docs.active->path = NULL;
		docs.active->save = FALSE;
		cb_save (p_widget, user_data);
		if (!docs.active->save)
		{
			(*docs.active) = tmp;
		}
	}
	else
	{
		print_warning ("No file open");
	}
}

/**
 * \fn void cb_about (GtkWidget *p_widget, gpointer user_data)
 * \brief Callback function called when pressing About button, open a
 * dialog box with some info about us.
 * \param *p_widget : Widget from the callback signal.
 * \param user_data : Text view widget.
 * \return void
 */

void cb_about (GtkWidget *p_widget, gpointer user_data)
{
	GtkWidget *p_about_dialog = NULL;

	p_about_dialog = gtk_about_dialog_new ();
	gtk_about_dialog_set_version (GTK_ABOUT_DIALOG (p_about_dialog), "0.4.2.42");
	gtk_about_dialog_set_program_name (GTK_ABOUT_DIALOG (p_about_dialog), 
								"Optical Character Recognition");

	const gchar *authors[5] = {"William.G","Alexandre.L","Pierre-Olivier.R",
								"Jeanne.M",NULL};
	gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG (p_about_dialog), authors);

	gtk_about_dialog_set_website (GTK_ABOUT_DIALOG (p_about_dialog), 
								"https://www.epita.fr/");
	GdkPixbuf *p_logo = NULL;

	p_logo = gdk_pixbuf_new_from_file ("./image_data/UI/logo_epita.jpg", NULL);
	gtk_about_dialog_set_logo (GTK_ABOUT_DIALOG (p_about_dialog), p_logo);

	switch(gtk_dialog_run (GTK_DIALOG (p_about_dialog)))
	{
		case GTK_RESPONSE_DELETE_EVENT:
			gtk_widget_destroy(p_about_dialog);
			return;
		break;
	}

  /* Unused Parameter */
  (void)p_widget;
  (void)user_data;
}

/**
 * \fn cb_doc(GtkWidget *p_widget, gpointer user_data)
 * \brief Callback function called when pressing Doc button.
 * Call system command "make doc".
 * \param *p_widget : Widget from the callback signal. (Unused parameter)
 * \param user_data : Text view widget. (Unused parameter)
 * \return void
 */

void cb_doc(GtkWidget *p_widget,gpointer user_data)
{
	int i = system("i3-sensible-terminal -e make doc &");

	if (i == -1 )
	{
		i = system("xterm -e make doc &");
		if(i == -1)
		{
			i = system("gnome-terminal -e make doc &");
		}
	}

	/* Unused parameter */
	(void) p_widget;
	(void) user_data;
}

/**
 * \fn cb_readme(GtkWidget *p_widget, gpointer user_data)
 * \brief Callback function called when pressing Readme button.
 * Show the Readme's text in a window to help the user.
 * \param *p_widget : Widget from the callback signal. (Unused parameter)
 * \param user_data : Text view widget. (Unused parameter)
 * \return void
 */

void cb_readme(GtkWidget *p_widget, gpointer user_data)
{
	FILE *file = NULL;
	file = fopen("src/UI/help", "r");
	
	char contents[250];
	
	
	GtkWidget *dialog;
	GtkWidget *dialog_contents;
	GtkWidget *label;

	dialog = gtk_dialog_new_with_buttons("README", GTK_WINDOW(docs.p_main_window),
										GTK_DIALOG_MODAL,"_Close",GTK_RESPONSE_CLOSE,NULL);
	dialog_contents = gtk_dialog_get_content_area (GTK_DIALOG(dialog));
	
	while(fgets(contents,sizeof(contents), file))
	{
			label = gtk_label_new (contents);
			gtk_box_pack_start(GTK_BOX(dialog_contents),label,FALSE,FALSE,0);
	}
	gtk_widget_show_all(dialog);
	gtk_dialog_run(GTK_DIALOG(dialog));

	gtk_widget_destroy(dialog);
	

	(void) p_widget;
	(void) user_data;
}

/**
 * \fn static void open_file (gchar *file_name, GtkTextView *p_text_view)
 * \brief Function used by cb_open, when the user want to open a file, and to
 * put its content in the text view widget.
 * \param *file_name : Path of the file.
 * \param *p_text_view : Text view widget.
 * \return void
 */
static void open_file (gchar *file_name, GtkTextView *p_text_view)
{
	g_return_if_fail (file_name && p_text_view);
	{
		gchar *contents = NULL;

		if (g_file_get_contents (file_name, &contents, NULL, NULL))
		{
			if(!docs.active)
				docs.active = g_malloc (sizeof (*docs.active));
			docs.active->path = g_strdup (file_name);

			docs.active->p_text_view = p_text_view;
			docs.active->save = TRUE;


			/* Copie of contents in GtkTextView */
			//gchar *utf8 = NULL;
			GtkTextIter iter;
			GtkTextBuffer *p_text_buffer = NULL;

			cb_new(NULL, p_text_view);
			gtk_widget_set_sensitive(GTK_WIDGET(docs.active->p_text_view),TRUE);

			/* Get buffer of GtkTextView to change text */
			p_text_buffer = gtk_text_view_get_buffer (p_text_view);
			gtk_text_buffer_get_iter_at_line (p_text_buffer, &iter, 0);

			gtk_text_buffer_insert (p_text_buffer, &iter, contents, -1);

			docs.active ->save = TRUE;
		}
		else
		{
			print_warning ("Failed to open %s\n", file_name);
		}
	}
}

/**
 * \fn static void open_ocr (gchar *file_name, neuNet *network)
 * \brief Function used by cb_ocr, when the user want to launch the OCR, this
 * function will put the text from OCR main function in the text view widget.
 * \param *file_name : Path of the picture.
 * \param *network : Neural Network.
 * \return void
 */

static void open_ocr(gchar *file_name, neuNet *network)
{
	GtkTextView *p_text_view = NULL;
	p_text_view = GTK_TEXT_VIEW(docs.active->p_text_view);
	if(docs.active)
		cb_close(NULL,p_text_view);
	g_return_if_fail (file_name && p_text_view);
	{
        gchar *contents = get_string(file_name,network);

		if(!docs.active)
			docs.active = g_malloc (sizeof (*docs.active));
		docs.active->path = NULL;

		docs.active->p_text_view = p_text_view;

		/* Copie of contents in GtkTextView */
		GtkTextIter iter;
		GtkTextBuffer *p_text_buffer = NULL;

		gtk_widget_set_sensitive (GTK_WIDGET (docs.active -> p_text_view), TRUE);

		/* Get buffer of GtkTextView to change text */
		p_text_buffer = gtk_text_view_get_buffer (p_text_view);
		gtk_text_buffer_get_iter_at_line (p_text_buffer, &iter, 0);

		gtk_text_buffer_insert (p_text_buffer, &iter, contents, -1);
		g_free(contents);

		docs.active->save = FALSE;
    }
}
