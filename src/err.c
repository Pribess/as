/* SPDX-License-Identifier: MIT */
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

/* print warning with custom warning message */
void as_warn_msg(const char *fmsg, ...) {
	va_list list;
	va_start(list, fmsg);
	vfprintf(stdout, fmsg, list);
	va_end(list);
	printf("\n");
}