#include "../matrix/matrix.h"
#include "structNet.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory_handler.h"

void ClearNeuNet(neuNet *n)
{
	layer* cL = n->layers[0];
//	FreeM(cL->values); //Maybe it will be needed to only free the pointer
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


Pool* InitPool(size_t size)
{
	Pool *p = malloc(sizeof(Pool));
	p->size = size;
	p->examples = malloc(sizeof(Matrix*) * size);
	//*p->examples = malloc(sizeof(Matrix) * size);
	p->results = malloc(sizeof(char) * size);
	return p;
}

void FreePool(Pool*p)
{
	for(size_t i = 0; i < p->size; i++)
	{
	//	DisplayM(*(p->examples+i));
		FreeM(*(p->examples+i));
	}
	free(p->examples);
	free(p->results);
	free(p);
}

void FreePoolP(Pool*p)
{
	free(p->examples);
	free(p->results);
	free(p);
}
