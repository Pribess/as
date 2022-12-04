/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/as.c
*/

#define AS_VERSION "0.01"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void parse_arg(int argc, char **argv);
void usage();
void version();
void help();

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "");

	parse_arg(argc, argv);

	// this must be at file part of as
	// FILE *fp;
	// if ((fp = fopen(*argv, "r")) == NULL) {
	//         printf("as: %s: %s\n", *argv, strerror(errno));
	//         return 1;
	// }

//     tokenize("xor eax, eax\nmov eax, 1\npush eax");

}

void parse_arg(int argc, char **argv) {
	argc--;
	argv++;
	
	if (argc < 1) {
			usage();
			exit(EXIT_FAILURE);
	}

	if ((*argv)[0] == '-') {
		switch ((*argv)[1]) {
			case 'v': {
				version();
				exit(EXIT_SUCCESS);
				break;
			}
			case 'h': {
				help();
				exit(EXIT_SUCCESS);
			}
		}
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