/*
        Copyright (C) 2022 Pribess (Heewon Cho)
        src/as.c
*/

#define AS_VERSION "0.01"

#include <stdio.h>
#include <locale.h>

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    argc--;
    argv++;

    if (argc < 1) {
            printf("usage: as [-v] file\n");
            return 1;
    }

    if (argc > 0 && (*argv)[0] == '-' && (*argv)[1] == 'v') {
            printf("as %s (%s, %s)\n", AS_VERSION, __DATE__, __TIME__);
            return 0;
    }

    // this must be at file part of as
    // FILE *fp;
    // if ((fp = fopen(*argv, "r")) == NULL) {
    //         printf("as: %s: %s\n", *argv, strerror(errno));
    //         return 1;
    // }

//     tokenize("xor eax, eax\nmov eax, 1\npush eax");

}