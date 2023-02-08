/* SPDX-License-Identifier: MIT */
/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/parser.c
*/

#include "parser.h"

char **as_preproc(const char *filename, char **src, int *cnt, struct import_meta *metadata) {
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
				char *imported_filename = as_malloc((size) * sizeof(char));

				k = 0;
				/* if filename is normaly provided */
				if (src[i][j++] == '"') {
					/* iterating until meet double quote */
					while (src[i][j + k] != '"') {
						/* skip if character is null character which means filename does not ends with double qoute */	
						if (!src[i][j + k]) {
							as_free(imported_filename);
							goto nextline;
						}

						if (k >= size) {
							size *= 2;
							imported_filename = as_realloc(imported_filename, (size) * sizeof(char));
						}

						imported_filename[k] = src[i][j + k];

						k++;
					}
					j += k + 1;

					/* resize to fit */
					imported_filename = as_realloc(imported_filename, (k + 1) * sizeof(char));
					imported_filename[k] = 0x00;

					/* check if trailing garbage exists */
					while (src[i][j]) {
						if (src[i][j] != ' ' && src[i][j] != '\t') {
							as_warn_fmsg("%s:%d: warning: trailing garbage after 'import' ignored", filename, i + 1);
							break;
						}
						j++;
					}

					/* convert to relative file path of file which is processing */
					int l = strlen(filename) - 1;
					while (!(l < 0) && filename[l--] != '/'); /* count last component of path */
					/* correct not intended decreases (postfix decrement and length) */
					if (l == -1) l++;
					else l += 2;
					
					/* 
						strlen("example/of/path/") + strlen("imported/filename")
						equals to
						strlen("example/of/path/imported/filename")
					*/
					char *relative_filename = malloc((l + strlen(imported_filename) + 1) * sizeof(char));
					
					strncpy(relative_filename, filename, l);
					strcpy(relative_filename + l, imported_filename);

					/* open file and append it to file which is processing */
					if (!as_file_exists(relative_filename)) {
						as_abort_fmsg("%s: %d: '%s': No such file or directory", filename, i + 1, relative_filename);
					}

					FILE *stream = as_openfile(relative_filename);

					int imported_cnt;
					char **imported_source = as_readall(stream, &imported_cnt);

					/* add import meta data to print line which has error in other process */
					if (metadata->children_cap < metadata->children_cnt + 1) {
						metadata->children_cap *= 2;
						metadata->children = as_realloc(metadata->children, (metadata->children_cap) * sizeof(struct import_meta *));
					}
					metadata->children[metadata->children_cnt] = malloc(sizeof(struct import_meta));
					metadata->children[metadata->children_cnt]->filename = imported_filename;
					size_t pushed_offset = 0;
					for (int n = 0 ; n < metadata->children_cnt ; n++) {
						pushed_offset += metadata->children[n]->size - 1;
					}
					metadata->children[metadata->children_cnt]->imported_line = i + 1 - pushed_offset;
					metadata->children[metadata->children_cnt]->size = imported_cnt;
					metadata->children[metadata->children_cnt]->children = as_malloc((4) * sizeof(struct import_meta *));
					metadata->children[metadata->children_cnt]->children_cap = 4;
					metadata->children[metadata->children_cnt]->children_cnt = 0;

					as_preproc(relative_filename, imported_source, &imported_cnt, metadata->children[metadata->children_cnt]);

					metadata->children_cnt++;

					src = as_realloc(src, (*cnt - 1 + imported_cnt + 1) * sizeof(char *));

					*cnt += imported_cnt - 1;
					src[*cnt] = NULL;

					as_free(*(src + i)); /* free line which had contained import keyword */

					memcpy(src + i + imported_cnt, src + i + 1, (*cnt - (imported_cnt - 1) - (i + 1)) * sizeof(char *)); /* move existing to back of imported source */
					memcpy(src + i, imported_source, (imported_cnt) * sizeof(char *));


					as_free(imported_source);

					goto nextline;
				} else {
					as_abort_fmsg("%s: %d: filename does not properly provided", filename, i + 1);
				}
			} else {
				goto nextline;
			}
		}

		nextline:
			i++;
	}

	return src;
}

