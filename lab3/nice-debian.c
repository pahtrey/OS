#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	id_t pid;
	int priority;
	int ret;

	if (argc != 3)
	{
		printf("Invalid arguments count\n");
		printf("Usage: nice-debian.exe <pid> <priority>");
		return 1;
	}

	pid = atoi(argv[1]);
    priority = atoi(argv[2]);

	if (priority < -20 || priority > 19)
	{
		printf("Invalid <priority> value: %d\n", priority);
		printf("<priority> value between -20 and 19");
		return 1;
	}		

    ret = setpriority(PRIO_PROCESS, pid, priority);
	
	if(ret == -1) 
	{
	    printf("%s\n", strerror(errno));
	    return 1;
	}

	printf("pid: %d priority: %d\n", pid, getpriority(PRIO_PROCESS, pid));

	return 0;
}