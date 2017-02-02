#include <windows.h>
#include <stdio.h>

void main()
{
    DWORD version = 0;
    DWORD majorVersion = 0;
    DWORD minorVersion = 0;
    DWORD build = 0;
    
    version = GetVersion();
    
    majorVersion = (DWORD) (LOBYTE(LOWORD(version)));
    minorVersion = (DWORD) (HIBYTE(LOWORD(version)));

    if (version < 0x80000000)
        build = (DWORD) (HIWORD(version));

    printf("Windows version is %d.%d build (%d)\n", majorVersion, minorVersion, build);
}