/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/file/file.c
*/

#include "file.h"

FILE *as_openfile(const char *filename) {
	FILE *stream;

	if (!(stream = fopen(filename, "r"))) {
		char *prefix = as_malloc(sizeof("as: ") + strlen(filename));
		sprintf(prefix, "%s%s", "as: ", filename);
		as_abort_prefix(prefix);
		free(prefix);
	}

	return stream;
}

char *as_readline(FILE *stream) {

	const size_t block = 16;
	char *line = as_malloc(block);
	int idx = 0;

	while (!feof(stream)) {
		if (!fgets(line + idx, block, stream)) {
			/* check if file is empty */
			if (fgetc(stream) == EOF) {
				return NULL;
			}
			as_abort();
		}

		/* if contains line feed or is end-of-file */
		if ((line + idx)[strlen(line + idx) - 1] == '\n') {
			line = as_realloc(line, idx + strlen(line));
			/* substitute line feed to null terminator */
			line[strlen(line) - 1] = 0x00;
			return line;
		} else if (feof(stream)) {
			line = as_realloc(line, idx + strlen(line));
			return line;
		} else {
			idx += block;
			line = as_realloc(line, idx + block);
		}
	}

	return NULL;
}