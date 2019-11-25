#include "../matrix/matrix.h"
#include "structNet.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "save_net.h"
#include "init_Network.h"

void SaveNeuNet(neuNet *n)
{
	
	FILE *file;
	file = fopen("network_save", "w");

	if(file != NULL)
	{
		for(int i = 0;i < n->nbLay; i++)
		{
			fputc(n->layers[i]->nbNeurons,file);
			fputc(' ', file);
		}
			
		for(int i = 0;i < n->nbLay; i++)
		{
			layer *cL = n->layers[i];
			printf("%i",i);
			
			printf("biases layer %i",i);
			DisplayM(cL->biases);
			fwrite(cL->biases, sizeof(double), cL->biases->size-1, file);  //Segfault 
			fputc('\n', file);

			printf("weights layer %i", i);
			DisplayM(cL->weights);
			fwrite(cL->weights, sizeof(double), cL->weights->size-1, file);
			fputc('\n', file);
				
			
		
		}
	}
	else
	{ printf("Pas de fichier où écrire !");
}

	
	fclose(file);
}

neuNet *LoadNeuNet()
{
	
	FILE *file;
	file = fopen("network", "w");
	if(file == NULL)
	{
		//errx("File can't be created");
		printf("rien à loader");
	}
	else
	{
		int layers_nbNeurons[3];
		int NbLay =0;
		char r = fgetc(file);
		
		

		while(r)		
		{
			layers_nbNeurons[NbLay] = r;
			fgetc(file);
			r = fgetc(file);
			NbLay+=1;
		}
		
		neuNet *network = init_network(layers_nbNeurons, NbLay);
		
		
		for(int i = 0;i < network->nbLay; i++)
		{
			layer *cL = network->layers[i];

			fread(cL->biases, sizeof(double), cL->biases->size, file);
			fgetc(file);
			fread(cL->weights, sizeof(double), cL->weights->size, file);
			fgetc(file);		
		
		}
	 	
	}


		
}

