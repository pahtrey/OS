#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

void printCmd(char * pid)
{
	char path[40], cmdLine[256];
	FILE * cmdFile;
	snprintf(path, 40, "/proc/%s/cmdline", pid);
	cmdFile = fopen(path, "r");
	if (fgets(cmdLine, sizeof(cmdLine), cmdFile))
	{
		printf("Command: %s\n", cmdLine);
	}
	fclose(cmdFile);
}

void printResources(char * pid)
{
	char path[40], statusLine[256];
	FILE * statusFile;
	snprintf(path, 40, "/proc/%s/status", pid);
	statusFile = fopen(path, "r");
	while (fgets(statusLine, sizeof(statusLine), statusFile))
	{
		if ((strncmp(statusLine, "Name", 4) == 0)
			|| (strncmp(statusLine, "State", 5) == 0)
			|| (strncmp(statusLine, "VmPeak", 6) == 0)
			|| (strncmp(statusLine, "VmSize", 6) == 0)
			|| (strncmp(statusLine, "VmLck", 5) == 0)
			|| (strncmp(statusLine, "VmHWM", 5) == 0)
			|| (strncmp(statusLine, "VmRss", 5) == 0)
		)
		{
			printf("%s", statusLine);
		}
	}
	fclose(statusFile);
}

int main()
{
    struct dirent * dir = NULL;
    DIR * dir_proc = NULL;
    dir_proc = opendir("/proc/");
    if (dir_proc == NULL)
    {
        perror("Can not open the /proc/ directory");
        return 1;
    }

    while ((dir = readdir(dir_proc)) != 0)
	{
        if (dir->d_type == DT_DIR && isdigit(dir->d_name[0]))
		{
			printf("Pid: %s\n", dir->d_name);
			printCmd(dir->d_name);
			printResources(dir->d_name);
			printf("===================\n");
        }
    }
    closedir(dir_proc) ;
    return 0;
}

