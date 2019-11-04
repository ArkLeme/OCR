#ifndef PROCESS_SEGM_H
#define PROCESS_SEGM_H

#include "../matrix/matrix.h"
#include "../sdl_tools/sdl_tools.h"

/**
 * \brief Get a binary matrix from an png image
 * \param path : Path of the input image
 * @return : binary matrix of the image
 */
Matrix *get_matrix_from_png(char *path);

#endif
