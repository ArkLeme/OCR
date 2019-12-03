#ifndef SEGM_H
#define SEGM_H

#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../sdl_tools/sdl_tools.h"
#include "../matrix/matrix.h"


/**
 * \file segmentation.h
 * \brief header of segmentation.c
 * \author Alexandre.L
 */

/*
 * Lines segmentation of a paragraph.
 * List *listofparagraph : The paragraph.
 * return void
 */

void lines_segmentation(List *listofparagraph);

/* Words segmentation of a line.
 * List *listoflines : The line.
 * return void
 */

void words_segmentation(List *listoflines);

#endif
