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
	    
	    fprintf(file,"%u \n",n->nbLay);
	    for(int i = 0; i < n->nbLay;i++)
	      {
		fprintf(file,"%u \n",n->layers[i]->nbNeurons);
	      }
	   
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
	    
		fprintf(file,"$\n");
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
	file = fopen("network", "r");
	if (file == NULL)
	  {
	    printf("File does not exists");
	    return NULL;
	  }

	char line[100];
           
	//fscanf(file,"%s",line);
	//printf("%s",line);
	size_t nb_lay= 0;	
        	       
    
	/* for(size_t i =0; i<nb_lay;i++)
	 {
	      scanf("%[,]",line);
	      sizeLay[i] = atoi(line);
	      nb_lay+=1;	      
	    
	      }*/

	 fscanf(file, "%s", line);
	 //nb_lay = (size_t)atoi(line);
	 fscanf(file, "%s", line);

	 int sizeLay[nb_lay];
	  
	 char chaine[5] = "";
	 
   
    
    for (size_t i = 1; line[i] != '}';i++)
    {
        if (line[i] == ',')
	  {
	    sizeLay[nb_lay] = atof(chaine);
	    nb_lay +=1;
	    char chaine[5] = "";
	  }
        else
	  {
	    char fu[1];
	    fu[0] = line[i];
	    strcat(chaine,fu);
          }
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
		value = atof(line);
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

