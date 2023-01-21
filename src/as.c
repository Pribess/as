/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/as.c
*/

#define AS_VERSION "0.01"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#include "assemble.h"
#include "file/file.h"

void init();
const char *parse_arg(int argc, char **argv);
void usage();
void version();
void help();

int main(int argc, char *argv[]) {

	init();
	assemble(parse_arg(argc, argv));

}

void init() {
	setlocale(LC_ALL, "");
}

const char *parse_arg(int argc, char **argv) {
	argc--;
	argv++;
	
	if (argc < 1) {
			usage();
			as_exit(EXIT_FAILURE);
	}

	while (argc--) {
		if ((*argv)[0] == '-') {
			if ((*argv)[2] == 0x00) {
				switch ((*argv)[1]) {
					case 'v': {
						version();
						as_exit(EXIT_SUCCESS);
						break;
					}
					case 'h': {
						help();
						as_exit(EXIT_SUCCESS);
						break;
					}
					default: goto err; /* if option does not exists */
				}
			} else { /* if option is too long */
				goto err;
			}
		} else { /* if it is input file */
			if (argc) /* if arguments still left */
				as_abort_msg("too much arguments");

			return *argv;
		}
		argv++;
	}

	/* if not returned on the upper loop */
	as_abort_msg("no input file");

	err: {
		char *msg = malloc(sizeof("unknown option: ") + strlen(*argv));
		sprintf(msg, "unknown option: '%s'", *argv);
		as_abort_msg(msg);
		free(msg);
	}

	/* control flow never reaches here */
	return NULL;
}

void usage() {
	printf("usage: as [options...] filename\n");
}

void version() {
	printf("as version %s (%s, %s)\n", AS_VERSION, __DATE__, __TIME__);
}

const char *option_descriptions[] = { 
	"-v\t\tprint version and compiled time then exit",
	NULL
};

void help() {
	int i = -1;

	while (option_descriptions[++i]) {
		printf("%s\n", option_descriptions[i]);
	}
}