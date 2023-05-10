//
// Created by Erfan on 5/10/2023.
//

#ifndef CALCULATOR_DATATYPE_H

enum{
    SIN = 's',
    COS = 'c',
    TAN = 't',
    ARCTAN = 'a',
    SQRT = 'r'
};

typedef union {
    int integer;
    char character;
    float floatingPoint;
}Data;

#define CALCULATOR_DATATYPE_H

#endif //CALCULATOR_DATATYPE_H
