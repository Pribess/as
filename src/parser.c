/* SPDX-License-Identifier: MIT */
/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/parser.c
*/

#include "parser.h"

char **as_preproc(char **src, int *cnt, struct metadata *src_metadata) {
	char *error_annotation = as_malloc((1) * sizeof(char *));
	error_annotation[0] = 0x00;
	src = as_preproc_import(src, cnt, src_metadata, error_annotation);

	size_t equtable_size = 0;
	struct equ *equtable = as_malloc((equtable_size) * sizeof(struct equ *));

	int i = 0;

	/* iterate lines */
	while (src[i]) {
		int j = 0;
		
		/* skip white spaces */
		while (src[i][j]) {
			if (src[i][j] != ' ' && src[i][j] != '\t') break;
			if (!src[i][j]) goto nextline;
			j++;
		}

		while (src[i][j]) {
			switch (src[i][j]) {
				case 'p': case 'P': { /* purge */

					break;
				}
				case 'r': case 'R': { /* repeat */
				
					break;
				}
				case 'm': case 'M': { /* macro */
				
					break;
				}
				case 'i': case 'I': {/* if */
				
					break;
				}
				default: {
					int k = 0;

					/* skip first token or get symbol length (if this line is for equ directive) */
					int symbol_length = 0;
					while (src[i][j + k] != ' ' && src[i][j + k] != '\t') {
						if (!src[i][j + k]) goto nextline;
						symbol_length++;
						k++;
					}

					/* skip whitespaces between symbol and 'equ' directive */	
					while (src[i][j + k] == ' ' || src[i][j + k] == '\t') {
						if (!src[i][j + k]) goto nextline;
						k++;
					}
					
					/* equ */
					if (!strncmp(src[i] + j + k, "equ", 3)) {
						k += 3;

						char *symbol = as_malloc((symbol_length + 1) * sizeof(char));
						symbol[symbol_length] = 0x00;

						/* read symbol here */
						int l = 0;
						while (src[i][j + l] != ' ' && src[i][j + l] != '\t') {
							symbol[l] = src[i][j + l];
							l++;
						}

						/* check if whitespaces exists between 'equ' directive and value */
						if (src[i][j + k] != ' ' && src[i][j + k] != '\t') {
							goto nextline;
						}
						/* and skip those whitespaces */
						while (src[i][j + k] == ' ' || src[i][j + k] == '\t') {
							if (!src[i][j + k]) goto nextline;
							k++;
						}

						/* get value length */
						int value_length = 0;
						while (src[i][j + k] != ' ' && src[i][j + k] != '\t') {
							if (!src[i][j + k]) break;
							value_length++;
							k++;
						}

						char *value = as_malloc((value_length + 1) * sizeof(char));
						value[value_length] = 0x00;

						/* read value here */
						l = 0;
						while (src[i][j + k - value_length + l] != ' ' && src[i][j + k - value_length + l] != '\t') {
							if (!src[i][j + k - value_length + l]) break;
							value[l] = src[i][j + k - value_length + l];
							l++;
						}

						/* check if other characters left */
						while (src[i][j + k] == ' ' || src[i][j + k] == '\t') {
							k++;
						}
						if (src[i][j + k]) {
							// 메타데이타 참조해서 임포트 위치 구하기
							// as_warn_fmsg("%s:%d: warning: trailing garbage after equ directive ignored", src_metadata->filename, i + 1);
						}

						if (as_is_banned_keyword(symbol)) {

						}
						if (as_is_banned_keyword(value)) {

						}

						equtable_size++;
						equtable = as_realloc(equtable, (equtable_size) * sizeof(struct equ *));
						equtable[equtable_size - 1].symbol = symbol;
						equtable[equtable_size - 1].value = value;
						equtable[equtable_size - 1].purged = false;

						goto nextline;
					} else { /* substitute if symbol which is defined before exists */

					};

					break;
				}
			}

			j++;
		}

		nextline:
			i++;
	}

	return src;
}

