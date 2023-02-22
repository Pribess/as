/* SPDX-License-Identifier: MIT */
/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/assemble.c
*/

#include "assemble.h"

extern int as_arch;

// static void test(const char *parent, struct metadata *metadata) {
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
	
	struct metadata src_metadata;
	src_metadata.filename = filename;
	src_metadata.imported_line = 0;
	src_metadata.size = cnt;
	src_metadata.children = as_malloc((4) * sizeof(struct metadata *));
	src_metadata.children_cap = 4;
	src_metadata.children_cnt = 0;

	src = as_preproc(filename, src, &cnt, &src_metadata);

	// test(filename, &metadata);

	switch (as_arch) {
		case ARCH_x86: {
			struct x86_line *lines = as_x86_parse(src, cnt, &src_metadata);
			break;
		}

		default: {
			as_abort_msg("undefined architecture");
		}
	}

} 