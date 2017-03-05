#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[])
{
	int pid;
	int priority;
	HANDLE hProcess;

	if (argc != 3)
	{
		printf("Invalid arguments count\n");
		printf("Usage: nice-windows.exe <pid> <priority>");
		return 1;
	}

	pid = atoi(argv[1]);
	priority = atoi(argv[2]);

	if (priority < 1 || priority > 6)
	{
		printf("Invalid <priority> value: %d\n", priority);
		printf("<priority> value between 1 and 6");
		return 1;
	}

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if (hProcess == NULL)
	{
		printf("Unable to get handle of process: %d\n", pid);
		return 1;
	}

	switch (priority)
	{
	case 1:
		SetPriorityClass(hProcess, ABOVE_NORMAL_PRIORITY_CLASS);
		break;
	case 2:
		SetPriorityClass(hProcess, BELOW_NORMAL_PRIORITY_CLASS);
		break;
	case 3:
		SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);
		break;
	case 4:
		SetPriorityClass(hProcess, IDLE_PRIORITY_CLASS);
		break;
	case 5:
		SetPriorityClass(hProcess, NORMAL_PRIORITY_CLASS);
		break;
	case 6:
		SetPriorityClass(hProcess, REALTIME_PRIORITY_CLASS);
		break;
	}

	printf("pid: %d priority: %d\n", pid, GetPriorityClass(hProcess));
	CloseHandle(hProcess);

	return 0;
}