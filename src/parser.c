/* SPDX-License-Identifier: MIT */
/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/parser.c
*/

#include "parser.h"
#include "alloc.h"
#include "err.h"

void as_preproc(const char *filename, char **src, int *cnt) {
	int i = 0;

	/* iterate lines */
	while (src[i]) {
		int j = 0;

		/* iterate characters of line */
		while (src[i][j]) {

			if (src[i][j] == ' ' || src[i][j] == '\t') {
				j++;
				continue;
			} else if (src[i][j] == 'i') {
				int k = 0;

				while (k < sizeof("import ") - 1) {
					if (src[i][j + k] != "import "[k]) {
						goto nextline;
					}
					k++;
				}
				j += k;
				
				size_t size = 16;
				char *ifilename = as_malloc(size * sizeof(char));

				k = 0;

				/* if filename is normaly provided */
				if (src[i][j++] == '"') {
					/* iterating until meet double quote */
					while (src[i][j + k] != '"') {
						/* skip if character is null character which means filename does not ends with double qoute */	
						if (!src[i][j + k]) {
							as_free(ifilename);
							goto nextline;
						}

						if (k >= size) {
							size *= 2;
							ifilename = as_realloc(ifilename, size);
						}

						ifilename[k] = src[i][j + k];

						k++;
					}
					j += k + 1;

					ifilename = as_realloc(ifilename, k + 1);
					ifilename[k] = 0x00;

					while (src[i][j]) {
						if (src[i][j] != ' ' && src[i][j] != '\t') {
							as_free(ifilename);
							as_warn_msg("%s:%d: warning: 'import' ignored because of trailing garbage", filename, i + 1);
							goto nextline;
						}
						j++;
					}

					FILE *stream = as_openfile(ifilename);
					as_free(ifilename);

					int icnt;
					char **rows = as_readall(stream, &icnt);
					
					src = as_realloc(src, (*cnt - 1 + icnt + 1) * sizeof(char *));

					*cnt += icnt - 1;
					src[*cnt] = NULL;

					memcpy(src + i, rows, icnt * sizeof(char *));

					as_free(rows);

					goto nextline;
				}
				goto nextline;
			} else {
				goto nextline;
			}
		}

		nextline:
			i++;
	}
}