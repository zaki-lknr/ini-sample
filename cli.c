#include "main.h"
#include <stdio.h>

int main(int argc, char * argv[])
{
    char szBuf[64] = {};

    if (argc > 1) {
        // 引数をiniへwrite
        WritePrivateProfileString("Section", "config", argv[1], "./config.ini");
    }
    else {
        // iniからread
        GetPrivateProfileString("Section", "config", "", szBuf, sizeof(szBuf), "./config.ini");
        printf("ini string: [%s]\n", szBuf);
    }
    return 0;
}
