#include <stdio.h>
#include <stdlib.h>

#include "string.h"

string * CreateStringStruct(int data)
{
    string * root = (string *)malloc(sizeof(string));
    root->data = data;
    root->next = NULL;
    return root;
}

void AddString(string * str, int data)
{
    string * acc = NULL;
    while (str)
    {
        acc = str;
        str = str->next;
    }
    acc->next = CreateStringStruct(data);
}

element * CreateElementStruct(char * data, int i, int j)
{
    element * root = (element *)malloc(sizeof(element));
    root->data = data;
    root->i = i;
    root->j = j;
    root->next = NULL;
    return root;
}

void AddElement(element * str, char * data, int i, int j)
{
    element * acc = NULL;
    while (str)
    {
        acc = str;
        str = str->next;
    }
    acc->next = CreateElementStruct(data, i, j);
}