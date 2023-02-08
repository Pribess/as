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

#include "file/file.h"
#include "alloc.h"

struct import_meta {
	const char *filename;
	size_t size;
	int imported_line; /* member which represent line of parent which imports this file */
	struct import_meta **children;
	int children_cnt;
	size_t children_cap;
};

char **as_preproc(const char *filename, char **src, int *cnt, struct import_meta *metadata);

#endif