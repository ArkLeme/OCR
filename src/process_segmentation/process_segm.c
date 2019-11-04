#include "process_segm.h"

Matrix *get_mat_from_png(char* path)
{
	SDL_Surface input = LoadImage(path);
	SDL_Surface gray = Gray(input);
	SDL_Surface contrast = Contrast(gray);
	SDL_Surface bin = Otsu(constrast);

	Matrix *m = GetMatFromIm(bin);

	Free_Surface(input);
	Free_Surface(gray);
	Free_Surface(contrast);
	Free_Surface(bin);

	return m;
}
