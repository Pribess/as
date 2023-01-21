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

char **as_preproc(const char *filename, char **src, int *cnt);

#endif