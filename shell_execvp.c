/*
    Simple program which executes hardcoded command with arguments using execvp system call
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char* arglist[4];
    arglist[0] = "ls";
    arglist[1] = "-al";
    arglist[2] = "/home/itvchi/Pobrane";
    arglist[3] = NULL; //last argument have to be NULL

    execvp(arglist[0], arglist);

    return 0;
}