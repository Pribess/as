/* SPDX-License-Identifier: MIT */
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

#include "arch/x86/x86.h"

int as_arch = ARCH_x86;
int as_format = 0; // give initial value after implementing output file formatter

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

	int proceeded = 0;

	while (argc--) {
		if ((*argv)[0] == '-') {
			if ((*argv)[1] != '-' && (*argv)[2] == 0x00) { /* single hyphen option */
				switch ((*argv)[1]) {
					case 'v': {
						if (argc || proceeded) as_abort_msg("too much arguments"); /* if some arguments still left or already proceeded */
						version();
						as_exit(EXIT_SUCCESS);
						break;
					}
					case 'h': {
						if (argc || proceeded) as_abort_msg("too much arguments"); /* if some arguments still left or already proceeded */
						help();
						as_exit(EXIT_SUCCESS);
						break;
					}
					default: goto err_unknown_option;
				}
			} else if ((*argv)[1] == '-') { /* double hyphen option */
				switch ((*argv)[2]) {
					case 'a': { /* arch */
						if (strncmp((const char *)(*argv + 2), "arch=", 5)) goto err_unknown_option;

						switch ((*argv)[7]) {
							case 'x':
								if (strcmp((const char *)(*argv + 7), "x86")) goto err_unknown_option;

								as_arch = ARCH_x86;
								break;
							default: goto err_unknown_arch;
						}
						break;
					}
					case 'f': { /* format */
						if (strncmp((const char *)(*argv + 2), "format=", 7)) goto err_unknown_option;

						switch ((*argv)[9]) {
							// formats...
							default: goto err_unknown_format;
						}
						break;
					}
					default: goto err_unknown_option;
				}
			} else { /* if option is too long */
				goto err_unknown_option;
			}

			argv++;
		} else { /* if it is input file */
			if (argc) /* if arguments still left */
				as_abort_msg("too much arguments");

			return *argv;
		}

		proceeded++;
	}

	/* if not returned on the upper loop */
	as_abort_msg("no input file");

	#define ERROR(name, index) \
		char *msg = malloc((sizeof("unknown : ") + strlen(name) + strlen(*argv + index)) * sizeof(char)); \
		sprintf(msg, "unknown %s: '%s'", name, *argv + index); \
		as_abort_msg(msg);

	err_unknown_option: {
		ERROR("option", 0);
	}

	err_unknown_arch: {
		ERROR("arch", 7);
	}

	err_unknown_format: {
		ERROR("format", 9);
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
	int i = 0;

	while (option_descriptions[i++]) {
		printf("%s\n", option_descriptions[i - 1]);
	}
}