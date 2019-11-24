#ifndef SEGM_H
#define SEGM_H

#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../sdl_tools/sdl_tools.h"
#include "../matrix/matrix.h"

void lines_segmentation(List *listofparagraph);
void words_segmentation(List *listoflines);

#endif
