/* SPDX-License-Identifier: MIT */
/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/assemble.c
*/

#include "assemble.h"

void assemble(const char *filename) {

	FILE *stream = as_openfile(filename);
	
	int cnt;
	char **src = as_readall(stream, &cnt);

	char ** asdfd = as_preproc(filename, src, &cnt);

	int i = 0;
	while (i++ < cnt) {
		printf("%s\n", asdfd[i - 1]);
	}

}