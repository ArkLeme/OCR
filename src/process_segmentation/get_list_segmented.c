#include "get_list_segmented.h"
#include "../string/string_operation.h"
#include "../segmentation/segmentation.h"

void testBin(char* path);
void SaveMat(List *l, int i, char *p);

List* get_list_segmented(char *path)
{
    List *lg = paragraph_segm(path);
    List *lp = lg;

    int p = 0;
    int l = 0;
    int w = 0;
    int c = 0;

    while(lp != NULL)
    {
        line_segm(lp);
        List *ll = lp->child;
        SaveMat(lp, p, "para");
        p++;

        while(ll != NULL)
        {
            words_segmentation(ll);
            List *lw = ll->child;
            SaveMat(ll, l, "line");
            l++;

            while(lw != NULL)
            {
                char_segm(lw);
                List *lc = lw->child;
                SaveMat(lw, w, "word");
                w++;

                while(lc != NULL)
                {
                    SaveMat(lc, c, "char");
                    c++;

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

void SaveMat(List *l,  int i, char *n)
{
    char *sint = Itoa(i);
    char *p = Concatene("../../image_data/rlsa/", n);
    char *s = Concatene(p, sint);
    char *sf = Concatene(s, ".bmp");

    SaveMatAsIm(((Matrix*) (l->mat)),sf);

    free(s);
    free(sint);
    free(sf);
    free(p);
}
