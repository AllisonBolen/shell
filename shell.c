#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char input[256];
	printf("$p2shell: ");
	scanf("%s", input);
	while(strcmp(input, "exit") != 0){
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
			printf("we are the child\n");
		}
		else {
		//	char* args[3];
		//	args[0] = "ls";
		//	args[1] = "\0";
		//	execve(args[1], &args[1]);
			printf("execute\n");
			exit(0);	
		} 

		printf("$p2shell: ");
		scanf("%s", input);

	}

	return(0);
}	
