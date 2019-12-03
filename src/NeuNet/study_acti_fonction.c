#include "../matrix/matrix.h"
#include "structNet.h"
#include "memory_handler.h"
#include "acti_fonction.h"
#include "training.h"
#include <err.h>
#include <stdio.h>
#include <math.h>
#include "init_Network.h"
#include "example_gen.h"
#include "f_b_Propagation.h"
#include "neuNet.h"
#include <stdlib.h>
#include "save_net.h"
#include "study_acti_fonction.h"
#include <string.h>
#include "propa_test.h"




void Write_convergence(int epoch, char acti_fct,char path[] )
{
	int layerSizes[] = {28*28,20,26};
	neuNet *network = init_network(layerSizes,3);

	Training_Write(network, epoch, 2.5, acti_fct, path);
	SaveNeuNet(network,"src/NeuNet/save_data/network_save");
        freeNeuNet(network);
}


void Training_Write(neuNet *n, int epoch, double learning_rate, char acti_fct, char path[])
{
	FILE* file;
	file = fopen(path, "w");

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
				forward_prop_actiTest(n, mat,acti_fct);
				Matrix* expected_out = CreateExpected(batches[b]->results[m]);
				backprop_batch_actiTest(n, expected_out, acti_fct);
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
		free(batches);
		printf("epoch %i : %i/%li\n", i, success, p->size);
		fprintf(file, "%i/%li\n", success,p->size);
	}
	FreePool(p);
	fclose(file);
}

void Write_Accuracy(char acti_fct, char path[])
{
	neuNet *network = LoadNeuNet("src/NeuNet/save_data/network_save");
	Predict(network, acti_fct, path);
        freeNeuNet(network);
}


void Predict(neuNet *n, char acti_fct, char path[])
{
	FILE* file;
	file = fopen(path, "w");

	GenerateExamples("neuralNetwork_data/names.data");
	Pool* p = ReadExamples("neuralNetwork_data/examples.data");
	int met[26] = {0};
	int success =0;

	for(size_t b = 0; b < p->size; b++)
	{
		if(met[p->results[b] - 'a'] == 0)
		{
			Matrix* mat = p->examples[b];
			mat->col = 1;
			mat->line = 784; //resizing matrix according to expected format
						// for neuNet input matrix

			forward_prop_actiTest(n, mat, acti_fct);
			if(GetOutput(n) == p->results[b] - 'a')
			{
				success++;
				printf("recognize : %c  [OK]", p->results[b]);
                                fprintf(file, "%c\n",p->results[b]);
			}
			else
			{
				printf("recognized : %c [K.O.]", p->results[b]);
                                fprintf(file, "!%c\n", p->results[b]);
			}
		 	met[p->results[b] - 'a'] = 1;

		}
                //ClearNeuNet(n);
        }

	FreePool(p);
	fclose(file);
        }
