#include "main.h"
#include <stdio.h>

int main(int argc, char * argv[])
{
    char szBuf[64] = {};

    if (argc > 1) {
        // ˆø”‚ğini‚Öwrite
        WritePrivateProfileString("Section", "config", argv[1], "./config.ini");
    }
    else {
        // ini‚©‚çread
        GetPrivateProfileString("Section", "config", "", szBuf, sizeof(szBuf), "./config.ini");
        printf("ini string: [%s]\n", szBuf);
    }
    return 0;
}
