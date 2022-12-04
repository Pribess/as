/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/as.c
*/

#define AS_VERSION "0.01"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "file/file.h"

char *filename = NULL;

void init();
void parse_arg(int argc, char **argv);
void usage();
void version();
void help();

int main(int argc, char *argv[]) {

	init();
	parse_arg(argc, argv);

}

void init() {
	setlocale(LC_ALL, "");
}

void parse_arg(int argc, char **argv) {
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

			filename = *argv;
			return;
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
}

void usage() {
	printf("usage: as [options...] filename\n");
}

void version() {
	printf("as version %s (%s, %s)\n", AS_VERSION, __DATE__, __TIME__);
}

const char *option_descriptions[] = { 
	"-v\t\tprint version and compiled time then exit"
};

void help() {
	for (int i = 0 ; i < sizeof(option_descriptions) / sizeof(*option_descriptions) ; i++) {
		printf("%s\n", option_descriptions[i]);
	}
}