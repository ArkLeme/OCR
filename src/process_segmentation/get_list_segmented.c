#include "get_list_segmented.h"
#include "../string/string_operation.h"
#include "../segmentation/segmentation.h"
#include "../output_files/create_string.h"

/**
 * \file get_list_segmented.c
 * \brief This files contains the function to create a list of every
 * paragraph, line, word and char from the image. It basically apply all
 * the preprocessing traitement and segmentation function.
 * \author William.G
 */

/**
 * \fn static void SaveMat(List *l, int i, char *n)
 * \brief Save Matrix in the List as Image.
 * It is a debug function but it can be usef to save only a part of the text.
 *
 * \param l : List
 * \param i : index to create multiple image with different name
 * \param n : type of the Matrix we are saving (para, line, word or char)
 */
static void SaveMat(List *l,  int i, char *n)
{
    char *sint = Itoa(i);
    char *p = Concatene("image_data/rlsa/", n);
    char *s = Concatene(p, sint);
    char *sf = Concatene(s, ".bmp");

    SaveMatAsIm(((Matrix*) (l->mat)),sf);

    free(s);
    free(sint);
    free(sf);
    free(p);
}

/**
 * \fn List* get_list_segmented(char *path)
 * \brief Create the matrix of the text and apply all the pretraitement.
 *  Create the list of every element in the the text and return a list of it.
 *  It can also save every Matrix as image.
 *
 *  \param path : path of the image
 *
 * \return List of every element in the text
 */
List* get_list_segmented(char *path)
{
    List *lg = paragraph_segm(path);
    List *lp = lg;

    /*
    int p = 0;
    int l = 0;
    int w = 0;
    int c = 0;
    */

    while(lp != NULL)
    {
        lines_segmentation(lp);
        List *ll = lp->child;
        //SaveMat(lp, p, "para");
        //p++;

        while(ll != NULL)
        {
            words_segmentation(ll);
            List *lw = ll->child;
            //SaveMat(ll, l, "line");
            //l++;

            while(lw != NULL)
            {
                char_segm(lw);
                List *lc = lw->child;
                //SaveMat(lw, w, "word");
                //w++;

                while(lc != NULL)
                {
                    //SaveMat(lc, c, "char");
                    //c++;

                    lc = lc->next;
                    //lc = NULL;
                }

                lw = lw->next;
                //lw = NULL;
            }

            ll = ll->next;
            //ll = NULL;
        }

        lp = lp->next;
        //lp = NULL;
    }

    return lg;
}

char *get_string(char *path)
{
    List *l = get_list_segmented(path);

    char *c = generate_string(l);

    DeleteL(l);

    return c;
}
