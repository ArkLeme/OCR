#ifndef CREATE_STRING_H
#define CREATE_STRING_H

#include "../matrix/matrix.h"
#include "../NeuNet/structNet.h"

/**
 * \file create_string.h
 * \brief header of create_string.c
 * \author William.G
 */

char* char_string(List *chr, neuNet *network);

char* word_string(List *word, neuNet *network);

char* line_string(List *line, neuNet *network);

char* para_string(List *para, neuNet *network);

char* text_string(List *text, neuNet *network);

char* generate_string(List *l, neuNet *network);

#endif
