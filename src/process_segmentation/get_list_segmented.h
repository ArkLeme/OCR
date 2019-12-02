#ifndef GET_LIST_SEGMENTED_H
#define GET_LIST_SEGMENTED_H

#include "process_segm.h"
#include "../NeuNet/structNet.h"

/**
 * \file get_list_segmented.h
 * \brief header of get_list_segmented.c
 * \author William.G
 */

List* get_list_segmented(char *path);

char *get_string(char *path, neuNet *network);

#endif
