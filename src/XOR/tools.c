#include "../matrix/matrix.h"
#include "structNet.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

void ClearNeuNet(neuNet *n)
{
	layer* cL = n->layers[0];
	FreeM(cL->values);
  	FreeM(cL->outputs);
	for(int i = 1; i < n->nbLay; i++)
	{
		layer* cL = n->layers[i];
  		FreeM(cL->values);
  		FreeM(cL->outputs);
  		FreeM(cL->errors);
	}
}


void freeNeuNet(neuNet *n)
{
	//free first layer
	layer* fL = n->layers[0];
	FreeM(fL->biases);
	FreeM(fL->weights);
	free(fL);
	for(int i = 1; i < n->nbLay; i ++)
		Freelayer(n->layers[i]);
	free(n);
}

void Freelayer(layer *cL)
{
  	FreeM(cL->biases);
  	FreeM(cL->weights);
	free(cL);
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

double sigmoid(float x)
{	
	return (double) 1.0/(1.0 + exp(-x));
	//return log(1 + exp(x)); // relu soft plus
	//return (exp(2*x) - 1)/(exp(2*x) + 1);
}

double sigPrime(float x)
{
	return sigmoid(x)*(1-sigmoid(x));
	//return 1/(1+exp(-x)); //relu prime
	//return 1- ( sigmoid( x)* sigmoid( x));
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
