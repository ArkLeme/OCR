#ifndef SEGM_H
#define SEGM_H

#include <stdio.h>
#include <stdint.h>
#include <err.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../sdl_tools/sdl_tools.h"


void lines_segmentation(SDL_Surface* img);
void char_segmentation(SDL_Surface *img, int begin, int end);

#endif
