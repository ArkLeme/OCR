#include "src/XOR/f_b_Propagation.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "src/XOR/structNet.h"
#include <time.h>
#include "src/XOR/init_Network.h"
#include "src/XOR/tools.h"
#include "src/matrix/matrix.h"

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
    }
}

int main()
{
    /*int layerSizes[] = {28*28,20,26};
	neuNet *network = init_network(layerSizes,3); 
	train(network,55000, 1.5);
	freeNeuNet(network);*/	
	Matrix* input = InitM(2,1);
	PutM(input, 0,0,1);
	PutM(input,1,0,1);
        softmax(input);
	DisplayM(input);
	return 0;
}

