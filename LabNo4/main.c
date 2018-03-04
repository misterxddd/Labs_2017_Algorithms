#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*    for (int i = 0; i < numAdjacent; i++)
    {
        matrixCopy = adjacencyMatrix[i];
        for (int j = 0; j < 2; j++)
        {
            matrixCopy = adjacencyMatrix[i]->next;
            printf("%i ", matrixCopy->data);
            free(adjacencyMatrix[i]);
            adjacencyMatrix[i] = matrixCopy;
        }
        printf("\n");
    }
    printf("\n");*/


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

int CheckSize(FILE * file)
{
    int num = 0, size = 0;
    while(!feof(file))
    {
        if ((num = fgetc(file)) == '\n')
            size++;
    }
    fseek(file, 8, SEEK_SET);
    return size;
}

string ** GiveMemory(int size)
{
    int i = 0;
    string ** str;
    str = (string **)malloc(size * sizeof(string));
    for (i = 0; i < size; i++)
        str[i] = malloc(2 * sizeof(string));
    return str;
}

string ** CreateMatrix(FILE * file, int size)
{
    int i, j, num[1];
    string ** matrix = GiveMemory(size);

    while (!feof(file))
    {
        for (i = 0; i < size; i++)
        {
            matrix[i] = CreateStringStruct(NULL);
            for (j = 0; j < 2; j++)
            {
                fscanf(file, "%i", num);
                AddElement(matrix[i], num[0]);
            }
        }
    }
    return matrix;
}

int StackLenght(string * stack)
{
    int counter = 0;
    string * acc = stack;
    while (stack)
    {
        stack = stack->next;
        counter++;
    }
    stack = acc;
    counter--;
    return counter;
}

string * stack = NULL;

string * CleanStack(void)
{
    string * q = stack;
    while (q->next)
    {
        q = stack->next;
        free(stack);
        stack = q;
    }
    return stack;
}

int flag = 0;

void Way(int startVert,int endVert, int K, string ** matrix, int size)
{
    string * elem;
    for (int i = 0; i < size;i++)
    {
        if (flag == 1) return;
        elem = matrix[i]->next;
        if (elem->data == startVert)
        {
            int nextVert = elem->next->data;
            if (StackLenght(stack) == 0)
                stack->data = i;
            AddElement(stack, startVert);

            if (nextVert == endVert)
            {
                int lenght = StackLenght(stack);
                if (lenght >= K)
                {
                    AddElement(stack, nextVert);
                    flag = 1;
                    return;
                }
                nextVert = stack->next->data;
                stack = CleanStack();
                i = stack->data;
                matrix[i]->next->data = 0;
            }
            Way(nextVert, endVert, K, matrix, size);
        }
    }
}

void PrintStack(string * stack, FILE * file)
{
    if (StackLenght(stack) == 0)
    {
        fprintf(file, "%i ", stack->data);
        free(stack);
    }
    else
    {
        string * q = stack;
        while (q->next)
        {
            q = stack->next;
            fprintf(file, "%i ", q->data);
            free(stack);
            stack = q;
        }
        free(stack);
    }
}

int main()
{
    int V, s, t, K, numAdjacent;
    FILE * inputFile, *outputFile;
    string ** adjacencyMatrix, * matrixCopy;
    inputFile = fopen("C:/Tests/input.txt", "r");
    assert(inputFile);
    fscanf(inputFile, "%i %i %i %i", &V, &s, &t, &K);
    numAdjacent = CheckSize(inputFile);
    adjacencyMatrix = CreateMatrix(inputFile, numAdjacent);

    stack = CreateStringStruct(NULL);
    Way(s, t, K, adjacencyMatrix, numAdjacent);

    outputFile = fopen("C:/Tests/output.txt", "w");
    PrintStack(stack, outputFile);

    fclose(outputFile);
    fclose(inputFile);
    return 0;
}
