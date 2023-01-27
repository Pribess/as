/* SPDX-License-Identifier: MIT */
/*
		Copyright (C) 2022 Pribess (Heewon Cho)
		src/arch/x86/x86.h
*/

#ifndef X86_H
#define X86_H

#define ARCH_x86 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../../err.h"

struct x86_operand {
	enum {
		x86_operand_register,
		x86_operand_constant,
		x86_operand_reference
	} type;

	union {
		struct x86_operand_register {
			enum {
				#include "data/register.dat"
			} reg;
		} reg;

		struct x86_operand_constant {
			uint64_t data;
			int size;
		} constant;

		struct x86_operand_reference {
			struct x86_operand *ptr;
			int size;
		} reference;
	};
};

struct x86_line {
	enum {
		x86_line_directive,
		x86_line_label,
		x86_line_instruction
	} type;

	union {
		struct x86_line_directive {
			enum {
				x86_directive_extern,
				x86_directive_public,
				x86_directive_section
			} type;

			const char *argument;
		} directive;

		struct x86_line_label {
			const char *name;
		} label;

		struct x86_line_instruction {
			int opcode;
			struct x86_operand *operands;
			int oprdcnt;
		} instruction;

	} data;

	struct err err;
};

#endif