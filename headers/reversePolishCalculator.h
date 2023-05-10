//
// Created by Erfan on 5/10/2023.
//

#ifndef CALCULATOR_MATH_H

#include "dataType.h"
#include "stack.h"
#include "stdio.h"
#include "math.h"
#include "ctype.h"
#include "dataType.h"
#include "string.h"
#include "functions.h"

float calculateComplexMath(float operand, char operator);
float calculateTwoOperands(float firstOperand, float secondOperand, char operator);
float reversePolishCalculator(char *inputString);

#define CALCULATOR_MATH_H

#endif //CALCULATOR_MATH_H
