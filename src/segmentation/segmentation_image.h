#ifndef SEGMENTATION_IMAGE
#define SEGMENTATION_IMAGE

#include <stdio.h>
#include <stdint.h>
#include <err.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../sdl_tools/sdl_tools.h"


void image_lines_segmentation(SDL_Surface* img);
void image_char_segmentation(SDL_Surface *img, int begin, int end);

#endif
