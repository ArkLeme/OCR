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

    SaveMatAsIm(m, "image_data/rlsa/bin.bmp");

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
    Matrix *rr = Hrlsa(r, cr/2);
    Matrix *rv = Vrlsa(rr, vr/3);

    FreeM(r);
    FreeM(rr);

    return rv;
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

    Matrix *rlsa = apply_rlsa(m, 60, 60);
    Matrix *twopass = CompLabeling(rlsa, &ml);
    int nbl = NumberLabel(twopass, ml);
    ReduceLabel(twopass, ml);

    PosM **pos = FindPosMat(twopass, nbl);
    List *l = ListOfMat(m, pos, nbl);
    RemoveLL(l); //Remove bloc with white pixel

    SaveMatAsIm(twopass, "image_data/rlsa/rlsa.bmp");

    FreeM(twopass);
    FreeM(m);
    FreeM(rlsa);

    //SaveMatsAsIm(l, nbl, "image_data/label/par");

    return l;

}

List* line_segm(List* p)
{
    List* par = p;
    int ml = 0;

    Matrix *m = par->mat;
    //SaveMatAsIm(m, "image_data/rlsa/par_empty.bmp");
    Matrix *rlsa = apply_rlsa(m, 0, m->col);

    //SaveMatAsIm(rlsa, "image_data/rlsa/rlsa.bmp");
    //SaveMatAsIm(m, "image_data/rlsa/par_rlsa.bmp");
    Matrix *twopass = CompLabeling(rlsa, &ml);
    int nbl = NumberLabel(twopass, ml);
    ReduceLabel(twopass, ml);
    //SaveMatAsIm(twopass, "image_data/rlsa/test1.bmp");

    PosM **pos = FindPosMat(twopass, nbl);
    List *l = ListOfMat(m, pos, nbl);
    RemoveLL(l);

    //SaveMatsAsIm(l, nbl, "image_data/label/line");
    par->child = l;

    FreeM(twopass);
    FreeM(rlsa);

    return p;
}

List* word_segm(List* p)
{
    List* line = p;
        int ml = 0;
        Matrix *m = line->mat;
        //SaveMatAsIm(m, "image_data/rlsa/line_empty.bmp");
        Matrix *rlsa = apply_rlsa(m, m->line, 20);
        Matrix *twopass = CompLabeling(rlsa, &ml);
        int nbl = NumberLabel(twopass, ml);
        ReduceLabel(twopass, ml);
        //SaveMatAsIm(twopass, "image_data/rlsa/rlsaV.bmp");

        PosM **pos = FindPosMat(twopass, nbl);
        List *l = ListOfMat(m, pos, nbl);

        RemoveLL(l);

        //SaveMatsAsIm(l, nbl, "image_data/label/word.bmp");
        line->child = l;

        FreeM(twopass);
        FreeM(rlsa);

    return p;
}

List* char_segm(List* w)
{
    List* word = w;
    int ml = 0;
    Matrix *wo = word->mat;
    Matrix *twopass = CompLabeling(wo, &ml);
    int nbl = NumberLabel(twopass, ml);
    ReduceLabel(twopass, ml);

    PosM **pos = FindPosMat(twopass, nbl);
    List *l = ListOfMat(wo, pos, nbl);

    RemoveLL(l);

    List* sorted_char = sort_list(l);
    List* word_no_point = remove_point(sorted_char);

    word->child = word_no_point;

    FreeM(twopass);

    return w;
}

List* remove_point(List *c)
{
    List *first = c;

    while(first != NULL)
    {
        List* next = first->next;
        if(next != NULL && ((Matrix*) (next->mat))->size < 30)
        {
            first->next = next->next;
            FreeL(next);
        }

        first = first->next;
    }

    if(c != NULL && ((Matrix*) (c->mat))->size < 20)
    {
        return RemoveFL(c);
    }

    return c;
}

List* sort_list(List *c)
{
    List* first = c;
    while(first != NULL)
    {
        List *f = first;
        List *min = first;

        while(f != NULL)
        {
            if(f->pos->mx < min->pos->mx)
                min = f;
            f = f->next;
        }

        swap_list(first, min);
        first = first->next;
    }

    return c;
}

void swap_list(List *c1, List *c2)
{
    PosM *p = c1->pos;
    Matrix *m = c1->mat;

    c1->pos = c2->pos;
    c1->mat = c2->mat;

    c2->pos = p;
    c2->mat = m;
}