char **as_preproc_import(char **src, int *cnt, struct metadata *src_metadata, char *error_annotation) { /* error_annotation is used for printing  */
	int i = 0;

	/* iterate lines */
	while (src[i]) {
		int j = 0;

		/* iterate characters of line */
		while (src[i][j]) {
			if (src[i][j] == ' ' || src[i][j] == '\t') {
				j++;
				continue;

			/* skip line if meets comment */
			} else if (src[i][j] == '|') { 
				goto nextline;
			} else if (src[i][j] == 'i' || src[i][j] == 'I') {

				const char *directive = src[i][j] == 'i' ? "import " : "IMPORT ";
				if (strncmp(src[i] + j, directive, strlen(directive))) {
					goto nextline;
				}
				j += strlen(directive);
				
				size_t size = 16;
				char *imported_filename = as_malloc((size) * sizeof(char));

				/* if filename is normaly provided */
				if (src[i][j++] == '"') {
					int k = 0;

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
							as_warn_fmsg("%s:%d: warning: trailing garbage after import directive ignored", src_metadata->filename, i + 1);
							break;
						}
						j++;
					}

					/* convert to relative file path of file which is processing */
					int l = strlen(src_metadata->filename) - 1;
					while (!(l < 0) && src_metadata->filename[l--] != '/'); /* count last component of path */
					/* correct not intended decreases (postfix decrement and length) */
					if (l == -1) l++;
					else l += 2;
					
					/* 
						strlen("example/of/path/") + strlen("imported/filename")
						equals to
						strlen("example/of/path/imported/filename")
					*/
					char *relative_filename = malloc((l + strlen(imported_filename) + 1) * sizeof(char));
					
					strncpy(relative_filename, src_metadata->filename, l);
					strcpy(relative_filename + l, imported_filename);

					/* open file and append it to file which is processing */
					if (!as_file_exists(relative_filename)) {
						as_abort_fmsg("%s: %d: '%s': No such file or directory", src_metadata->filename, i + 1, relative_filename);
					}

					FILE *stream = as_openfile(relative_filename);

					int imported_cnt;
					char **imported_source = as_readall(stream, &imported_cnt);

					/* add import meta data to print line which has error in other process */
					if (src_metadata->children_cap < src_metadata->children_cnt + 1) {
						src_metadata->children_cap *= 2;
						src_metadata->children = as_realloc(src_metadata->children, (src_metadata->children_cap) * sizeof(struct metadata *));
					}
					src_metadata->children[src_metadata->children_cnt] = malloc(sizeof(struct metadata));
					src_metadata->children[src_metadata->children_cnt]->filename = imported_filename;
					size_t pushed_offset = 0;
					for (int n = 0 ; n < src_metadata->children_cnt ; n++) {
						pushed_offset += src_metadata->children[n]->size - 1;
					}
					src_metadata->children[src_metadata->children_cnt]->imported_line = i + 1 - pushed_offset;
					src_metadata->children[src_metadata->children_cnt]->size = imported_cnt;
					src_metadata->children[src_metadata->children_cnt]->children = as_malloc((4) * sizeof(struct metadata *));
					src_metadata->children[src_metadata->children_cnt]->children_cap = 4;
					src_metadata->children[src_metadata->children_cnt]->children_cnt = 0;

					error_annotation = as_malloc(strlen(error_annotation) + sizeof("imported from ::\n") + strlen(src_metadata->filename) + (log10(i + 1) + 1));
					sprintf(error_annotation, "%simported from %s:%d:\n", error_annotation, src_metadata->filename, i + 1);

					as_preproc_import(imported_source, &imported_cnt, src_metadata->children[src_metadata->children_cnt], error_annotation);

					as_free(error_annotation);

					src_metadata->children_cnt++;

					src = as_realloc(src, (*cnt - 1 + imported_cnt + 1) * sizeof(char *));

					*cnt += imported_cnt - 1;
					src[*cnt] = NULL;

					as_free(*(src + i)); /* free line which had contained import keyword */

					memcpy(src + i + imported_cnt, src + i + 1, (*cnt - (imported_cnt - 1) - (i + 1)) * sizeof(char *)); /* move existing to back of imported source */
					memcpy(src + i, imported_source, (imported_cnt) * sizeof(char *));


					as_free(imported_source);

					goto nextline;
				} else {
					as_abort_fmsg("%s: %d: filename does not properly provided", src_metadata->filename, i + 1);
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

char *as_resolve_actual_row(char **src, int row, struct metadata *src_metadata) {
	
}

bool as_is_banned_keyword(char *keyword) {
	const char *banned_keyword[] = {
		"extern",
		"public",
		"section",
		"offset",
		"align",

		"import",
		"equ",
		"purge",
		"repeat",
		"macro",
		"defined",
		"if",
		"else",
		"elseif",
		"endif"
	};

	for (int i = 0 ; i < sizeof(banned_keyword) / sizeof(const char *) ; i++) {
		if (!strncmp(keyword, banned_keyword[i], strlen(banned_keyword[i]))) {
			return true;
		}
	}

	return false;
}