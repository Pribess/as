/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/parser.c
*/

#include "parser.h"

char **as_preproc(char **src, int *cnt) {
	int i = 0;

	while (src[i]) {
		int j = 0;

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
				char *filename = as_malloc(size * sizeof(char));

				k = 0;

				/* if filename is normaly provided */
				if (src[i][j++] == '"') {
					/* iterating until meet double quote */
					while (src[i][j + k] != '"') {
						/* skip if character is null character which means filename does not ends with double qoute */	
						if (!src[i][j + k]) {
							as_free(filename);
							goto nextline;
						}

						if (k >= size) {
							size *= 2;
							filename = as_realloc(filename, size);
						}

						filename[k] = src[i][j + k];

						k++;
					}

					filename = as_realloc(filename, k + 1);
					filename[k] = 0x00;
						printf("%s\n", filename);

					FILE *stream = as_openfile(filename);
					as_free(filename);

					int cnt;
					char **rows = as_readall(stream, &cnt);
					/* todo */
					/* print warning and ignores when characters are found after import keyword (skip if meet remarks) */
					/* should implement inserting rows which are loaded from file */

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