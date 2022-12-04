/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/file/file.c
*/

#include "file.h"

FILE *as_open_file(const char *filename) {
	FILE *fp;

	if (!(fp = fopen(filename, "r"))) {
		char *prefix = malloc(sizeof("as: ") + strlen(filename));
		sprintf(prefix, "%s%s", "as: ", filename);
		as_abort(prefix);
		free(prefix);
	}

	return fp;
}