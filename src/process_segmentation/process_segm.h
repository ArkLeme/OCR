#ifndef PROCESS_SEGM_H
#define PROCESS_SEGM_H

#include "../sdl_tools/sdl_tools.h"
#include "../preprocessing/preprocessing.h"
#include "../matrix/matrix_image.h"

/**
 * \file process_segm.h
 * \brief header of process_segm.h
 * \author William.G
 */

/**
 * \brief Get a binary matrix from an png image
 * \param path : Path of the input image
 * \return : binary matrix of the image
 */
Matrix *get_matrix_from_png(char *path);

#endif
