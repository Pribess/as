/* SPDX-License-Identifier: MIT */
/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/file/file.c
*/

#include "file.h"

FILE *as_openfile(const char *filename) {
	FILE *stream;

	if (!(stream = fopen(filename, "r"))) {
		char *prefix = as_malloc((sizeof("as: ") + strlen(filename)) * sizeof(char));
		sprintf(prefix, "%s'%s'", "as: ", filename);
		as_abort_prefix(prefix);
	}

	return stream;
}

bool as_file_exists(const char *filename) {
	FILE *stream;
	if (!(stream = fopen(filename, "r"))) return false;
	fclose(stream);
	return true;
}

char *as_readline(FILE *stream) {
	if (!stream) {
		return NULL;
	}

	const size_t block = 16;
	char *line = as_malloc((block + 1) * sizeof(char));
	int idx = 0;

	while (!feof(stream)) {
		if (!fgets(line + idx, block + 1, stream)) {
			/* check if file is empty */
			if (fgetc(stream) == EOF) {
				return NULL;
			}
			as_abort();
		}

		/* if contains line feed or is end-of-file */
		if ((line + idx)[strlen(line + idx) - 1] == '\n') {
			line = as_realloc(line, (strlen(line) + 1) * sizeof(char));
			/* substitute line feed to null terminator */
			line[strlen(line) - 1] = 0x00;
			return line;
		} else if (feof(stream)) {
			line = as_realloc(line, (strlen(line) + 1) * sizeof(char));
			return line;
		} else {
			idx += block;
			line = as_realloc(line, (idx + block + 1) * sizeof(char));
		}
	}

	return NULL;
}

char **as_readall(FILE* stream, int *cnt) {
	*cnt = 0;
	size_t size = 64;
	char **list = as_malloc((size) * sizeof(char *));

	while ((list[(*cnt)++] = as_readline(stream))) {
		/* double-up size if list overflows */
		if (*cnt >= size) {
			size *= 2;
			list = as_realloc(list, (size) * sizeof(char *));
		}
	}
	(*cnt)--;

	list[*cnt + 1] = NULL;

	/* resize to fit */
	list = as_realloc(list, (*cnt + 1) * sizeof(char *));

	return list;
}