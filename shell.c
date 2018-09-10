#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void parse(char* strInput, char** parsedInput);

int main(int argc, char* argv[])
{
	char input[256];
	char* parsedInput[256];
	printf("$p2shell: ");
	fgets(input, 256, stdin);
	//printf("Before parsing: %s\n", input);
	parse(input, parsedInput);
	//printf("After Parsing: %s\n", parsedInput[0]);
	while(strcmp(parsedInput[0], "exit") != 0){
		int status, pid;
		
		// make fork 
		pid = fork();
		if(pid < 0){
			// fork failed
			perror("Fork failed\n");
			exit(1);
		}
		else if (pid){
			waitpid(pid, &status, 0);
	//		printf("we are the parent\n");
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
	//printf ("Splitting string \"%s\" into tokens:\n",strInput);	
	pch = strtok (strInput," ");
	int count = 0;
  	while (pch != NULL)
  	{	
    	//	printf ("%s\n",pch);
    		parsedInput[count] = pch;
    		pch = strtok (NULL, " ");
    		count++;
  	}
	parsedInput[count+1]=NULL; 
}
