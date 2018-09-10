#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

void parse(char* strInput, char** parsedInput);

int main(int argc, char* argv[])
{
	char input[256];
	char* parsedInput[256];
	struct rusage usage;
	//long pSec = 0;
	//long pUsec = 0;
	//long pSwch = 0;
	printf("$p2shell: ");
	fgets(input, 256, stdin);
	parse(input, parsedInput);
	while(strcmp(parsedInput[0], "exit") != 0){
		int status, pid;
		//struct rusage usage;		

		// make fork 
		pid = fork();
		if(pid < 0){
			// fork failed
			perror("Fork failed\n");
			exit(1);
		}
		else if (pid){
			waitpid(pid, &status, 0);
		getrusage(RUSAGE_CHILDREN,&usage);
		printf("\nCPU TIME USED BY CHILD: %ld.%08ld\n",usage.ru_utime.tv_sec,usage.ru_utime.tv_usec);
		//pSec = usage.ru_utime.tv_sec;
		//pUsec = usage.ru_utime.tv_usec;
		
		printf("\nINVOLUNTARY CONTEXT SWITCHES: %ld\n", usage.ru_nivcsw);

		//pSwch = usage.ru_nivcsw;
			
		}
		else {		
			execvp(parsedInput[0], parsedInput);
			// grusage
			exit(0);	
		} 

		printf("$p2shell: ");
		fgets(input, 256, stdin);
		parse(input, parsedInput);
	}

	return(0);
}

// i want parsed int to be a passed by reference var so its changes here are saved to the original
// This should return an array of arrays? words and \0s? for the comands used in exeve
void parse(char * strInput, char** parsedInput)
{	
	char *pos;
	if((pos=strchr(strInput, '\n')) != NULL){
		*pos = '\0';
	}	
	char * pch;
	pch = strtok(strInput," ");
	int count = 0;
  	while (pch != NULL)
 	{	
    	//	printf ("*%s*\n",pch);
    		parsedInput[count] = pch;
    		pch = strtok (NULL, " ");
    		count++;
  	}
	parsedInput[count]=NULL;
}
