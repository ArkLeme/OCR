#include "src/XOR/f_b_Propagation.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "src/XOR/structNet.h"
#include <time.h>
#include "src/XOR/init_Network.h"
#include "src/XOR/memory_handler.h"
#include "src/XOR/acti_fonction.h"
#include "src/XOR/save_net.h"
#include "src/XOR/example_gen.h"
#include "src/matrix/matrix.h"
#include "src/XOR/training.h"

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
		int layerSizes[] = {28*28,15,26};
		neuNet *network = init_network(layerSizes,3); 
		train(network,55000, 1.5);

		freeNeuNet(network);

	
	}	
	freeNeuNet(network);


	return 0;
}

