#include <stdio.h>
#include "../matrix/matrix.h"

#include "structNet.h"
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

double randFloat()
{	
	//random float between -1 and 1
	double sign = rand() %2;
	double rdm = (double) rand()/((double)(RAND_MAX)/2+ 1.0);
	if(sign ==1)
		rdm *= -1;
	return rdm;
}


int random_int(int max_value)
{
  	int randomvalue = (int) rand() / ((double) RAND_MAX * max_value);
  	return randomvalue;
  
 }


//Initialize biases and weights matrix with random it between 0 and 1
void  Init_biases_weights(layer* Layer)
{
	srand((unsigned) time(NULL));

    	double rnd;
  
    	for(int i = 0; i < Layer->weights->line; i++)
	{
		rnd = randFloat();
		PutM(Layer->biases, i, 0,rnd);
	    	for(int j = 0; j < Layer->weights->col; j++)
		{
		    	//rnd = random_int(1);
		  	rnd = randFloat();
		  	PutM(Layer->weights,i,j, rnd);
		}
	}

	
}


layer *init_layer(int nbNeurons, int nbNeurons_prec)
{
  	layer *Layer = malloc(sizeof(layer));

  	if(Layer)
    	{
		//Layer->values = InitM(nbNeurons,1);
		Layer->biases = InitM(nbNeurons,1);
	//	Layer->biases_batch = InitM(nbNeurons,1);
    		//Layer->outputs = InitM(nbNeurons,1);
      
      		if(nbNeurons_prec)
		{
			Layer->weights = InitM(nbNeurons,nbNeurons_prec);
		//	Layer->weight_batch = InitM(nbNeurons,nbNeurons_prec);
		}	
      
     		else 
		{
			Layer->weights = InitM(nbNeurons,1);    
     			// Layer->errors = InitM(nbNeurons,1);
      			
		}

		Layer->nbNeurons = nbNeurons;
	}
    
  	return Layer;
}




//take the nbLayer wanted and the size of each layer_size
neuNet* init_network(int layer_size[], size_t nbLayers)
{

    neuNet *network = malloc(sizeof(neuNet));

	size_t i = 0;
        
	if(network)
    {
	    
	  	//init first layer with no weights biases
	  	network->layers[0] = init_layer(layer_size[i],0);
	  	i+=1;
	  	//int k = 2;
	  	while(i<nbLayers)
	    {
	      	network->layers[i] = init_layer(layer_size[i],layer_size[i-1]);
	      	Init_biases_weights(network->layers[i]);
	      	//k+=1;
		i+=1;
	    }

	    network -> nbLay = nbLayers;
	}

	return network;
	  
}		     

void InitNeuNetForBatch(neuNet*n)
{
	for(int i = 1; i < n->nbLay; i++)
	{
		layer *cl = n->layers[i];
		cl->weight_batch = InitM(cl-> nbNeurons, n->layers[i-1]->nbNeurons);
		cl->biases_batch = InitM(cl->nbNeurons, 1);
	}
}
