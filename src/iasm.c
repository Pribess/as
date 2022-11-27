/*
        Copyright (C) 2022 Pribess (Heewon Cho)
        src/iasm.c
*/

#define IASM_VERSION "0.01"

#include <iasm.h>

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    argc--;
    argv++;

    if (argc < 1) {
            printf("usage: iasm [-v] file\n");
            return 1;
    }

    if (argc > 0 && (*argv)[0] == '-' && (*argv)[1] == 'v') {
            printf("iasm %s (%s, %s)\n", IASM_VERSION, __DATE__, __TIME__);
            return 0;
    }

    // this must be at file part of iasm
    // FILE *fp;
    // if ((fp = fopen(*argv, "r")) == NULL) {
    //         printf("iasm: %s: %s\n", *argv, strerror(errno));
    //         return 1;
    // }

    tokenize("xor eax, eax\nmov eax, 1\npush eax");

}