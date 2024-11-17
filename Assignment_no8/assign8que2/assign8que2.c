#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>

void handle_sigchld(int sig)
{
	while (waitpid(-1, NULL, WNOHANG) > 0);
}
void execute_command(char *command)
{
	pid_t pid;
	char *args[100];
	int i = 0;
    int background = 0;

	char *token = strtok(command, "\n");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, "\n");
	}
	args[i] = NULL;
	if (i> 0 && strcmp(args[i -1], "&") == 0)
	{
		background = 1;
		args[i - 1] = NULL;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) <0)
		{
			perror("Exec failed");
			exit(1);
		}
	}
	else
	{
		printf("started background process with PID: %d\n", pid);
	}
}

int main()
{
	char command[1024];
	signal(SIGCHLD, handle_sigchld);
	while (1)
	{
		printf("my_shell> ");
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			break;
		}
		if (strlen(command) >1)
		{
			execute_command(command);
		}
	}
	return 0;
}
