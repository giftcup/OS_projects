#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LINE 80     // define 

int main(void) {
    char *args[MAX_LINE/2 + 1];
    char arg[MAX_LINE];
    int ch, i = 0;
    int should_run = 1;

    while (should_run) {
        printf("osh> ");
        fflush(stdout);
        
        fgets(arg, sizeof(arg), stdin);

        args[0] = strtok(arg, " \n");
        while (args[i] != NULL) {
            args[++i] = strtok(NULL, " \n");
        }
        should_run = 0;
    }

    execvp(args[0], args);


    return 0;
}