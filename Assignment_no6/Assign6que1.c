#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main() 
{
	int i, pid1, pid2, pid3, pid4, pid5, s1, s2, s3, s4, s;

	pid1 = fork();
	if(pid1 == 0)
	{//child 1
		for(i=1; i<=5; i++)
		{// child 1
			printf("child1: %d\n", i);
			sleep(1);
		}
		_exit(3);
	}

	pid2 = fork();
	if(pid2 == 0)
	{//child 2
		for(i=1; i<=5; i++)
		{
			printf("child2: %d\n", i);
			sleep(1);
		}
		_exit(4);
	}

	pid3 = fork();
	if(pid3 == 0)
	{// child 3
		for(i=1; i<=5; i++)
		{
			printf("child3: %d\n", i);
			sleep(1);
		}
		_exit(5);
	}

	pid4 = fork();
	if(pid4 == 0)
	{// child4
		for(i=1; i<=5; i++)
		{
			printf("child4: %d\n", i);
			sleep(1);
		}
		_exit(6);
	}

	pid5 = fork();
	if(pid5 == 0)
	{//child5
		for(i=1; i<=5; i++)
		{
			printf("child5: %d\n", i);
			sleep(1);
		}
		_exit(7);
	}

	for(i=1; i<=5; i++)
	{
		printf("parent: %d\n", i);
		sleep(1);
	}

	while(waitpid(-1, &s, 0) > 0)
		printf("child exit status: %d\n",WEXITSTATUS(s));
	return 0;
}


