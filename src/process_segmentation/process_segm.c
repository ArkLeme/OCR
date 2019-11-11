#include "process_segm.h"
#include "../segmentation/rlsa.h"
#include "../comp_labeling/comp_labeling.h"
#include "separate_matrix.h"
#include "../preprocessing/preprocessing.h"

Matrix* get_mat_from_png(char* path)
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

Matrix* apply_rlsa(Matrix *m)
{
    Matrix *r = rlsa(m, 80);
    Matrix *rv = Vrlsa(r, 15);
    Matrix *rr = Hrlsa(rv,15);

    FreeM(r);
    FreeM(rv);
    FreeM(m);

    return rr;
}

List* first_segmentation(char *path)
{
    Matrix *m = get_mat_from_png(path);
    int ml = 0;
    Matrix *twopass = CompLabeling(m, &ml);
    int nbl = NumberLabel(twopass, ml);
    ReduceLabel(twopass, ml);

    PosM **pos = FindPosMat(twopass, nbl);
    List *l = ListOfMat(twopass, pos, nbl);

    SaveMatsAsIm(l, nbl - 1, "image_data/label/char");

    FreeM(twopass);
    FreeM(m);

    return l;
}
