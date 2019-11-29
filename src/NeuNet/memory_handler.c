#include "../matrix/matrix.h"
#include "structNet.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory_handler.h"

/*!
 * \author pierre-olivier.rey
 * \brief Clear temporary matrix of the neunet. 
 * \param n the neuNet 
 * Clear input, output and erros matrix of layers of n.
 * Used for cleaning after each iteration of training.
 */
void ClearNeuNet(neuNet *n)
{
	layer* cL = n->layers[0];
  	FreeM(cL->outputs);
	for(int i = 1; i < n->nbLay; i++)
	{
		layer* cL = n->layers[i];
  		FreeM(cL->values);
  		FreeM(cL->outputs);
//		DisplayM(cL->errors);
//		if(cL->errors)
 // 			FreeM(cL->errors);
	}
}

/*!
 * \author pierre-olivier.rey
 * \brief Free the neural network. 
 * \param n the neuNet 
 * All matrix are freed finally the network too.
 * To call just before the end of the program.
 */
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

/*!
 * \author pierre-olivier.rey
 * \brief Free biases and weights of a layer.
 * \param n the neuNet 
 * Not made to be call anywhere but in freeNeuNet.
 */
void Freelayer(layer *cL)
{
  	FreeM(cL->biases);
  	FreeM(cL->weights);
	free(cL);
}

/*!
 * \author pierre-olivier.rey
 * \brief Clear temporary matrix of the neunet. 
 * \param n the neuNet 
 * Clear matrix used for batch propagation.
 */
void FreeBatchMatrix(neuNet*n)
{
	for(int i = 1; i < n->nbLay; i++)
	{
		FreeM(n->layers[i]->weight_batch);
		FreeM(n->layers[i]->biases_batch);
	}
}

/*!
 * \author pierre-olivier.rey
 * \brief Initialise a pool and its members. 
 * \param size The number of examples the pool will contains. 
 */
Pool* InitPool(size_t size)
{
	Pool *p = malloc(sizeof(Pool));
	p->size = size;
	p->examples = malloc(sizeof(Matrix*) * size);
	//*p->examples = malloc(sizeof(Matrix) * size);
	p->results = malloc(sizeof(char) * size);
	return p;
}

/*!
 * \author pierre-olivier.rey
 * \brief Free a pool. 
 * \param p the pool to free. 
 * Free everything in the Pool p. 
 */
void FreePool(Pool*p)
{
	for(size_t i = 0; i < p->size; i++)
	{
		FreeM(*(p->examples+i));
	}
	free(p->examples);
	free(p->results);
	free(p);
}

/*!
 * \author pierre-olivier.rey
 * \brief Clear pointers of a pool. It does not delete its matrix and array. 
 * \param n the neuNet 
 * Used to clean beetween iteration of training process.
 * This way pool of matrix is not free and does not need to be re-generated.
 */
void FreePoolP(Pool*p)
{
	free(p->examples);
	free(p->results);
	free(p);
}
