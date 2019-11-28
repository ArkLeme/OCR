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

#include "src/NeuNet/parcours.h"
#include "src/NeuNet/cross_entropy.h"
//predict answer with a network trained
/*int calculate (neuNet* Network,Matrix *input_data)
{
	//TODO only works with XOR NN
	forward_prop(Network, input_data);
	return GetM(Network->layers[2]->outputs,0,0);	
	}*/



	
char Calculate(Matrix* c, neuNet * n)
{
	c->col = 1;
	c->line = 784;
	forward_prop(n, c);
	int result = GetOutput(n);
	ClearNeuNet(n);
	return (char) ('a' + result);
}

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
	//backprop(Network, 1, out, learning_rate);
		backprop_batch(Network,out);
		ClearNeuNet(Network);
		FreeM(out);
		//FreeM(input);
    }

		FinalUpdate_batch(Network,learning_rate, steps);	

	
}

int main(int argc, char** argv)
{
    int layerSizes[] = {28*28,20,26};
	neuNet *network = init_network(layerSizes,3); 
	if(argc == 2 && *argv[1] == 't')
	{
		printf("Beigining the training\n");
		Training(network, 10000, 2.5);
		printf("Training completed\n");
	}
	else
	{	
			/*FILE *file;
			file = fopen("test","wb");
			if(file != NULL)		
			{ short int a[2] = {1,2};
			fwrite ( a, sizeof(short int), 2, file); }
			else
			{printf("file == NULL");}
			fclose(file);

			FILE *file2;
			file2 = fopen("test","rb");
			if(file != NULL)		
			{ int nb_val =2;
			  int Taille_buf = 2;
			  short int buf[2];
				while(nb_val == Taille_buf)
				{
					nb_val = fread ( buf, sizeof(short int), 2, file2); 
					for(int i =0; i<nb_val; i++) {printf("%hd \n", buf[i]);}
					
				}
			fclose(file2);*/


		Training(network, 2, 2.5);
		SaveNeuNet(network);

		neuNet *network_load;
		network_load = LoadNeuNet();

		//freeNeuNet(network_load);
		
	}	
	freeNeuNet(network);
	
	return 0;
}

