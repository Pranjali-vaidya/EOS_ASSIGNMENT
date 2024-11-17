#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


void handle_sigint(int sig) {
    printf("\nCaught signal %d (SIGINT). Shell will continue running...\n", sig);
}


int is_delim(char *delim, char ch) {
    int i;
    for (i = 0; delim[i] != '\0'; i++) {
        if (ch == delim[i])
            return 1;
    }
    return 0;
}

char *strtok_custom(char *str, char *delim) {
    static char *ptr = NULL;
    char *p, *ret;

    
    if (str != NULL)
        ptr = str;

    
    if (ptr == NULL)
        return NULL;

    ret = ptr;
    p = ptr;

    
    while (*p != '\0' && is_delim(delim, *p))
        p++;

    
    if (*p == '\0') {
        ptr = NULL;
        return NULL;
    }

    
    while (*p != '\0' && !is_delim(delim, *p))
        p++;

    
    if (*p != '\0') {
        *p = '\0';
        ptr = p + 1;
    } else {
        ptr = NULL;
    }

    return ret;
}

int main() {
    char string[256];  
    char *ptr;
    
    
    signal(SIGINT, handle_sigint);

    
    while (1) {
        
        printf("Enter a string to tokenize (or type 'exit' to quit): ");
        if (fgets(string, sizeof(string), stdin) == NULL) {
            
            printf("\nExiting the program...\n");
            break;
        }

        
        string[strcspn(string, "\n")] = '\0';

       
        if (strcmp(string, "exit") == 0) {
            printf("Exiting the shell...\n");
            break;
        }

        
        ptr = strtok_custom(string, " ");
        int token_count = 1;
        while (ptr != NULL) {
            printf("%dth token: %s\n", token_count, ptr);
            ptr = strtok_custom(NULL, " ");
            token_count++;
        }

        
        printf("-----\n");
    }

    return 0;
}

