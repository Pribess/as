/* SPDX-License-Identifier: MIT */
/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/arch/x86/x86.c
*/

#include "x86.h"

struct x86_line *as_x86_parse(char **src, int cnt, struct metadata *src_metadata) {
	int i = 0;

	while (src[i]) {
		printf("%s\n", src[i]);

		i++;
	}
}