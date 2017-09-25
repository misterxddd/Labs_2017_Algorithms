#ifndef ARRAY_H
#define ARRAY_H

typedef struct pop
{
	char *word;
	struct pop * next;
}string;

string * CreateStringStruct(char * _word);
void AddString(string * _str, char * _word);
int LengthString(string * _str);
void SortString(string * _str);
void PrintWords(string * _str, int _numberN);
void CheckLength(string * _str, int _checkNumber);

#endif
