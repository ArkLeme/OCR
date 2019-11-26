#ifndef PROCESS_SEGM_H
#define PROCESS_SEGM_H

#include "../matrix/matrix_image.h"

/**
 * \file process_segm.h
 * \brief header of process_segm.c
 * \author William.G
 */

Matrix* get_mat_from_png(char *path);

List* first_segmentation(char *path);

List* paragraph_segm(char *path);

List* line_segm(List* p);

List* word_segm(List* p);

List* char_segm(List *p);

List* remove_point(List *w);

int is_point(Matrix *m);

List* sort_list(List *c);

void swap_list(List *c1, List *c2);
#endif
