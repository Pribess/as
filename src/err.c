/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/err.c
*/

#include "err.h"

void as_exit(int code) {
    exit(code);
}

void as_abort() {
    perror("as");
    as_exit(EXIT_FAILURE);
}

/* abort with system error message and custom prefix */
void as_abort_prefix(const char *prefix) {
    perror(prefix);
    as_exit(EXIT_FAILURE);
}

/* abort with custom error message */
void as_abort_msg(const char *msg) {
    fprintf(stderr, "as: %s\n", msg);
    as_exit(EXIT_FAILURE);
}