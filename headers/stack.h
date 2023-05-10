//
// Created by Erfan on 5/10/2023.
//

#ifndef CALCULATOR_STACK_H

#define MAX_DEPTH_OF_STACK 100

#include "stdio.h"
#include "dataType.h"

typedef struct Stack
{
    Data items[MAX_DEPTH_OF_STACK];
    int top;
} Stack;

Data pop(Stack* stack);
void push(Stack* stack, Data pushItem);

#define CALCULATOR_STACK_H

#endif //CALCULATOR_STACK_H
