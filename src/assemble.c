/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/assemble.c
*/

#include "assemble.h"

void assemble() {

	FILE *stream = as_openfile(filename);
	
	int cnt;

	char **src = as_readall(stream, &cnt);
	as_preproc(src, &cnt);

	printf("lines:\n");
	int i = 0;
	while (src[i]) {
		printf("%s\n", src[i]);
		i++;
	}

}