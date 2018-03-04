#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "matrix.h"
#include "tree.h"
#include "string.h"

int main()
{
    FILE * inputFile;
    tree * mainTree;
    inputFile = fopen("C:/Tests/input_5.txt", "r");

    mainTree = ReadTree(inputFile);


    PrintTree(mainTree);

    _getch();
    return 0;
}
