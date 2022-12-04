/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/file/file.h
*/

#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <string.h>

#include "../err.h"

FILE *as_open_file(const char *filename);

#endif