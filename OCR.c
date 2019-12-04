#include <stdio.h>
#include <stdlib.h>
#include "src/NeuNet/structNet.h"
#include "src/NeuNet/memory_handler.h"
#include "src/NeuNet/save_net.h"
#include "src/NeuNet/init_Network.h"
#include "src/UI/testUI.h"
#include "src/NeuNet/neuNet.h"

int main(int argc, char** argv)
{
	//int layersize[] = {28*28,20,26};
	//neuNet *network = init_network(layersize,3);

	neuNet *network = LoadNeuNet("src/NeuNet/save_data/network_save");

	if(argc > 1)
		testTrain();
	else
		exec_UI(network, argc, argv);

	freeNeuNet(network);

	return 0;
}
