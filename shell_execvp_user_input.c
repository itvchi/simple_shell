/*
    Simple program which executes command with one argument passed by user using execvp system call
    Passed command and argument should be up to 15 byte long each
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Please, pass only one command with one argument!\n");

    char* arglist[3];
    for(uint i=0; i<3; i++)
        arglist[i] = (char*) malloc(sizeof(char)*16);
    
    printf("arglist[0]: ");
    scanf("%s", arglist[0]); //get command
    printf("arglist[1]: ");
    scanf("%s", arglist[1]); //get argument
    arglist[2] = NULL; //last argument have to be NULL

    execvp(arglist[0], arglist);

    return 0;
}