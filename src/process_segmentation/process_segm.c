#include "process_segm.h"
#include "../segmentation/rlsa.h"
#include "../comp_labeling/comp_labeling.h"
#include "separate_matrix.h"
#include "../preprocessing/preprocessing.h"

/**
 * \file process_segm.c
 * \brief This files apply all segmentation algorithm.
 * \author William.G
 */

/**
 * \fn Matrix* get_mat_from_png(char *path)
 * \brief Aplpy all prepocessing to an image and return the binary Matrix.
 *
 * \param path : path of the png
 *
 * \return binary matrix
 */
Matrix* get_mat_from_png(char *path)
{
	SDL_Surface *input = LoadImage(path);
	SDL_Surface *gray = GrayScale(input);
    SDL_Surface *brightness = brightness_filter(gray);
	SDL_Surface *contrast = Contrast(brightness);
	SDL_Surface *bin = Otsu(contrast);

	Matrix *m = GetMatFromIm(bin);

    SaveMatAsIm(m, "image_data/rlsa/bin.bmp");

    SDL_FreeSurface(brightness);
    SDL_FreeSurface(input);
	SDL_FreeSurface(gray);
	SDL_FreeSurface(contrast);
	SDL_FreeSurface(bin);

    SwapColor(m);

	return m;
}

/**
 * \fn Matrix* apply_rlsa(Matrix *m, int vr, int cr)
 * \brief apply rlsa to matrix with vr as vertical treshold
 * and cr as horizontal treshold.
 *
 * \param m : matrix
 * \param vr : vertical threshold
 * \param cr : horizontal treshold
 *
 * \return new matrix
 */
Matrix* apply_rlsa(Matrix *m, int vr, int cr)
{

    Matrix *r = rlsa(m, vr, cr);
    Matrix *rr = Hrlsa(r, cr/2);
    Matrix *rv = Vrlsa(rr, vr/3);

    FreeM(r);
    FreeM(rr);

    return rv;
}

/**
 * \fn List* first_segmentation(char *path)
 * \brief Old function, it is not use, but it can be usefull for DEBUG
 *
 * \param path : path of the image
 *
 * \return List of paragraph
 */
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


/**
 * \fn static int is_image(List *l)
 * \brief Detect if the Matrix is an image
 * according to the number of pixel in the image.
 *
 * \param l : List containing the Matrix
 *
 * \return 1 if it is an image, 0 otherwise
 */
static int is_image(List *l)
{
    Matrix *m = ((Matrix*) (l->mat));

    int black = 0;

    for(int i = 0; i < m->size; i++)
    {
        if(GetPosM(m, i))
            black++;
    }

    return black > m->size - m->size/3;
}

/**
 * \fn static List* remove_image(List *p)
 * \brief Remove every image in the list of paragraph
 *
 * \param p : list of paragraph
 *
 * \return pointer to the first element
 */
static List* remove_image(List *p)
{
    List *first = p;
    if(first != NULL)
    {
        List *next = first->next;

        while(first->next != NULL)
        {
            next = first->next;

            if(is_image(first->next))
            {
                first->next = next->next;
                FreeL(next);
            }

            first = first->next;
        }
    }

    if(is_image(p))
        return RemoveFL(p);

    return p;
}

 /**
 * \fn List* paragraph_segm(char *path)
 * \brief Apply the first segmentation, it take the path of the file
 * and it return a List of paragraph.
 *
 * \param path : path of the image
 *
 * \return List of paragraph
 */
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

    l = remove_image(l);

    //RemoveFL(l); //Remove bloc with white pixel

    SaveMatAsIm(twopass, "image_data/rlsa/rlsa.bmp");

    FreeM(twopass);
    FreeM(m);
    FreeM(rlsa);

    //SaveMatsAsIm(l, nbl, "image_data/label/par");

    return l;

}

 /**
 * \fn List* line_segm(List* p)
 * \brief Apply the second segmentation, it take a paragraph
 * and it set child of p as List of line.
 *
 * \param p : One paragraph
 *
 * \return List of paragraph
 */
