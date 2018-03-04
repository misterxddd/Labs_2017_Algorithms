#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "string.h"
#include "matrix.h"

string * dep;
element * mas;

tree * CreateTreeNode(char * data)
{
    tree * root = (tree *)malloc(sizeof(tree));
    root->word = data;
    root->left = NULL;
    root->right = NULL;
    return root;
}

char * ReadWord(FILE * file)
{
    char * w;
    char data[20];

    if (fscanf(file, "%s", data) == NULL)
    {
        w = NULL;
    }
    else
    {
        w = (char *)malloc(strlen(data) + 1);
        strcpy(w, data);
    }
    return w;
}

tree * ReadTree(FILE * file)
{
    char * w;
    tree * t;
    char c;

    w = ReadWord(file);

    if (w[0] == ' ' || w[0] == ')')
        return t = NULL;

    t = CreateTreeNode(w);
    fscanf(file, " %c", &c);
    if (c == '(')
    {
        t->left = ReadTree(file);
    }
    else if (c == ')')
    {
        return t;
    }

    fscanf(file, " %c", &c);
    if (c == '(')
    {
        t->right = ReadTree(file);
    }
    else if (c == ')')
    {
        return t;
    }

    fscanf(file, " %c", &c);
    if (c == ')')
        return t;

    return t;
}

void CountTree(tree * t, int * count)
{
    *count = *count + 1;
    if (t->left != NULL)
    {
        CountTree(t->left, count);
    }

    if (t->right != NULL)
    {
        CountTree(t->right, count);
    }

    return;
}

void Round(tree * t, int * h)
{
    *h = *h + 1;
    if (t->left != NULL)
    {
        Round(t->left, h);
        *h = *h - 1;
    }

    if (t->right != NULL)
    {
        Round(t->right, h);
        *h = *h - 1;
    }

    if (t->right == NULL && t->left == NULL)
    {
        AddString(dep, *h);
    }
    return;
}

int TreeHeight(tree * t)
{
    int h = 0, height = 0;
    string * acc = NULL;
    Round(t, &h);

    while (dep)
    {
        acc = dep;
        if (acc->data > height)
        {
            height = acc->data;
        }
        dep = dep->next;
    }

    return height;
}

void PrintTree(tree * t)
{
    int counter = 0, height = 0, hCur = 0, colCur = 0;
    string ** matrix;

    CountTree(t, &counter);
    dep = CreateStringStruct(0);
    height = TreeHeight(t);
    mas = CreateElementStruct(0, 0, 0);
    WorkOnNodes(t, height, counter, &hCur, &colCur);
    matrix = CreateMatrix(mas, height, counter);
    PrintMatrix(matrix, height, counter);

}

void WorkOnNodes(tree * t, int hMax, int countMax, int * hCur, int * colCur)
{
    *hCur = *hCur + 1;
    if (t->left != NULL)
    {
        WorkOnNodes(t->left, hMax, countMax, hCur, colCur);
        *hCur = *hCur - 1;
        *colCur = *colCur + 1;
        AddElement(mas, t->word, *hCur, *colCur);
    }
    else if (t->left == NULL && t->right != NULL)
    {
        *colCur = *colCur + 1;
        AddElement(mas, t->word, *hCur, *colCur);
    }

    if (t->right != NULL)
    {
        WorkOnNodes(t->right, hMax, countMax, hCur, colCur);
        *hCur = *hCur - 1;
    }
    
    if (t->left == NULL && t->right == NULL)
    {
        *colCur = *colCur + 1;
        AddElement(mas, t->word, *hCur, *colCur);
        return;
    }

    return;
}