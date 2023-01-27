/* SPDX-License-Identifier: MIT */
/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/alloc.h
*/

#ifndef ALLOC_H
#define ALLOC_H

#include <stdlib.h>

#include "err.h"

void *as_malloc(size_t size);
void *as_realloc(void *ptr, size_t size);
void as_free(void *ptr);

#endif