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

    SaveMatAsIm(m, "image_data/rlsa/bin");

    SDL_FreeSurface(input);
	SDL_FreeSurface(gray);
	SDL_FreeSurface(contrast);
	SDL_FreeSurface(bin);

    SwapColor(m);

	return m;
}

Matrix* apply_rlsa(Matrix *m, int vr, int cr)
{
    Matrix *r = rlsa(m, vr, cr);
    SaveMatAsIm(r, "image_data/rlsa/binr");
    Matrix *rv = Vrlsa(r, 20);
    Matrix *rr = Hrlsa(rv, 30);
    SaveMatAsIm(rr, "image_data/rlsa/binrr");

    FreeM(r);
    FreeM(rv);

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
    RemoveLL(l); //Remove bloc white white pixel

    List* ll = l;
    while(ll)
    {
        ll->mat = normalize_dimension(ll->mat);
        ll = ll->next;
    }

    FreeM(twopass);
    FreeM(m);

    //SaveMatsAsIm(l, nbl, "image_data/label/char");

    return l;
}

List* paragraph_segm(char *path)
{
    Matrix *m = get_mat_from_png(path);
    int ml = 0;

    Matrix *rlsa = apply_rlsa(m, 80, 80);
    Matrix *twopass = CompLabeling(rlsa, &ml);
    int nbl = NumberLabel(twopass, ml);
    ReduceLabel(twopass, ml);

    PosM **pos = FindPosMat(twopass, nbl);
    List *l = ListOfMat(m, pos, nbl);
    RemoveLL(l); //Remove bloc white white pixel

    SaveMatAsIm(twopass, "image_data/rlsa/rlsa");

    FreeM(twopass);
    FreeM(m);
    FreeM(rlsa);

    SaveMatsAsIm(l, nbl, "image_data/label/char");

    return l;

}

List* line_segm(List* par)
{
    while(par != NULL)
    {
        int ml = 0;
    }
}
