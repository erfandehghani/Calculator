//
// Created by Erfan on 5/10/2023.
//

#ifndef CALCULATOR_ISFUNC_H

#include "dataType.h"
#include "stdio.h"

#define MAX_CHAR_INPUT_SIZE 250

int operatorValue(char character);
int isEntity(char character);
int isOperator(char character);
int isComplexMath(char character);
int getLine(char* s, int lim);

#define CALCULATOR_ISFUNC_H

#endif //CALCULATOR_ISFUNC_H
