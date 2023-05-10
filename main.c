#include "headers/headers.h"
#define MAX_CHAR_INPUT_SIZE 250

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