#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#define BUFF_SIZE 255

// error message, as specified by assignment instructions
void error() {
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
    return;
}

// main function
int main(int argc, char **argv) {
    printf("This shell currently only supports exit as a built-in function,\n");
    printf("and breaks with more than one argument.\n");
    printf("Use at your own risk.\n");
    printf("(made my Collin Bauer)\n");

    // begin shell loop
    char buffer[BUFF_SIZE];
    while (1) {
        printf("ccsh>");
        fgets(buffer, BUFF_SIZE, stdin);

        // read in arguments
        // unfortunately breaks with more than one argument
        // not sure why
        char *args[100];
        int i = 0;
        int j = 0;
        while (buffer[j] != '\n') {
            args[i] = malloc(100 * sizeof(char));
            int k = 0;
            while (1) {
                if (buffer[j] != ' ' && buffer[j] != '\n')
                    args[i][k] = buffer[j];
                else {
                    args[i][k] = '\0';
                    break;
                }
                j++;
                k++;
            }
            i++;
//            printf("i: %d\n", i); //debug
        }
        args[i] = NULL;


        // built-in functions
        if      (strcmp(args[0], "exit") == 0){
            exit(0);
        }
        else if (strcmp(args[0], "cd") == 0){
            printf("Not yet implemented.\n");
            error();
        }
        else if (strcmp(args[0], "path") == 0){
            printf("Not yet implemented.\n");
            error();
        }
        else {
            // if not built-in, execute the command in a subprocess
//            printf("%s\n", args[0]); //debug
            int pid;
            // try to fork a child
            if ((pid = fork()) < 0)
                error();
            else if (pid == 0)
                // on successful fork, attempt to execute command
                if (execvp(args[0], args) < 0)
                    error();
            // wait for child process to finish
            wait(NULL); 
        }
    }
    
}