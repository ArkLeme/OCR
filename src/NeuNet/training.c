#include "structNet.h"
#include "memory_handler.h"
#include "init_Network.h"
#include "example_gen.h"
#include "../matrix/matrix.h"
#include "f_b_Propagation.h"
#include "neuNet.h"
#include <stdlib.h>
#include <stdio.h>
#include "save_net.h"
#include "parcours.h"


void ShufflePool(Pool*p)
{
	for(size_t i = 0; i < p->size; i++)
	{
		size_t j = rand() % p->size;
		Matrix* tmp = p->examples[i];
		char temp = p->results[i];
		p->results[i] = p->results[j];
		p->results[j] = temp;
		p->examples[i] = p->examples[j];
		p->examples[j] = tmp;
	}
}	
int GetOutput(neuNet *n)
{
	double max = -1;
	int index = 0;
	layer*ll = n->layers[n->nbLay-1];
//	DisplayM(ll->outputs);
	for(int i  = 0; i < ll->outputs->line; i++)
	{
		if(GetM(ll->outputs, i, 0) > max)
		{
			max = GetM(ll->outputs, i, 0);
		    index = i;
		}
	}
	return index;
}
Matrix* CreateExpected(char c)
{
	Matrix* m = InitM(26, 1);
	PutM(m, c - 'a', 0, 1);
	return m;
}

Pool** CreateBatches(Pool* p, size_t batchSize)
{
	ShufflePool(p);
	size_t batchNb = p->size/batchSize +1;
	Pool** batches = malloc(sizeof(Pool*) * batchNb); 
	size_t i = 0;
	while(i < batchNb-1)
	{
		Pool*batch = InitPool(batchSize);
		for(size_t j = 0; j < batchSize; j++)
		{
			*(batch->examples + j) = *(p->examples + i*batchSize +j);
			batch->results[j] = p->results[i*batchSize +j];
		}
		*(batches +i) = batch;
		i++;
	}
	i = batchSize*(batchNb-1);
	Pool* lastBatch = InitPool(p->size - batchSize*(batchNb-1));	
	for(size_t j = 0; j < lastBatch->size; j++)
	{
		*(lastBatch->examples +j) = *(p->examples +i +j);
		lastBatch->results[j] = p->results[i+j];
	}
	
	*(batches + batchNb-1) = lastBatch;
	return batches; 
}

void testTraining(neuNet *n)
{
	List* l = Parcours("image_data/png/ocr.png");
	List* save = l;
	while(l)
	{
		printf("%c", Calculate(l->mat, n));
		l = l->next;
	}
	printf("\n");
	DeleteL(save);
}
void Training(neuNet *n, int epoch, double learning_rate)
{
	int batchSize = 10; //Arbritrary value, needs of tests
	GenerateExamples("neuralNetwork_data/names.data");
	Pool* p = ReadExamples("neuralNetwork_data/examples.data");
	
	for(int i = 0; i < epoch; i++)
	{
		int success = 0;	
		Pool** batches = CreateBatches(p, batchSize);
		for(size_t b = 0; b < p->size/batchSize +1; b++)
		{
			InitNeuNetForBatch(n);
			for(size_t m  = 0; m < batches[b]->size; m++)
			{	
				Matrix* mat = batches[b]->examples[m];
				mat->col = 1;
				mat->line = 784; //resizing matrix according to expected format
								// for neuNet input matrix
				forward_prop(n, mat);
				Matrix* expected_out = CreateExpected(batches[b]->results[m]);
				backprop_batch(n, expected_out);
				if(GetOutput(n) == batches[b]->results[m] - 'a')
					success++;
				ClearNeuNet(n);
				FreeM(expected_out);
			}
			FinalUpdate_batch(n,learning_rate, batchSize);
			FreeBatchMatrix(n);
		}
		for(size_t i = 0; i < p->size/batchSize+1; i++)
			FreePoolP(*(batches+i));
		if((i+1) % 100 == 0)
		{
			SaveNeuNet(n,"neuralNetwork_data/network_saved");
			testTraining(n);
		}
		free(batches);
		printf("epoch %i : %i/%li\n", i, success, p->size);
	}
	FreePool(p);
}

