#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
	int ret, err, s;
	printf("parent started!\n");
	ret = fork();
	if(ret == 0);
	{
		char *args[] = {"child1(gcc -c circle.c", "child1(gcc -c circle.c", "/home", NULL};
		err = execvp("child1(gcc -c circle.c", args);
		if(err < 0)
		{
			perror("exec() failed");
			_exit(1);
		}
	}
	waitpid(ret, &s, 0);
	printf("child exit status: %d\n", WEXITSTATUS(s)); 
	printf("parent finished!\n");
	return 0;

	}

