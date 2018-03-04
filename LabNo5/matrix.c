#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

matrixElem * CreateMatStruct(char * data)
{
    matrixElem * root = (matrixElem *)malloc(sizeof(matrixElem));
    root->data = data;
    root->next = NULL;
    return root;
}

void AddMat(matrixElem * str, char * data)
{
    matrixElem * acc = NULL;
    while (str)
    {
        acc = str;
        str = str->next;
    }
    acc->next = CreateMatStruct(data);
}

matrixElem ** GiveMemory(int n, int m)
{
    int i = 0;
    matrixElem ** str;
    str = (matrixElem **)malloc(n * sizeof(matrixElem));
    for (i = 0; i < n; i++)
        str[i] = malloc(m * sizeof(matrixElem));
    return str;
}

matrixElem ** CreateMatrix(element * elem, int n, int m)
{
    int i, j, number = 0, hCur, colCur, flag = 0, counter = 0;
    matrixElem ** matrix = GiveMemory(n, m);
    element * acc = elem->next;

    for (i = 0; i < n; i++)
    {
        matrix[i] = CreateMatStruct(0);
        for (j = 0; j < m; j++)
        {
            while (acc)
            {
                hCur = acc->i;
                colCur = acc->j;
                if (((hCur-1) == i) && ((colCur-1) == j))
                {
                    AddMat(matrix[i], acc->data);
                    flag = 1;
                }
                acc = acc->next;
            }
            if(flag == 0)
                AddMat(matrix[i], NULL);
            acc = elem->next;
            flag = 0;
            counter++;
        }
    }
    return matrix;
}

void PrintMatrix(matrixElem ** matrix, int n, int m)
{
    int i, j;
    matrixElem * matrixCopy;
    for (i = 0; i < n; i++)
    {
        matrixCopy = matrix[i];
        for (j = 0; j < m; j++)
        {
            matrixCopy = matrix[i]->next;
            if (matrixCopy->data != NULL)
                printf("%s ", matrixCopy->data);
            else
                printf("  ");
            free(matrix[i]);
            matrix[i] = matrixCopy;
        }
        printf("\n");
    }
    printf("\n");
}