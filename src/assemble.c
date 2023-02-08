/* SPDX-License-Identifier: MIT */
/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/assemble.c
*/

#include "assemble.h"

extern int as_arch;

// static void test(const char *parent, struct import_meta *metadata) {
// 	for (int i = 0 ; i < metadata->children_cnt ; i++) {
// 		printf("parent: %s     index: %d     imported filename: %s     imported line: %d     size: %d\n",
// 			parent,
// 			i,
// 			metadata->children[i]->filename,
// 			metadata->children[i]->imported_line,
// 			metadata->children[i]->size
// 		);
// 		test(metadata->children[i]->filename, metadata->children[i]);
// 	}
// }

void assemble(const char *filename) {

	FILE *stream = as_openfile(filename);

	int cnt;
	char **src = as_readall(stream, &cnt);
	
	struct import_meta metadata;
	metadata.filename = filename;
	metadata.imported_line = 0;
	metadata.size = cnt;
	metadata.children = as_malloc((4) * sizeof(struct import_meta *));
	metadata.children_cap = 4;
	metadata.children_cnt = 0;

	src = as_preproc(filename, src, &cnt, &metadata);

	// test(filename, &metadata);

	switch (as_arch) {
		case ARCH_x86: {
			break;
		}

		default: {
			as_abort_msg("undefined architecture");
		}
	}

} 