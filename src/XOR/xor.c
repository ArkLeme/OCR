#include "f_b_Propagation.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "structNet.h"
#include <time.h>
#include "init_Network.h"
#include "tools.h"
#include "../matrix/matrix.h"

void train(neuNet *Network,int steps,float learning_rate);

/*
int main()
{
    int layerSizes[] = {2,2,1};
	neuNet *network = init_network(layerSizes,3); 
	train(network,500, 0.1); 
	freeNeuNet(network);
	return 0;
}
*/

//predict answer with a network trained
/*int calculate (neuNet* Network,Matrix *input_data)
{
	//TODO only works with XOR NN
	forward_prop(Network, input_data);
	return GetM(Network->layers[2]->outputs,0,0);	
	}*/


//train network with output_data and given output wanted
void train(neuNet *Network,int steps,float learning_rate)
{
	int inp[4][2] = {{0,0},{1,1},{0,1},{1,0}};

	srand((unsigned) time(0));
  	for (int i =0; i<steps; i++)
  	{
		int index = i %4;
		int j = inp[index][0];
		int k = inp[index][1];
		Matrix* input = InitM(2,1);
		PutM(input, 0,0,j);
		PutM(input,1,0,k);
		Matrix* out = InitM(1,1);
		PutM(out, 0,0,k=!j);	
		forward_prop(Network, input);
		//printf("%i xor %i",j,k);
		//printf("%i ^ %i = %f/%i\t%i\n", j,k, GetM(Network->layers[2]->outputs, 0,0),k!=j, i);
		printf("%f\n\n", GetM(Network->layers[2]->outputs,0,0));
		backprop(Network, 1, out, learning_rate);
		ClearNeuNet(Network);
		FreeM(out);
    }
}
