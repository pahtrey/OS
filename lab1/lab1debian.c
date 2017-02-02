#include <stdio.h>

void main ()
{
    char ch;
    FILE *fileVersion;
    
    fileVersion = fopen("/proc/version", "r");

    while ((ch = getc(fileVersion)) != EOF)
    {
        putchar(ch);
    }

    fclose(fileVersion);
}
