/* SPDX-License-Identifier: MIT */
/*
	Copyright (C) 2022 Pribess (Heewon Cho)
	src/parser.h
*/

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "file/file.h"
#include "alloc.h"

struct metadata {
	const char *filename;
	size_t size;
	int imported_line; /* member which represent line of parent which imports this file */
	struct metadata **children;
	int children_cnt;
	size_t children_cap;
};

struct equ {
	const char *symbol;
	const char *value;
	bool purged;
};

char **as_preproc(char **src, int *cnt, struct metadata *src_metadata);
char **as_preproc_import(char **src, int *cnt, struct metadata *src_metadata, char *error_annotation);

char *as_resolve_actual_row(char **src, int row, struct metadata *src_metadata);
bool as_is_banned_keyword(char *keyword);

#endif