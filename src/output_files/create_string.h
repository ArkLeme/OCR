#ifndef CREATE_STRING_H
#define CREATE_STRING_H

#include "../matrix/matrix.h"


/**
 * \file create_string.h
 * \brief header of create_string.c
 * \author William.G
 */

char* char_string(List *chr);

char* word_string(List *word);

char* line_string(List *line);

char* para_string(List *para);


char* text_string(List *text);

char* text_string(List *text);

void write_files(char* path, List *l);

#endif
