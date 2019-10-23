#include "../matrix/matrix.h"
#include "structNet.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "tools.h"


void freeNeuNet(neuNet *n)
{
	for(int i = 0; i < n->nbLay; i ++)
	{
		//layer* cL = n->layers[i];
		Freelayer(n->layers[i]);
	}
	free(n);
}

void SaveNeuNet(neuNet *n)
{
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

float sigmoid(float x)
{
        if(x == 0)
	  return 1;
	
	return 1.0/(1.0 * exp(-x));
}

float sigPrime(float x)
{
	return sigmoid(x)*(1-sigmoid(x));
}

Matrix* Sig(Matrix *m)
{
	Matrix* m2 = InitM(m->line, m->col);
	for(int i = 0; i < m->line; i++)
	{
		for( int j = 0; j < m->col; j++)
			PutM(m2, i, j, sigmoid(GetM(m,i, j)));
	}
	return m2;
}

Matrix* SigPrime(Matrix *m)
{
	Matrix* m2 = InitM(m->line, m->col);
	for(int i = 0; i < m->line; i++)
	{
		for( int j = 0; j < m->col; j++)
			PutM(m2, i, j, sigPrime(GetM(m,i, j)));
	}
	return m2;
}

void Freelayer(layer *cL)
{
	if(cL->biases !=NULL)
  		FreeM(cL->biases);
	if(cL->values != NULL)
  		FreeM(cL->values);
	if(cL->outputs)
  		FreeM(cL->outputs);
  	if(cL->weights)
  		FreeM(cL->weights);
	if(cL->errors)
  		FreeM(cL->errors);
  free(cL);
}

