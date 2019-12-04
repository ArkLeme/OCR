#include "get_list_segmented.h"
#include "../string/string_operation.h"
#include "../segmentation/segmentation.h"
#include "../output_files/create_string.h"
#include "../NeuNet/memory_handler.h"
#include "../NeuNet/neuNet.h"
#include "../NeuNet/init_Network.h"
#include "../NeuNet/save_net.h"
#include "../NeuNet/structNet.h"

/**
 * \file get_list_segmented.c
 * \brief This files contains the function to create a list of every
 * paragraph, line, word and char from the image. It basically apply all
 * the preprocessing traitement and segmentation function.
 * \author William.G
 */

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

    while(lp != NULL)
    {
        lines_segmentation(lp);
        List *ll = lp->child;

        while(ll != NULL)
        {
            words_segmentation(ll);
            List *lw = ll->child;

            while(lw != NULL)
            {
                char_segm(lw);

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

/**
 * \fn char* get_string(char *path)
 * \brief This function get the string of the text, it is use to print the
 * text in the UI so the user can modifiy it if it's needed.
 *
 * \param path : path of the image
 *
 * \return string detected by the segmentation.
 */
char* get_string(char *path)
{
    List *l = get_list_segmented(path);

    neuNet *network = LoadNeuNet("neuralNetwork_data/network_saved");

    char *c = generate_string(l, network);

    DeleteL(l);

    freeNeuNet(network);

    return c;
}
