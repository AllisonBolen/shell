#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
* This class simulaltes a commmand line (shell)
*
* @author Allison Bolen
* @author Alec Allain
* @version 9/9/18
*/

/** Global variables */
//char exit;
char entry[81];
int pid;
int status;

/**
* Main method
*/
int main (int argc, char** argv) {
    // instanciates variables
    //exit = "quit"
    pid = 0;
    status = 0;

    while (1) {
        printf("\nShell: ");
        scanf("%s80\n", entry);
        if (strcmp(entry, "quit") == 0) {
            break;
        }
        for (int i = 0; i < 81; i++) {

        }
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "The fork failed to produce a child");
        }
        else if (pid) {
            waitpid(-1, &status, 0);
        }
        else {
            //execve();
        }
    }
    return 0;
}

/**
* This method parses the string and seperates
* the main command from the parameters
*/
void command () {
    int i = 0;
    while (token != NULL) {
        token = (NULL, " ");
        //printf("%s\n", token);
        counter[i] = token;
        i++;
    }
}
