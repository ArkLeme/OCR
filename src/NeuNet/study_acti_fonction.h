#ifndef CROSS_ENTROPY_H
#define CROSS_ENTROPY_H

void Write_convergence(int epoch, char acti_fct, char path[]);
void Training_Write(neuNet *n, int epoch, double learning_rate, char acti_fct, char path[]);
void Write_Accuracy(char acti_fct,char path[]);
void Predict(neuNet *n, char acti_fct, char path[]);

#endif
