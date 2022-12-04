/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/parser.c
*/

#include "parser.h"

char **tokenize(const char *src) {
	const char *str = src;
	int cnt = 1;
	while (str++ != 0x00) {
		if (*str == '\n') {
			cnt++;
		}
	}
	char **tokens = malloc(sizeof(char *) * cnt);

	tokens[0] = strtok((char *)src, "\n");
	for (int idx = 1 ; idx < cnt ; idx++) {
		tokens[idx] = strtok(NULL, "\n");
	}

	return tokens;
}
