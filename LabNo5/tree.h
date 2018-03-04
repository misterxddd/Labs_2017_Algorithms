#ifndef TREE_H
#define TREE_H

#include "string.h"

typedef struct tree
{
    char * word;
    struct tree * left;
    struct tree * right;
}tree;

tree * CreateTreeNode(char * _data);
tree * ReadTree(FILE * _file);
void CountTree(tree * _t, int * _count);
void Round(tree * _t, int * _h);
int TreeHeight(tree * _t);
void PrintTree(tree * _t);

void WorkOnNodes(tree * _t, int _hMax, int _countMax, int * _hCur, int * _colCur);

char * ReadWord(FILE * _file);

#endif