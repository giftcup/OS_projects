#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_CMDS 100

typedef struct args {
    char **args;
    int len;
} Args;

char *builtin_cmd[] = { "exit",
                        "! !" };

char* read_cmds(char *buffer);
Args parse_cmds(Args argument, char *buffer);

int main(void) {
    Args parse;
    Args previous_parse;
    char *buffer;
    int* pid;
    int ch, i = 0;
    int should_run = 1;

    pid = malloc(sizeof(int));
    parse.args = NULL;

    while (should_run) {
        printf("osh> ");
        fflush(stdout);
        
        buffer = read_cmds(buffer);
        previous_parse = parse;
        parse = parse_cmds(parse, buffer);
   
        if (strcmp(parse.args[0], "exit") == 0)
            should_run = 0;
        
        if (strcmp(parse.args[0], "!!") == 0) {
            parse = previous_parse;
            previous_parse = parse;
            
            if (parse.args == NULL) {
                printf("No commands in history\n");
                continue;
            }
        }

        *pid = fork();
        if (*pid == 0) {
            printf("Been in child\n");

            execvp(parse.args[0], parse.args);
            if (execvp(parse.args[0], parse.args) == -1) {
                printf("failure to execute");
                exit(0);
            }
            printf("%s %s\n", parse.args[0], parse.args[1]);
        }
        else if (*pid > 0 && (strcmp(parse.args[parse.len-1], "&") != 0)){
            printf("Been in parent\n");
            wait(pid);
        }
    }

    return 0;
}

char* read_cmds(char *buffer) {
    char ch;
    int position, bufsize;

    bufsize = MAX_CMDS;

    buffer = malloc(sizeof(ch) * bufsize);
    if (buffer == NULL) {
        printf("memalloc failed in read_cmds\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        ch = getchar();

        if (ch == '\n' || ch == EOF) {
            buffer[position] = '\0';
            return buffer;
        }
        else {
            buffer[position] = ch;
        }
        position++;

        if (position >= bufsize) {
            bufsize += MAX_CMDS;
            buffer = realloc(buffer, bufsize);
            if (buffer == NULL) {
                printf("memalloc failed in read_cmds\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

Args parse_cmds(Args parse, char *buffer) {
    int i = 0;

    parse.args = malloc(sizeof(char) * strlen(buffer));
    
    parse.args[0] = strtok(buffer, " \n\t\b");
    while (parse.args[i] != NULL) {
       parse.args[++i] = strtok(NULL, " \n\t\b");
    }
    parse.args[i] = NULL;
    parse.len = i;

    return parse;
}