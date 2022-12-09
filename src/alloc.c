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