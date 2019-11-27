#include "../matrix/matrix.h"
#include "structNet.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "save_net.h"
#include "init_Network.h"
#include <string.h>



/*!
 * \author jeanne.morin
 * \Save the network in a binary file
 * \param network is the current network, needed to be saved.
 */

void SaveNeuNet(neuNet *n)
{
  
	FILE *file;
	file = fopen("network_save", "w");
	if(file == NULL)
	  {
	    printf("Erreur : SaveNeuNet : No stream opened")
	  }

	else
	  {
	    fprintf(file, "%lu\n{",n->nbLay);
	    for(size_t i = 0; i < mynet->size;i++)
	      {
		fprintf(file,"%lu",n->layers[i]);
		if (i < net->nbLay-1)
		  fprintf(file,",");
	      }
	    fprintf(myfile,",}\n");
	    double value;
	
	    for(size_t i = 1; i < n->nbLay; i++)
	      {
		layer *current_layer = n->layers[i];
	    	    
		for (size_t j = 0; j < current_layer->nbNeurons; j++)
		  {
		    for(size_t k = 0; k <prec_layer->weights->col ;k++)
		      {
			value = GetM(curren_layer->weights,j,k);
			fprintf(file,"%lf\n",value);
		      }

		    value = GetM(curren_layer->biases,j,0);
		    fprintf(file,"b\n%lf\n", value);
		  }
	    
		fprintf(file,"$\n");
	      }
	
	    fclose(myfile);
	  }
}

/*!
 * \author jeanne.morin
 * \Load the network from the save file, written in binary.
 */

neuNet *LoadNeuNet()
{
	
	FILE *file;
	file = fopen("network", "r");
	if(file == NULL)
	{
		//errx("File can't be created");
		printf("rien à loader");
		
	}
	else
	{
		int layers_nbNeurons[3];
		int NbLay =0;
		int r = fgetc(file);
		
		

		while(r)		
		{
			layers_nbNeurons[NbLay] = r; //a changer avec double while ou autre fonction de lecture genre fgets
			fgetc(file);
			r = fgetc(file);
			NbLay+=1;
		}
		
		neuNet *network = init_network(layers_nbNeurons, NbLay);
		
		
		for(int i = 0;i < network->nbLay; i++) //du coup peut etre commencer à  si tu save pas le 1er layer
		{
			layer *cL = network->layers[i];

			fread(cL->biases, sizeof(double), cL->biases->size, file);
			fgetc(file);
			fread(cL->weights, sizeof(double), cL->weights->size, file);
			fgetc(file); // ce for c'est grave clean		
		
		}


return network;

	 	
	}


		
}

