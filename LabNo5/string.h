#ifndef STRING_H
#define STRING_H

typedef struct string
{
    int data;
    struct string * next;
}string;

typedef struct element
{
    char * data;
    int i;
    int j;
    struct element * next;
}element;

string * CreateStringStruct(int _data);
void AddString(string * _str, int _data);
element * CreateElementStruct(char * _data, int _i, int _j);
void AddElement(element * _str, char * _data, int _i, int _j);

#endif
