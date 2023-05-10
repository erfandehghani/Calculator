#include "headers/headers.h"

int main()
{
    system("cls");
    printf("\n");

    float result;

	char inputString[MAX_CHAR_INPUT_SIZE];
	char *Seprator = "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n";

	while (1)
	{
        char outputString[MAX_CHAR_INPUT_SIZE];

        printf_s("\033[0;36mEnter something to calculate: \033[0;37m");
        getLine(inputString, MAX_CHAR_INPUT_SIZE);

		evaluateStringToPostfix( inputString, outputString);
		printf("Postfix string is: %s\n", outputString);

        result = reversePolishCalculator(outputString);
		printf("\033[0;32mResult is: %f\n \033[0;37m", result);

        printf_s("\n%s\n",Seprator);
	}
	
}