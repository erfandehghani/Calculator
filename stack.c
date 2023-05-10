//
// Created by Erfan on 5/10/2023.
//


#include "headers/stack.h"


Data pop(Stack* stack)
{
    if (stack->top > 0)
        return stack->items[--stack->top];

    Data tmpData;
    tmpData.floatingPoint = 0.0;

    return tmpData;
}
void push(Stack* stack, Data pushItem)
{
    if(stack->top < MAX_DEPTH_OF_STACK)
        stack->items[stack->top++] = pushItem;
    else
        printf("Error: Stack is full\n");
}