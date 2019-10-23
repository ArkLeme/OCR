#include <stdio.h>
#include "../matrix/matrix.h"
#include "tools.h"
#include "structNet.h"
#include <err.h>
#include <stdlib.h>
#include <stdio.h>


int random_int(int max_value)
{
  int randomvalue = (int) rand() / ((double) RAND_MAX * max_value);
  return randomvalue;
  
 }


//Initialize biases and weights matrix with random it between 0 and 1
void  Init_biases_weights(layer* Layer)
{
  int rnd = random_int(1);
  
  for(int i = 0; i < Layer->weights->line; i++)
	{
	    PutM(Layer->biases, i, 0,rnd);

	      for(int j = 0; j < Layer -> weights->col; j++)
		{
		  rnd = random_int(1);
		  PutM(Layer->weights,i,j, rnd);
		}
	     rnd = random_int(1);
	}
	
}


void InitBW(Matrix* m1)
{
	for(int i =0; i < m1->line; i++)
	{
		for(int j = 0; j < m1->col; j++)
		{
			int rnd = random_int(1);
			PutM(m1, i,j,rnd);
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
    //Layer->outputs = InitM(nbNeurons,1);
      
      if(nbNeurons_prec)
	Layer->weights = InitM(nbNeurons,nbNeurons_prec);
      
      else Layer->weights = InitM(nbNeurons,1);
      
     // Layer->errors = InitM(nbNeurons,1);

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
	  	int k = 2;
	  	while(i<nbLayers)
	    {
	      	network->layers[i] = init_layer(layer_size[i],k);
	      	Init_biases_weights(network->layers[i]);
	      	k+=1;
			i+=1;
	    }

	    network -> nbLay = nbLayers;
	}

        return network;
	  
}		     


	/*	    layer *current_layer = network->layers[i];
	    
	    //Initialize the Matrix
	    Matrix *biases= InitM(*(layer_size + i),1);
	    Matrix *values = InitM(*(layer_size + i),1);
	    Matrix *weights =InitM(*(layer_size +i),1);
	    Matrix *outputs =InitM(*(layer_size +i),1);
	    Matrix *errors =InitM(*(layer_size +i),1);
	    Matrix *test =InitM(*(layer_size +i),1);
		
		current_layer->biases = biases;
		current_layer->values = values;
		current_layer->weights = weights;
		current_layer->outputs = outputs;
		current_layer->errors = errors;
		current_layer->nbNeurons = *(layer_size +i);
		current_layer->test = test;


	network->layers[0] = &layF;
	printf("ok init network");


	//init neuNet structure
	//layer* layers = malloc(sizeof(*layers)  + 3*sizeof(*network->layers));
	//network->layers = layer;
    i =1; //first layer doesn't have biases nor weights
    while (i<3) //TODO changes to non-hardode
    {
		//create a new layer
	//	layer *current_layer = malloc(sizeof(layer));
	//	network->layers[i] = current_layer;
		current_layer = network->layers[i];
	    //Initialize the Matrix
		Matrix *biases= InitM(*(layer_size + i),1);
	    Matrix *values = InitM(*(layer_size + i),1);
	    Matrix *weights =InitM(*(layer_size +i),*(layer_size +i-1));
	    Matrix *outputs =InitM(*(layer_size +i),1);
	    Matrix *errors =InitM(*(layer_size +i),1);

		//Add the marix to the new layer
		current_layer->biases = biases;
		current_layer->values = values;
		current_layer->weights = weights;
		current_layer->outputs = outputs;
		current_layer->errors = errors;
		current_layer->nbNeurons = *(layer_size +i);
		Init_biases_weigths(current_layer,network->layers[i-1]);
		InitBW(current_layer->weights);
		InitBW(current_layer->biases);
		i+=1;
	}

    network->nbLay = 3;
	

    //network->layers = Layers;
      }


void Main()
{
  size_t a[3] = {2,3,1};
  neuNet *Network = init_network(a);
  
  DisplayM(Network->layers[1]->outputs);

  

}*/
