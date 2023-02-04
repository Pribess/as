/* SPDX-License-Identifier: MIT */
/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/alloc.c
*/

#include "alloc.h"

void *as_malloc(size_t size) {
    void *ptr;

    if (!(ptr = malloc(size))) {
        as_abort();
    }

    return ptr;
}

void *as_realloc(void *ptr, size_t size) {
    if (!(ptr = realloc(ptr, size))) {
        as_abort();
    }

    return ptr;
}

void as_free(void *ptr) {
    free(ptr);
}

void as_free_all(void **ptr) {
    int cnt = 0;
    while (ptr[cnt++]) {
        as_free(ptr[cnt - 1]);
    }
    
    as_free(ptr);
}