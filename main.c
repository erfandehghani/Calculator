#include <stdio.h>
#include <ctype.h>
#include "string.h"
#include "math.h"

#define MAX_DEPTH_OF_STACK 100
#define MAX_CHAR_INPUT_SIZE 250
enum{
    SIN = 's',
    COS = 'c',
    TAN = 't',
    ARCTAN = 'a',
    SQRT = 'r'
};

//Stack related functions
typedef union {
	int integer;
	char character;
	float floatingPoint;
}Data;
typedef struct Stack
{
	Data items[MAX_DEPTH_OF_STACK];
	int top;
} Stack;
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
//End of stack related functions

int isEntity(char character)
{
	return (character == '+' || character == '-' || character == '*' || character == '/' || character == ']' || character == ')') ? 1 : 0;
}
int isOperator(char character)
{
	return (character == '+' || character == '-' || character == '*' || character == '/') ? 1 : 0;
}
int isComplexMath(char character)
{
    return (character == 's' || character == 'c' || character == 't' || character == 'a' || character == 'r') ? 1 : 0;
}
int operatorValue(char character)
{
    switch (character) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case SIN:
        case COS:
        case TAN:
        case ARCTAN:
        case SQRT:
            return 3;
        case ')':
        case ']':
            return 4;
        default:
            return 0;
    }
}

void evaluateStringToPostfix(char* inputString, char* outputString)
{
	Data operator;
	Data tmpChar;
    char word[6];

    Stack operatorStack;
    operatorStack.top = 0;

	while (*inputString)
	{

        while(*inputString == ' ')
            inputString++;

        //Handling digits
        if (isdigit(*inputString) || (*inputString == '-' && *(inputString - 1) == ' ' && isdigit(*(inputString + 1))))
        {
            float sign;
            float numb;
            char tmpString[20];

            sign = (*inputString == '-' && *(inputString - 1) == ' ' && isdigit(*(inputString + 1))) ? -1.0 : 1.0;

            if(sign == -1.0)
                inputString++;

            numb = sign * (float)atof(inputString);

            sprintf(tmpString, "%f", numb);

            for (int i = 0; tmpString[i] != '\0'; ++i)
                *outputString++ = tmpString[i];

            while (isdigit(*inputString))
                inputString++;

            if(*inputString == '.')
                inputString++;

            while (isdigit(*inputString))
                inputString++;

            *outputString++ = ' ';
        }

        //Handling words
        if (isalpha(*inputString))
        {
            int wordCharactersCount = 0;
            while (isalpha(*inputString))
            {
                wordCharactersCount++;
                inputString++;
            }

            inputString = inputString - wordCharactersCount;

            if(wordCharactersCount > 2)
            {

                int i;

                for (i = 0; i < wordCharactersCount; ++i)
                    word[i] = *(inputString+i);

                word[i] = '\0';

                if (strcmp(word, "sin") == 0)
                {
                    tmpChar.character = SIN;
                    push(&operatorStack, tmpChar);
                }

                if (strcmp(word, "cos") == 0)
                {
                    tmpChar.character = COS;
                    push(&operatorStack, tmpChar);
                }

                if (strcmp(word, "tan") == 0)
                {
                    tmpChar.character = TAN;
                    push(&operatorStack, tmpChar);
                }

                if (strcmp(word, "sqrt") == 0)
                {
                    tmpChar.character = SQRT;
                    push(&operatorStack, tmpChar);
                }

                if (strcmp(word, "arctan") == 0)
                {
                    tmpChar.character = ARCTAN;
                    push(&operatorStack, tmpChar);
                }
                inputString = inputString + wordCharactersCount;

            }

        }

        //Handling Entities
        if (isEntity(*inputString))
        {
            if((tmpChar = pop(&operatorStack)).character != 0)
            {
                push(&operatorStack, tmpChar);

                if (operatorValue(*inputString) <= operatorValue(tmpChar.character))
                    while((operator = pop(&operatorStack)).character != 0 && operator.character != '(' && operator.character != '[')
                    {
                        *outputString++ = operator.character;
                        *outputString++ = ' ';
                    }
            }
            if (isOperator(*inputString) && *(inputString + 1) != '\0')
            {
                tmpChar.character = *inputString;
                push(&operatorStack, tmpChar);
            }
        }

        else
            switch (*inputString)
            {
                case '\0':
                case ' ':
                    break;
                case '(':
                case '[':
                    tmpChar.character = *inputString;
                    push(&operatorStack, tmpChar);
                    break;
                default:
                    printf("Unknown Character: %d\n", *inputString);
                    break;
            }

        if(*inputString == '\0')
            break;

        inputString++;
	}

    if (*inputString == '\0')
        while((operator = pop(&operatorStack)).character != 0)
            if (operator.character != '(' && operator.character != '[')
            {
                *outputString++ = operator.character;
                *outputString++ = ' ';
            }


    *outputString = '\0';
}

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
    tmp.integer = 0;
    tmp.floatingPoint = 0.0;
    tmp.character = 0;

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

//Getting input
int getLine(char* s, int lim) {
    int c, i;
    for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    s[i] = '\0';
    return i - 1;
}

int main()
{
    float result;

	char inputString[MAX_CHAR_INPUT_SIZE];

	while (getLine(inputString, MAX_CHAR_INPUT_SIZE))
	{
        char outputString[MAX_CHAR_INPUT_SIZE];
		evaluateStringToPostfix( inputString, outputString);
		printf("Postfix string is: %s\n", outputString);
        result = reversePolishCalculator(outputString);
		printf("Result is: %f\n", result);
	}
	
}