#ifndef PROCESS_SEGM_H
#define PROCESS_SEGM_H

#include "../preprocessing/preprocessing.h"
#include "../matrix/matrix_image.h"

/**
 * \file process_segm.h
 * \brief header of process_segm.c
 * \author William.G
 */

/**
 * \brief Create a binary matrix from a png image where black pixel are one 
 * and white pixel are 0
 * \param path : Path of the input image
 * \return the binary matrix
 */

Matrix *get_matrix_from_png(char *path);

#endif
