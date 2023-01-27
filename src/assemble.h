/* SPDX-License-Identifier: MIT */
/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/assemble.h
*/

#ifndef ASSEMBLE_H
#define ASSEMBLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "file/file.h"
#include "parser.h"

void assemble(const char *filename);

#endif