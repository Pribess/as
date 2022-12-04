/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/err.h
*/

#ifndef ERR_H
#define ERR_H

#include <stdio.h>
#include <stdlib.h>

void as_exit(int code);
void as_abort();
void as_abort_msg(const char *msg);

#endif