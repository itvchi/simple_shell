/*
    Simple program which executes command with number of arguments passed by user using execvp system call
    Passed command and argument should be up to 15 byte long each
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Enter number of arguments (including command):");
    uint maxargs;
    scanf("%d", &maxargs);

    char** arglist = (char**) malloc(sizeof(char*)*(maxargs+1)); //last argument have to be NULL, so there are maxargs+1 arguments
    for(uint i=0; i<maxargs; i++)
        arglist[i] = (char*) malloc(sizeof(char)*16);
    
    uint i=0;
    while(i<maxargs)
    {
        printf("arglist[%d]: ", i);
        scanf("%s", arglist[i]); //get argument
        i++;
    }
    arglist[i] = NULL; //last argument have to be NULL

    execvp(arglist[0], arglist);
    perror("Exec failed");

    return 0;
}