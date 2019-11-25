#include "../matrix/matrix.h"
#include "structNet.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "save_net.h"

void SaveNeuNet(neuNet *n)
{
	
	FILE *file;
	file = fopen("network_save", "w");

	if(file != NULL)
	{
			
		for(int i = 0;i < n->nbLay; i++)
		{
			layer *cL = n->layers[i];
			printf("%i",i);
			if(cL->biases)
			{
				DisplayM(cL->biases);
			
				fwrite(cL->biases, sizeof(double), cL->biases->size-1, file);  //Segfault 
				fputc('\n', file);
			}
			
			if(cL->weights)
			{
				DisplayM(cL->weights);
				fwrite(cL->weights, sizeof(double), cL->weights->size-1, file);
				fputc('\n', file);
				
			}
		
		}
	}
	else
	{ printf("Pas de fichier où écrire !");
}

	
	fclose(file);
}

/*void LoadNeuNet()
{
	//DEPRECATED
	//we need to use fread/fwrite (efficiency)
	FILE *p;
	p = fopen("network", "w");
	if(p == NULL)
	{
		//errx("File can't be created");
	}


	int nbNeurons;
	int nbNeurons_precLayer = 0;	


	fprintf(p, "%i\n", n->nbLay);	
	for(int i = 0;i < n->nbLay; i++)
	{
		layer cL = n->layers[i];

		fprintf(p, "%i\n", cL->nbNeurons);
		fwrite(cL->biases, sizeof(double), cL->biases->size, p);
		fwrite(cL->weights, sizeof(double), cL->weights->size, p);
		
		
	}
	for(int i = 0; i < n->nbLay; i++)
	{
		layer* cL = n->layers[i];
		for(int j = 0; j < cL->weights->size; j++)
		{
			fprintf(p,"%f\n", GetPosM(cL->weights, j));
		}
	}
	
		
}*/

