/* SPDX-License-Identifier: MIT */
/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/file/file.h
*/

#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <string.h>

#include "../alloc.h"
#include "../err.h"

FILE *as_openfile(const char *filename);
char *as_readline(FILE *stream);
char **as_readall(FILE *stream, int *cnt);

#endif