#include "main.h"
#include <stdio.h>

int main(int argc, char * argv[])
{
    char szBuf[64] = {};

    if (argc > 1) {
        // ������ini��write
        WritePrivateProfileString("Section", "config", argv[1], "./config.ini");
    }
    else {
        // ini����read
        GetPrivateProfileString("Section", "config", "", szBuf, sizeof(szBuf), "./config.ini");
        printf("ini string: [%s]\n", szBuf);
    }
    return 0;
}
