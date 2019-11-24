#include "../matrix/matrix.h"
#include "structNet.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "save_net.h"

void SaveNeuNet(neuNet *n)
{
	//DEPRECATED
	//we need to use fread/fwrite (efficiency)
	FILE *p;
	p = fopen("network", "w");
	if(p == NULL)
	{
		//errx("File can't be created");
	}
	fprintf(p, "%i\n", n->nbLay);	
	for(int i = 0;i < n->nbLay; i++)
	{
		fprintf(p, "%i\n", n->layers[i]->nbNeurons);
	}
	for(int i = 0; i < n->nbLay; i++)
	{
		layer* cL = n->layers[i];
		for(int j = 0; j < cL->weights->size; j++)
		{
			fprintf(p,"%f\n", GetPosM(cL->weights, j));
		}
	}
	fclose(p);
}

void LoadNeuNet()
{
	FILE *p = fopen("network", "r");
	if(p == NULL)
	{
		//errx("File can't be created");
	}
	
		
}