List* line_segm(List* p)
{
    int ml = 0;

    Matrix *m = p->mat;
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

    //SaveMatsAsIm(l, nbl, "image_data/label/line");
    p->child = l;

    FreeM(twopass);
    FreeM(rlsa);

    return p;
}

 /**
 * \fn List* word_segm(List* p)
 * \brief Apply the third segmentation, it take a line
 * and it set child of p as List of word.
 *
 * \param p : One line
 *
 * \return List of paragraph
 */
List* word_segm(List* p)
{
    int ml = 0;
    Matrix *m = p->mat;
    //SaveMatAsIm(m, "image_data/rlsa/line_empty.bmp");
    Matrix *rlsa = apply_rlsa(m, m->line, 20);
    Matrix *twopass = CompLabeling(rlsa, &ml);
    int nbl = NumberLabel(twopass, ml);
    ReduceLabel(twopass, ml);
    //SaveMatAsIm(twopass, "image_data/rlsa/rlsaV.bmp");

    PosM **pos = FindPosMat(twopass, nbl);
    List *l = ListOfMat(m, pos, nbl);

    //SaveMatsAsIm(l, nbl, "image_data/label/word.bmp");
    p->child = l;

    FreeM(twopass);
    FreeM(rlsa);

    return p;
}

/**
 * \fn static int is_point(List *l)
 * \brief detect if the matrix is a point of an i or and j
 * if the first matrix is not a point reurn 0
 * if the first matrix is a point return 1
 * if the second matrix is a point return 2
 *
 * \param m : List
 *
 * \return different case
 */
static int is_point(List *l)
{
    if(l != NULL && l->next != NULL)
    {
        int m1x = l->pos->mx;
        int M1x = l->pos->Mx;

        int m2x = l->next->pos->mx;
        int M2x = l->next->pos->Mx;

        int m1y = l->pos->My;
        int m2y = l->next->pos->My;


        if(m1x >= m2x - 1 && M1x <= M2x + 1)
            return 1;

        if(m1y > m2y && m1x <= m2x + 1 && M1x >= M2x - 1)
            return 2;
    }

    return 0;
}

/**
 * \fn static List* remove_point(List *c)
 * \brief Delete little matrix which are not char, such as point or some
 * unwanted noise in the image.
 *
 *\param c : List of char

 \return the list
 */
static List* remove_point(List *c)
{
    List *first = c;

    while(first != NULL)
    {
        List* next = first->next;

        int cas = is_point(next);

        if(cas == 1)
        {
            first->next = next->next;
            FreeL(next);
        }
        else if(cas == 2)
        {
            List *point = next->next;
            next->next = point->next;
            FreeL(point);
        }

        first = first->next;
    }

    int cas = is_point(c);

    if(cas == 1)
        return RemoveFL(c);

    if(cas == 2)
    {
        c->next = RemoveFL(c->next);
        return c;
    }

    return c;
}

/**
 * \fn static void swap_list(List *c1, List *c2)
 * \brief swap 2 element in the list
 *
 * \param c1 : first list
 * \param c2 : second list
 */

static void swap_list(List *c1, List *c2)
{
    PosM *p = c1->pos;
    Matrix *m = c1->mat;

    c1->pos = c2->pos;
    c1->mat = c2->mat;

    c2->pos = p;
    c2->mat = m;
}

/**
 * \fn static List* sort_list(List *c)
 * \brief Sort a list of char, the component labeling do not sort the char in
 * the correct order so we must sort them.
 *
 * \param c : List of char
 *
 * \return List of char
 */
static List* sort_list(List *c)
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
/**
 * \fn List* char_segm(List* p)
 * \brief Apply the fourth segmentation, it take a word
 * and it set child of p as List of char.
 *
 * \param p : One word
 *
 * \return List of paragraph
 */
List* char_segm(List* w)
{
    int ml = 0;
    Matrix *word = w->mat;
    Matrix *twopass = CompLabeling(word, &ml);
    int nbl = NumberLabel(twopass, ml);
    ReduceLabel(twopass, ml);

    PosM **pos = FindPosMat(twopass, nbl);
    List *l = ListOfMat(word, pos, nbl);

    List* sorted_char = sort_list(l);
    List* word_no_point = remove_point(sorted_char);

    w->child = word_no_point;

    FreeM(twopass);

    return w;
}
