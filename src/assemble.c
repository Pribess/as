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

	as_preproc(filename, src, &cnt);

}