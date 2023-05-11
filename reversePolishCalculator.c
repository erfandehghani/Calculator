#include "headers/reversePolishCalculator.h"

float calculateComplexMath(float operand, char operator)
{
    switch (operator) {
        case 's':
            return sinf(operand);
        case 'c':
            return cosf(operand);
        case 't':
            return tanf(operand);
        case 'a':
            return atanf(operand);
        case 'r':
            return sqrtf(operand);
        default:
            printf("Error: function is not defined.");
            return 0;
    }
}
float calculateTwoOperands(float firstOperand, float secondOperand, char operator)
{
    switch (operator)
    {
        case '+':
            return firstOperand + secondOperand;
        case '-':
            return firstOperand - secondOperand;
        case '*':
            return firstOperand * secondOperand;
        case '/':
            if (secondOperand != 0)
                return firstOperand / secondOperand;
            else
            {
                printf("Error: Division by zero.\n");
                return 0;
            }
        case '^':
            return powf(firstOperand,secondOperand);
        default:
            printf("Error: Unknown operator.\n");
            return 0;
    }
}
float reversePolishCalculator(char *inputString)
{
    float sign, firstFloat, secondFloat, result;

    Stack numberStack;
    numberStack.top = 0;

    Data tmp;
    tmp.floatingPoint = 0.0;

    while (*inputString)
    {
        while(*inputString == ' ')
            inputString++;

        if (isdigit(*inputString) || (*inputString == '-' && isdigit(*(inputString + 1))))
        {
            sign = (*inputString == '-' && isdigit(*(inputString + 1))) ? -1.0 : 1.0;

            if(sign == -1.0)
                inputString++;

            tmp.floatingPoint = sign * (float)atof(inputString);

            push(&numberStack, tmp);

            while (isdigit(*inputString))
                inputString++;

            if(*inputString == '.')
                inputString++;

            while (isdigit(*inputString))
                inputString++;

        }

        if(isOperator(*inputString))
        {
            secondFloat = pop(&numberStack).floatingPoint;
            firstFloat = pop(&numberStack).floatingPoint;
            result = calculateTwoOperands(firstFloat, secondFloat, *inputString);

            tmp.floatingPoint = result;
            push(&numberStack, tmp);
        }

        if (isComplexMath(*inputString))
        {
            firstFloat = pop(&numberStack).floatingPoint;
            result = calculateComplexMath(firstFloat, *inputString);

            tmp.floatingPoint = result;
            push(&numberStack, tmp);
        }

        if(*inputString == '\0')
            break;

        inputString++;
    }

    return pop(&numberStack).floatingPoint;
}