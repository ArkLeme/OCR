#ifndef SAVE_NET_H
#define SAVE_NET_H


void SaveNeuNet(neuNet* n, char path[]);
neuNet* LoadNeuNet(char path[]);
char *DoubleToArray(double a);

#endif
