#include "f_b_Propagation.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "structNet.h"
#include <time.h>
#include "init_Network.h"
#include "memory_handler.h"
#include "acti_fonction.h"
#include "save_net.h"
#include "example_gen.h"
#include "../matrix/matrix.h"
#include "training.h"

#include "parcours.h"
#include "study_acti_fonction.h"
#include "propa_test.h"


	
char Calculate(Matrix* c, neuNet * n)
{
	c->col = 1;
	c->line = 784;
	forward_prop(n, c);
	int result = GetOutput(n);
	ClearNeuNet(n);
	return (char) ('a' + result);
}

void testTrain()
{
    
	if(1)
	{
            int layerSizes[] = {28*28,20,26};
            neuNet *network = init_network(layerSizes,3);
			printf("Beigining the training\n");
		Training(network, 100000000, 2.5);
		printf("Training completed\n");

                freeNeuNet(network);
	}
	else
	{	
	/*		
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
            
             for(int i = 0; i<4; i++)
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
            FreeM(relu);
     */       
	}	
}
