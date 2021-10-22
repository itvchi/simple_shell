/*
    Simple shell which executes commands passed by user
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LEN 512 //max length of input string
#define MAXARGS 15 //max arguments passed with command including itself
#define ARG_LEN 30 //max length of single argument

char* read_line(char* prompt, FILE* fp);
char** tokenize(char* string);
void execute(char* arglist[]);

int main()
{
    char* prompt = "simple_shell> ";
    char* user_imput;
    char** arglist;

    while((user_imput = read_line(prompt, stdin)) != NULL)
    {
        if((arglist = tokenize(user_imput)) != NULL)
        {
            execute(arglist);

            //free used memory
            for(uint i=0; i<MAXARGS+1; i++)
                free(arglist[i]);
            free(arglist); 
        }
        free(user_imput);
    }

    return 0;
}

char* read_line(char* prompt, FILE* fp)
{
    printf("%s", prompt); //show prompt
    char* line = (char*) malloc(sizeof(char)*MAX_LEN); //alocate memory for input string

    char c; //temp character
    uint i=0; //position counter

    while ((c = getc(fp)) != EOF)
    {
        if(c == '\n')
            break;
        line[i++] = c;
    }
    line[i] = '\0'; //end string with 0 byte
    
    return line;
}

char** tokenize(char* string)
{
    //alocate memory for arglist
    char** arglist = (char**) malloc(sizeof(char*)*(MAXARGS+1)); //last argument have to be NULL, so there are MAXARGS+1 arguments
    for(uint i=0; i<MAXARGS+1; i++)
    {
        arglist[i] = (char*) malloc(sizeof(char)*(ARG_LEN+1)); //end string with 0 byte, so there are ARG_LEN+1 bytes
        bzero(arglist[i], ARG_LEN+1);
    }

    char* cp = string;
    char* start;
    uint len;
    uint argnum = 0;

    while(*cp != '\0')
    {
        //skip leading spaces
        while(*cp == ' ' || *cp == '\t')
            cp++;

        start = cp; //cp is now pointing to first letter of the word
        len = 1; //initialize length of the word

        while(*++cp != '\0' && !(*cp == ' ' || *cp == '\t')) //find the length of the word
            len++;
        
        strncpy(arglist[argnum], start, len); //copy string to arglist
        arglist[argnum][len] = '\0'; //end string with 0 byte
        argnum++;
    }

    arglist[argnum] = NULL; //last argument have to be NULL
    return arglist;
}

void execute(char* arglist[])
{
    int status;
    int cpid = fork();

    switch(cpid)
    {
        case -1:
            perror("fork failed");
            exit(1);
            break;
        case 0:
            execvp(arglist[0], arglist);
            perror("exec failed");
            exit(2);
            break;
        default:
            while(wait(&status) != cpid);
            printf("Child exited with status %d\n", status>>8);

    }
}