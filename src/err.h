/* SPDX-License-Identifier: MIT */
/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/err.h
*/

#ifndef ERR_H
#define ERR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

struct err {
	int row;
};

void as_exit(int code);

void as_abort();
void as_abort_prefix(const char *prefix);

void as_abort_msg(const char *msg);
void as_abort_fmsg(const char *fmsg, ...);

void as_warn_fmsg(const char *fmsg, ...);

#endif