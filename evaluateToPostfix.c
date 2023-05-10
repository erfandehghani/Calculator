//
// Created by Erfan on 5/10/2023.
//
#include "headers/evaluateToPostfix.h"

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