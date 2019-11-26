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
			fputc(n->layers[i]->nbNeurons,file);//ne fonctionne pas car un nombre != 
			//un character
			//pense à Itoa(int to string) qu'a fait william et la fonctin fprintf("%s\n", itoa); 
			fputc(' ', file);
		}
		fputc('\n',file);
			
		for(int i = 0;i < n->nbLay; i++) //premier layer n'a rien a save (pas de poids biais sur le premier)
		{
			layer *cL = n->layers[i];
			printf("%i",i);
			
			printf("biases layer %i",i);
			
			if(cL->biases->size != fwrite(cL->biases, sizeof(double), cL->biases->size-1, file)) //Je pense pas qu'il y ai besoin du  puisque tu écris le nb d'element
				{printf("Pas write tous les élèements !!");}
			else
{ 
			fputc('\n', file);

			printf("weights layer %i", i);
			DisplayM(cL->weights);
			fwrite(cL->weights, sizeof(double), cL->weights->size-1, file);//idem
			fputc('\n', file);}
				
			
		
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
	 	
	}


		
}

