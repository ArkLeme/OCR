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
#include "src/NeuNet/study_acti_fonction.h"
#include "src/NeuNet/propa_test.h"


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
    
	if(argc == 2 && *argv[1] == 't')
	{
            int layerSizes[] = {28*28,20,26};
            neuNet *network = init_network(layerSizes,3);
		printf("Beigining the training\n");
		Training(network, 10000, 2.5);
		printf("Training completed\n");

                freeNeuNet(network);
	}
	else
	{	
			
            //Write_convergence(1000, 's', "neuralNetwork_data/sigmo_convergence");
            // Write_Accuracy('s', "neuralNetwork_data/sigmo_accuracy");
          


            //Write_convergence(1000, 't', "neuralNetwork_data/tanh_convergence");
            //Write_Accuracy('t', "neuralNetwork_data/tanh_accuracy");
            
            
            Write_convergence(1000, 'r', "neuralNetwork_data/relu_convergence");
            
            Write_Accuracy('r', "neuralNetwork_data/relu_accuracy");
           

            //Matrix* m = InitM(4,2);
            //Matrix* tan =Acti(m, 't');
            //DisplayM_double(m);
            //FreeM(m);
            //FreeM(tan);
            
            /* for(int i = 0; i<4; i++)
            {
                for(int j = 0; j<2; j++)
                {     //printf("tan(%f) = %f\n", i, tan(i));
                    PutM(m,i,j,(double)((i*j)+1)/(-10));
                }
            }

            DisplayM_double(m);
            Matrix* relu = Acti(m, 'r');
            DisplayM_double(relu);
            FreeM(m);
            FreeM(relu);*/
            
	}	
	
	return 0;
}

