#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "array.h"


string * CreateStringStruct(char * word)
{
	string * root = (string *)malloc(sizeof(string));
	root->word = word;
	root->next = NULL;
	return root;
}

void AddString(string * str, char * word)
{
	string * acc = NULL;
	while (str)
	{
		acc = str;
		str = str->next;
	}
	acc->next = CreateStringStruct(word);
}

int LengthString(string * str)
{
	int counter = 0;
	while (str)
	{
		str = str->next;
		counter++;
	}
	return counter;
}


void SortString(string * str)
{
	string * acc = NULL;

	if (str != NULL)
	{
		while (str->next != NULL) 
		{
			acc = str->next;

			do {
				if (strlen(acc->word) < strlen(str->word))
				{
					char * Copy = acc->word;
					acc->word = str->word;
					str->word = Copy;
				}
				else if (strlen(acc->word) == strlen(str->word))
				{
					int i = 0;
					while (acc->word[i] == str->word[i] || (acc->word[i] + 0x020) == str->word[i] || acc->word[i] == (str->word[i] + 0x020))
						i++;
					if (acc->word[i] < str->word[i])
					{
						char * Copy = acc->word;
						acc->word = str->word;
						str->word = Copy;
					}
				}
				acc = acc->next;
			} while (acc != NULL);

			str = str->next;
		}
	}
}

void PrintWords(string * str, int numberN)
{
	int i = 0;
	int length = LengthString(str);
	for (i = 0; i < length; i++)
	{
		if ((int )strlen(str->word) > numberN)
		{
			printf("%s ", str->word);
		}
		str = str->next;
	}
	printf("\n");
}

void CheckLength(string * str, int checkNumber)
{
	int i = 0;
	int counter = 0;
	int length = LengthString(str);
	for (i = 0; i < length; i++)
	{
		if ((int)strlen(str->word) == checkNumber)
		{
			printf("%s ", str->word);
			counter++;
		}
		str = str->next;
	}
	if (counter == 0) printf("No words");
}
