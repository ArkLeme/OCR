#ifndef PROCESS_SEGM_H
#define PROCESS_SEGM_H

#include "../matrix/matrix_image.h"

/**
 * \file process_segm.h
 * \brief header of process_segm.c
 * \author William.G
 */

List* first_segmentation(char *path);

List* paragraph_segm(char *path);

List* line_segm(List* p);

List* word_segm(List* p);
#endif
