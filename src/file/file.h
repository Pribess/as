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

#endif