#include "process_segm.h"

Matrix *get_mat_from_png(char* path)
{
	SDL_Surface *input = LoadImage(path);
	SDL_Surface *gray = GrayScale(input);
	SDL_Surface *contrast = Contrast(gray);
	SDL_Surface *bin = Otsu(contrast);

	Matrix *m = GetMatFromIm(bin);

    SDL_FreeSurface(input);
	SDL_FreeSurface(gray);
	SDL_FreeSurface(contrast);
	SDL_FreeSurface(bin);

	return m;
}
