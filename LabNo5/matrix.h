#ifndef MATRIX_H
#define MATRIX_H

#include "string.h"
#include "string.h"

typedef struct mat
{
    char * data;
    struct mat * next;

}matrixElem;

matrixElem * CreateMatStruct(char * _data);
void AddMat(matrixElem * _str, char * _data);

matrixElem ** GiveMemory(int _n, int _m);
matrixElem ** CreateMatrix(element * _elem,int _n, int _m);
void PrintMatrix(matrixElem ** _matrix, int _n, int _m);

#endif 

