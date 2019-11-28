#include "../matrix/matrix.h"
#include "structNet.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "save_net.h"
#include "init_Network.h"
#include <string.h>



/*!
 * \author jeanne.morin
 * \Save the network in a binary file
 * \param network is the current network, needed to be saved.
 */

void SaveNeuNet(neuNet *n)
{
  
	FILE *file;
	file = fopen("network_save", "w");
	if(file == NULL)
	  {
	    printf("Erreur : SaveNeuNet : No stream opened");
	  }

	else
	  {
	    
	    //fprintf(file,"%u \n",n->nbLay);
	    for(int i = 0; i < n->nbLay;i++)
	      {
		fprintf(file,"%u \n",n->layers[i]->nbNeurons);
	      }
	    fprintf(file, "}\n");
	   
	    double value;
	
	    for(int i = 1; i < n->nbLay; i++)
	      {
		layer *current_layer = n->layers[i];
	    	    
		for (int j = 0; j < current_layer->nbNeurons; j++)
		  {
		    for(int k = 0; k <current_layer->weights->col ;k++)
		      {
			value = GetM(current_layer->weights,j,k);
			fprintf(file,"%f\n",value);
		      }

		    value = GetM(current_layer->biases,j,0);
		    fprintf(file,"%f\n", value);
		  }
	    
		}
	
	    fclose(file);
	  }
}

/*!
 * \author jeanne.morin
 * \brief Load the network from the save file, written in binary.
 * \return the network loaded.
 */

neuNet *LoadNeuNet()
{
	
        FILE *file;
	file = fopen("network_save", "r");
	if (file == NULL)
	  {
	    printf("File does not exists");
	    return NULL;
	  }

	char line[100];
	char chaine[5] = "";
	size_t nb_lay= 0;	
        	       
    
	/* for(size_t i =0; i<nb_lay;i++)
	 {
	      
	      sizeLay[i] = atoi(line);
	      nb_lay+=1;	      
	    
          }*/

	 
	 int sizeLay[nb_lay];
	  
	 //char chaine[5] = "";
	 fscanf(file, "%s\n", chaine);
    
	  while(chaine[0] != '}')
	   {
	         printf("%s\n", chaine);
	         sizeLay[nb_lay] = atof(chaine);
		 nb_lay +=1;
		 fscanf(file, "%s\n", chaine);
		
	    }
       
	  double value;
	  neuNet  *net = init_network(sizeLay,nb_lay);
	  
	  //Load for each Layer except the first, the weights and biases matrices
	  for(int i=1; i<net->nbLay; i++)
	    {
	      layer *cL= net->layers[i];
	      for(int j =0; j<cL->weights->line;j++)
		{
		  //Get every component of the matrix weights
		  for(int k=0; k<cL->weights->col;k++)
		    {
		      fscanf(file,"%s",line);
		      printf("%s  ->",line);
		      value = atof(line);
		      printf("%f\n",value);
		      PutM(cL->weights,j,k,value);
		    }
		  
		  //Get biases
		  fscanf(file,"%s",line);
		  value = atof(line);
		  PutM(cL->biases,j,0,value);
		}
	
	     }
    
    fclose(file);
    return net;


		
}

