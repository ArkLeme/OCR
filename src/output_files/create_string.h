#ifndef CREATE_STRING_H
#define CREATE_STRING_H

#include "../matrix/matrix.h"

char* char_string(List *chr);

char* word_string(List *word);

char* line_segm(List *line);

char* para_segm(List *para);

char* text_segm(List *text);

void write_files(char* path, List *l);

#endif
