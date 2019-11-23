#include "src/NeuNet/f_b_Propagation.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "src/NeuNet/structNet.h"
#include <time.h>
#include "src/NeuNet/init_Network.h"
#include "src/NeuNet/memory_handler.h"
#include "src/NeuNet/acti_fonction.h"
#include "src/NeuNet/save_net.h"
#include "src/NeuNet/example_gen.h"
#include "src/matrix/matrix.h"
#include "src/NeuNet/training.h"

//predict answer with a network trained
/*int calculate (neuNet* Network,Matrix *input_data)
{
	//TODO only works with XOR NN
	forward_prop(Network, input_data);
	return GetM(Network->layers[2]->outputs,0,0);	
	}*/


int GetOutput(neuNet *n)
{
	double max = -1;
	int index = 0;
	layer*ll = n->layers[n->nbLay-1];
	for(int i  = 0; i < ll->nbNeurons; i++)
	{
		if(GetM(ll->outputs, i, 1) > max)
		{
			max = GetM(ll->outputs, i, 1);
		   index = i;
		}
	}
	return index;
}
	
char Calculate(Matrix* c, neuNet * n)
{
	forward_prop(n, c);
	return (char) ('a' + GetOutput(n));
}

//train network with output_data and given output wanted
void train(neuNet *Network,int steps,float learning_rate, Matrix* input, int output_wanted)
{
	int inp[4][2] = {{0,0},{1,1},{0,1},{1,0}};
	int res[4] = {0,0,1,1};
  	for (int i =0; i<steps; i++)
  	{
		int index = i %4;
		int j = inp[index][0];
		int k = inp[index][1];
		
		Matrix* input = InitM(2,1);
		PutM(input, 0,0,j);
		PutM(input,1,0,k);
		Matrix* out = InitM(1,1);
		PutM(out, 0,0,res[index]);
		forward_prop(Network, input);
		printf("%d xor %d = %f\t%d\n", j, k, GetM(Network->layers[2]->outputs,0,0), i);
		backprop(Network, 1, out, learning_rate);
		ClearNeuNet(Network);
		FreeM(out);
		FreeM(input);
    }
    

	

	
}

int main(int argc, char** argv)
{
      int layerSizes[] = {28*28,20,26};
	neuNet *network = init_network(layerSizes,3); 
	if(argc == 2 && *argv[1] == 't')
	{
		Training(network, 5, 0.01);
		printf("Training completed");
	}
	else
	{	
		Matrix *input = InitM(2,1);
		int layerSizes[] = {2,3,1};
		neuNet *network = init_network(layerSizes,3); 
		train(network,2, 1.5, input, ' ' );
		
		

		freeNeuNet(network);
		FreeM(input);

	
	}	
	freeNeuNet(network);

	

	
	
	return 0;
}

