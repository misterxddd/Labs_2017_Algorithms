#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct string
{
	int data;
	struct string * next;
}string;

string * CreateStringStruct(int * data)
{
	string * root = (string *)malloc(sizeof(string));
	root->data = data;
	root->next = NULL;
	return root;
}

void AddElement(string * str, int * data)
{
	string * acc = NULL;
	while (str)
	{
		acc = str;
		str = str->next;
	}
	acc->next = CreateStringStruct(data);
}

char pop(string * str)
{
	string * acc = NULL;
	string * strCopy = str;
	while (str->next)
	{
		acc = str;
		str = str->next;
	}
	char value = str->data;
	free(str);
	acc->next = NULL;
	str = strCopy;
	return value;
}

int CheckSize(FILE * file)
{
	int num = 0, size = 0;
	while ((num = fgetc(file)) != '\n') {
		if (num != ' ')
			size++;
	}
	fseek(file, 0, SEEK_SET);
	return size;
}

string ** GiveMemory(int size)
{
	int i = 0;
	string ** str;
	str = (string **)malloc(size * sizeof(string));
	for (i = 0; i < size; i++)
		str[i] = malloc(size * sizeof(string));
	return str;
}

string ** CreateMatrix(string * stack, int size)
{
	int i, j, number = 0;
	string ** matrix = GiveMemory(size);

	for (i = 0; i < size; i++)
	{
		matrix[i] = CreateStringStruct(NULL);
		for (j = 0; j < size; j++)
		{
			if (i == j)
			{
				number = pop(stack);
				AddElement(matrix[i], number);
			}
			else if (i == 0 && j == 2)
			{
				number = pop(stack);
				AddElement(matrix[i], number);
			}
			else
				AddElement(matrix[i], 0);
		}
	}
	return matrix;
}

void FixMatrix(string ** matrix, string * stack, int size)
{
	int i, j, number = 0;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (i == 2 && j == 0)
			{
				if ((matrix[i]->next)->data != 0)
					i++;
				number = pop(stack);
				(matrix[i]->next)->data = number;
				return;
			}
		}
	}
}

void PrintMatrix(string ** matrix, int size, FILE * file)
{
	int i, j;
	string * matrixCopy;
	for (i = 0; i < size; i++)
	{
		matrixCopy = matrix[i];
		for (j = 0; j < size; j++)
		{
			matrixCopy = matrix[i]->next;
			fprintf(file, "%i ", matrixCopy->data);
			free(matrix[i]);
			matrix[i] = matrixCopy;
		}
		fprintf(file, "\n");
	}
	fprintf(file, "\n");
}


int main()
{
	int i = 0, j = 0, sizeMatrix = 0, num[1], stackSize = 0, sizeLittleMatrix = 0;
	string ** matrixMain, ** matrix1, ** matrix2, ** matrix3, ** matrix4;
	FILE * inputFile, * outputFile;
	inputFile = fopen("C:/Tests/Test.txt", "r");
	assert(inputFile);

	sizeMatrix = CheckSize(inputFile); 

	matrixMain = GiveMemory(sizeMatrix);

	sizeLittleMatrix = sizeMatrix / 2;

	string * stack = CreateStringStruct(NULL);

	while (!feof(inputFile))
	{
		for (i = 0; i < sizeMatrix; i++)
		{
			matrixMain[i] = CreateStringStruct(NULL);
			for (j = 0; j < sizeMatrix; j++)
			{
				fscanf(inputFile, "%i", num);
				AddElement(matrixMain[i], num[0]);
				if (num[0] != 0)
				{
					AddElement(stack, num[0]);
					stackSize++;
				}
			}
		}
	}

	fclose(inputFile);

	matrix1 = CreateMatrix(stack, sizeLittleMatrix);
	matrix2 = CreateMatrix(stack, sizeLittleMatrix);
	matrix3 = CreateMatrix(stack, sizeLittleMatrix);
	matrix4 = CreateMatrix(stack, sizeLittleMatrix);

	while (stack->next != NULL)
	{
		FixMatrix(matrix1, stack, sizeLittleMatrix);
		if (stack->next == NULL) break;
		FixMatrix(matrix2, stack, sizeLittleMatrix);
		if (stack->next == NULL) break;
		FixMatrix(matrix3, stack, sizeLittleMatrix);
		if (stack->next == NULL) break;
		FixMatrix(matrix4, stack, sizeLittleMatrix);
		if (stack->next == NULL) break;
	}

	free(stack);

	outputFile = fopen("C:/Tests/Test_Out.txt", "w");

	PrintMatrix(matrixMain, sizeMatrix, outputFile);
	PrintMatrix(matrix1, sizeLittleMatrix, outputFile);
	PrintMatrix(matrix2, sizeLittleMatrix, outputFile);
	PrintMatrix(matrix3, sizeLittleMatrix, outputFile);
	PrintMatrix(matrix4, sizeLittleMatrix, outputFile);

	fclose(outputFile);


	return 0;
}
