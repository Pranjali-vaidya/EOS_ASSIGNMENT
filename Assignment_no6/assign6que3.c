#include<stdio.h>
#include<unistd.h>
int main() 
{
	int ret, cnt = 0;
    int ret = s1;
	int cnt =s2;
	while(1)
		{
			ret = fork();
			if(ret == -1) 
			{// parent
				printf("fork() failed.\n");
			}
			waitpid(&s1, 0);
				_exit(0);
			}
			else if(ret == 0)
			{// child proces
				sleep(5);
			}
			waitpid(&s2 , 0); 
				_exit(0);
			}
			else
			{//parent process
				cnt++;
				printf("child count: %d\n", cnt);
			}
		}
	
		return 0;
}

