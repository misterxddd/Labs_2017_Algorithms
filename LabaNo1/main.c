#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>

#include "array.h"
int main()
{
	int N = 0;
	int K = 0;
	char buf[20];
	char *w;
	string * root, * q;
	root = CreateStringStruct(NULL);
	FILE * file, * fileTest;
	file = fopen("C:/Tests/Words_Tests.txt", "r");

	while (!feof(file))
	{
		fscanf(file, "%s", buf);
		w = (char*)malloc(strlen(buf) + 1);
		strcpy(w, buf);
		AddString(root, w);
	}

	fclose(file);
	root = root->next;

	SortString(root);

	fileTest = fopen("C:/Tests/Lenght.txt", "r");
	fscanf(fileTest, "%i", &N);
	fclose(fileTest);

	PrintWords(root, N);

	scanf("%i", &K);
	CheckLength(root, K);

	q = root;
	while (q)
	{
		q = root->next;
		free(root);
		root = q;
	}
	free(root);

	_getch();
	return 0;
}
