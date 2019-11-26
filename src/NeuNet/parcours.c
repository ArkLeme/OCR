#include "../matrix/matrix.h"
#include "../process_segmentation/process_segm.h"
#include <stddef.h>
List* Parcours(char* path)
{
	List*p = NULL;
    List* lg = paragraph_segm(path);
    List * lp = lg;

    while(lp != NULL)
    {
        line_segm(lp);
        List *ll = lp->child;

        while(ll != NULL)
        {
            word_segm(ll);
            List *lw = ll->child;

            while(lw != NULL)
            {
                char_segm(lw);
                List *lc = lw->child;

                while(lc != NULL)
                {
					//TRAITEMENT
					p = AppendL(p, normalize_dimension(lc->mat), NULL);
				//	DisplayM(p->mat);
                    /**
                     * Liste de char du mot lc, les char sont dans le bon ordre
                     * pour le mort abcde :
                     * lc = a -> b -> c -> d -> e -> NULL
                     * par contre pour lc, lw et ll c'est à l'envers, pour :
                     * tu peux retirer les comms pour save les images dans le
                     * doss image_data/rlsa pour voir dans quel ordre elles
                     * sont.
                     */
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

    DeleteL(lg);
	return p;
}


