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
	file = fopen("network_save", "wb");

	if(file != NULL)
	{
		/*for(int i = 0;i < n->nbLay; i++)
		{
			fputc(n->layers[i]->nbNeurons,file);//ne fonctionne pas car un nombre != 
			//un character
			//pense à Itoa(int to string) qu'a fait william et la fonctin fprintf("%s\n", itoa); 
			fputc(' ', file);
		}
		fputc('\n',file);*/
			
		//for(int i = 1;i < n->nbLay; i++) //premier layer n'a rien a save (pas de poids biais sur le premier)
		{
			layer *cL = n->layers[1];
			printf("%i", cL->biases->size);
			double a[2] = {1.00,2.13};
			Matrix *test = InitM(2,2);
			
		
			//fwrite ( &test, sizeof(double), test->size, file);
			for(int l=0; l<cL->biases->size;l++)
			{
				for(int c= 0; c<cL->biases->col; c++)
				{
					double value = GetM(cL->biases,l,c);
					char value_to_char[sizeof(value)] = {0};
					sprintf(value_to_char,"%.21f",value);
					fwrite ( value_to_char, sizeof(char), sizeof(value), file);
				}
			}		

						

			fputc('\n', file);

			
			DisplayM(cL->weights);
			FreeM(test);
			//fwrite(cL->weights, sizeof(double), cL->weights->size, file);//idem
			//fputc('\n', file);}
				
			
		
		
	}
}
	else
	{ printf("Pas de fichier où écrire !");
}

	
	fclose(file);
}

/*!
 * \author jeanne.morin
 * \Load the network from the save file, written in binary.
 */

neuNet *LoadNeuNet()
{
	
	FILE *file;
	file = fopen("network", "w");
	if(file == NULL)
	{
		//errx("File can't be created");
		printf("rien à loader");
		
	}
	else
	{
		int layers_nbNeurons[3];
		int NbLay =0;
		int r = fgetc(file);
		
		

		while(r)		
		{
			layers_nbNeurons[NbLay] = r; //a changer avec double while ou autre fonction de lecture genre fgets
			fgetc(file);
			r = fgetc(file);
			NbLay+=1;
		}
		
		neuNet *network = init_network(layers_nbNeurons, NbLay);
		
		
		for(int i = 0;i < network->nbLay; i++) //du coup peut etre commencer à  si tu save pas le 1er layer
		{
			layer *cL = network->layers[i];

			fread(cL->biases, sizeof(double), cL->biases->size, file);
			fgetc(file);
			fread(cL->weights, sizeof(double), cL->weights->size, file);
			fgetc(file); // ce for c'est grave clean		
		
		}


return network;

	 	
	}


		
}

