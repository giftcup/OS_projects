#include <stdio.h>
#include <string.h>

int main(void) {
    char str[80] = "This is a string";
    char *token;

    token = strtok(str, " ");
    while (token != NULL) {
        printf("%s\n", token);

        token = strtok(NULL, " ");
    }
    
    return 0;
}