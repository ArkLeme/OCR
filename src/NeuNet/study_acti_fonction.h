#ifndef CROSS_ENTROPY_H
#define CROSS_ENTROPY_H

void Write_convergence(int epoch, char acti_fct);
void Training_Write(neuNet *n, int epoch, double learning_rate, char acti_fct);
void Write_Accuracy(char acti_fct);
void Predict(neuNet *n, char acti_fct);

#endif
