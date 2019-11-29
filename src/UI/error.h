#ifndef H_ERROR
#define H_ERROR

/**
 * \file error.h
 * \brief header of error.c
 * \author Alexandre.L
 */

/*
 * Print function called when an info must appear in a dialog box.
 * char * : Message to display
 * return void
 */
void print_info (char *, ...);

/*
 * Print function called when a warning must appear in a dialog box.
 * char * : Message to display
 * return void
 */
void print_warning (char *, ...);

/*
 * Print function called when an error must appear in a dialog box.
 * char * : Message to display
 * return void
 */

void print_error (char *, ...);

#endif /* not H_ERROR */
