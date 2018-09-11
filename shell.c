#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

/**
 * This class simulates a command line
 * terminal (shell)
 *
 * @author Allison Bolen
 * @author Alec Allain
 * @version 9/9/18
 */ 

/** Instanciating method */ 
void parse(char* strInput, char** parsedInput);

/**
 * Main method
 */
int main(int argc, char* argv[])
{
	// Instanciating variables
	char input[256];
	char* parsedInput[256];
	struct rusage usage;
	//long pSec = 0;
	//long pUsec = 0;
	//long pSwch = 0;
	
	// Prompt takes in command
	printf("$p2shell: ");
	fgets(input, 256, stdin);
	// Checks for only press of enter button or blank space
	while(input[0] =='\n' || input[0] == ' '){
		fgets(input, 256, stdin);
	}
	// Parses the command entered to get main command and parameters
	parse(input, parsedInput);
	// Checks for prompt to exit program
	while(strcmp(parsedInput[0], "quit") != 0){
		int status, pid;
		//struct rusage usage;		

		// Make fork 
		pid = fork();
		if(pid < 0){
			// Fork failed
			perror("Fork failed\n");
			exit(1);
		}
		else if (pid){
			// Child process is created
			waitpid(pid, &status, 0);
			// CPU usage of child process and involuntary context switches are displayed
			getrusage(RUSAGE_CHILDREN, &usage);
			printf("\nCPU TIME USED BY CHILD: %ld.%08ld\n",usage.ru_utime.tv_sec,usage.ru_utime.tv_usec);
			//pSec = usage.ru_utime.tv_sec;
			//pUsec = usage.ru_utime.tv_usec;
		
			printf("\nINVOLUNTARY CONTEXT SWITCHES: %ld\n", usage.ru_nivcsw);

			//pSwch = usage.ru_nivcsw;
			
		}
		else {
			// Command is executed
			execvp(parsedInput[0], parsedInput);
			// If command is not executed properly, printf displays error
			printf("Unkown command.");
			// grusage
			exit(0);	
		} 

		// Prompt is displayed once command has been executed
		printf("$p2shell: ");
		fgets(input, 256, stdin);
		while(input[0] =='\n' || input[0] == ' '){
			fgets(input, 256, stdin);
		}
		parse(input, parsedInput);
	}

	return(0);
}

// i want parsed int to be a passed by reference var so its changes here are saved to the original
// This should return an array of arrays? words and \0s? for the comands used in exeve
/**
 * This method parses the string the user has entered
 * to get both the shell command as well as the flags
 * and extentions
 */ 
void parse(char * strInput, char** parsedInput)
{	
	char *pos;
	if((pos=strchr(strInput, '\n')) != NULL){
		*pos = '\0';
	}	
	char * pch;
	// String is split every time a space is detected
	pch = strtok(strInput," ");
	int count = 0;
  	while (pch != NULL)
 	{	
    	//	printf ("*%s*\n",pch);
    		parsedInput[count] = pch;
    		pch = strtok (NULL, " ");
    		count++;
  	}
	// Ending of string is set as a Null point
	parsedInput[count]=NULL;
}
