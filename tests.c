#include "tests.h"

/* Batch tests */

static uint16_t test_address = 0xFF00;
static uint8_t test_r8_1 = B;
static uint8_t test_r8_2 = D;
static uint8_t test_r16 = BC;
static uint8_t test_uint8 = 0xF0;
static uint16_t test_uint16 = 0xC0DE;

bool test_all(System *system, bool print_all) {
	uint16_t sum = 0;
	/* 8-bit instructions */
	sum += test_8bit(system, print_all);

	/* 16-bit instructions*/
	sum += test_16bit(system, print_all);

	/* Bit operations instructions */
	sum += test_bit(system, print_all);

	/* Bit shift instructions */
	sum += test_bitshift(system, print_all);

	/* Load instructions */
	sum += test_load(system, print_all);

	/* Jumps and Subroutines */
	sum += test_jumps_subtoutines(system, print_all);

	/* Stack operations instructions */
	sum += test_stack(system, print_all);

	/* Miscellaneous Instructions */
	test_misc(system, print_all);

	/* Result */
	if (sum) {
		printf("\nTotal of %hu failed tests.\n", sum);
	} else {
		printf("\nTotal:\nNo failures!\n");
	}
}

bool test_8bit(System *system, bool print_all) {
	uint16_t sum = 0;
	printf("\n8-bit instructions test.\n");
	/* 8-bit instructions */
	for (uint32_t i = 0; i <= 0xFF; i++) {
		if (print_all)
			printf("i: %hhu\n", i);
		sum += test_ADC_A_r8(system, i, print_all);
		sum += test_ADC_A_HL(system, i, print_all);
		sum += test_ADC_A_n8(system, i, print_all);
		sum += test_ADD_A_r8(system, i, print_all);
		sum += test_ADD_A_HL(system, i, print_all);
		sum += test_ADD_A_n8(system, i, print_all);
		sum += test_AND_A_r8(system, i, print_all);
		sum += test_AND_A_HL(system, i, print_all);
		sum += test_AND_A_n8(system, i, print_all);
		sum += test_CP_A_r8(system, i, print_all);
		sum += test_CP_A_HL(system, i, print_all);
		sum += test_CP_A_n8(system, i, print_all);
		sum += test_OR_A_r8(system, i, print_all);
		sum += test_OR_A_HL(system, i, print_all);
		sum += test_OR_A_n8(system, i, print_all);
		sum += test_SBC_A_r8(system, i, print_all);
		sum += test_SBC_A_HL(system, i, print_all);
		sum += test_SBC_A_n8(system, i, print_all);
		sum += test_SUB_A_r8(system, i, print_all);
		sum += test_SUB_A_HL(system, i, print_all);
		sum += test_SUB_A_n8(system, i, print_all);
		sum += test_XOR_A_r8(system, i, print_all);
		sum += test_XOR_A_HL(system, i, print_all);
		sum += test_XOR_A_n8(system, i, print_all);
	}
	sum += test_DEC_r8(system, print_all);
	sum += test_DEC_HL(system, print_all);
	sum += test_INC_r8(system, print_all);
	sum += test_INC_HL(system, print_all);
	/* Result */
	if (sum) {
		printf("\n8-bit instructions:\nTotal of %hu failed runs.\n",
		       sum);
	} else {
		printf("\n8-bit instructions:\nNo failures!\n");
	}
	return sum;
}

bool test_16bit(System *system, bool print_all) {
	uint16_t sum = 0;
	/* They are very long */
	printf("\n16-bit instructions test.\n");
	for (uint32_t i = 0; i <= 0xFFFF; i++) {
		sum += test_ADD_HL_r16(system, i, print_all);
	}
	sum += test_DEC_r16(system, print_all);
	sum += test_INC_r16(system, print_all);

	/* Result */
	if (sum) {
		printf("\n16-bit instructions:\nTotal of %hu failed tests.\n",
		       sum);
	} else {
		printf("\n16-bit instructions:\nNo failures!\n");
	}
	return sum;
}

bool test_bit(System *system, bool print_all) {
	uint16_t sum = 0;
	printf("\nBit instructions test.\n");
	for (uint32_t i = 0; i <= 0xFF; i++) {
		sum += test_BIT_u3_r8(system, i, print_all);
		sum += test_BIT_u3_HL(system, i, print_all);
		sum += test_RES_u3_r8(system, i, print_all);
		sum += test_RES_u3_HL(system, i, print_all);
		sum += test_SET_u3_r8(system, i, print_all);
		sum += test_SET_u3_HL(system, i, print_all);
		sum += test_SWAP_r8(system, i, print_all);
		sum += test_SWAP_HL(system, i, print_all);
	}

	/* Result */
	if (sum) {
		printf("\nBit instructions:\nTotal of %hu failed tests.\n",
		       sum);
	} else {
		printf("\nBit instructions:\nNo failures!\n");
	}
	return sum;
}

bool test_bitshift(System *system, bool print_all) {
	uint16_t sum = 0;
	printf("\nBit shift instructions test.\n");

	for (uint16_t i = 0; i <= 0xFF; i++) {
		sum += test_RL_r8(system, i, print_all);
		sum += test_RL_HL(system, i, print_all);
		sum += test_RLA(system, i, print_all);
		sum += test_RLC_r8(system, i, print_all);
		sum += test_RLC_HL(system, i, print_all);
		sum += test_RLCA(system, i, print_all);
		sum += test_RR_r8(system, i, print_all);
		sum += test_RR_HL(system, i, print_all);
		sum += test_RRA(system, i, print_all);
		sum += test_RRC_r8(system, i, print_all);
		sum += test_RRC_HL(system, i, print_all);
		sum += test_RRCA(system, i, print_all);
		sum += test_SLA_r8(system, i, print_all);
		sum += test_SLA_HL(system, i, print_all);
		sum += test_SRA_r8(system, i, print_all);
		sum += test_SRA_HL(system, i, print_all);
		sum += test_SRL_r8(system, i, print_all);
		sum += test_SRL_HL(system, i, print_all);
	}

	/* Result */
	if (sum) {
		printf(
		    "\nBit shift instructions:\nTotal of %hu failed tests.\n",
		    sum);
	} else {
		printf("\nBit shift instructions:\nNo failures!\n");
	}
	return sum;
}

bool test_jumps_subtoutines(System *system, bool print_all) {
	uint16_t sum = 0;
	printf("\nJumps and subroutines instructions test.\n");

	for (uint32_t i = 0; i <= 0x8000; i++) {
		sum += test_JP_HL(system, i, print_all);
		sum += test_JP_n16(system, i, print_all);
		sum += test_JP_cc_n16(system, i, print_all);
		sum += test_JR_n16(system, i, print_all);
		sum += test_JR_cc_n16(system, i, print_all);
		sum += test_RET(system, i, print_all);
		sum += test_RET_cc(system, i, print_all);
	}

	/* Result */
	if (sum) {
		printf("\nJumps and subroutines instructions:\nTotal of %hu "
		       "failed tests.\n",
		       sum);
	} else {
		printf("\nJumps and subroutines instructions:\nNo failures!\n");
	}
	return sum;
}

bool test_load(System *system, bool print_all) {
	uint16_t sum = 0;
	printf("\nLoad instructions test.\n");

	sum += test_LD_r8_r8(system, test_uint8, print_all);
	sum += test_LD_r8_n8(system, test_uint8, print_all);
	sum += test_LD_r16_n16(system, test_uint16, print_all);
	sum += test_LD_HL_r8(system, test_uint8, print_all);
	sum += test_LD_HL_n8(system, test_uint8, print_all);
	sum += test_LD_r8_HL(system, test_uint8, print_all);
	sum += test_LD_r16_A(system, test_uint8, print_all);
	sum += test_LD_n16_A(system, test_uint8, print_all);
	sum += test_LDH_n8_A(system, test_uint8, print_all);
	sum += test_LDH_C_A(system, test_uint8, print_all);
	sum += test_LD_A_r16(system, test_uint8, print_all);
	sum += test_LD_A_n16(system, test_uint8, print_all);
	sum += test_LDH_A_n8(system, test_uint8, print_all);
	sum += test_LDH_A_C(system, test_uint8, print_all);
	sum += test_LD_HLI_A(system, test_uint8, print_all);
	sum += test_LD_HLD_A(system, test_uint8, print_all);
	sum += test_LD_A_HLI(system, test_uint8, print_all);
	sum += test_LD_A_HLD(system, test_uint8, print_all);

	/* Result */
	if (sum) {
		printf("\nLoad instructions:\nTotal of %hu failed tests.\n",
		       sum);
	} else {
		printf("\nLoad instructions:\nNo failures!\n");
	}
	return sum;
}

bool test_stack(System *system, bool print_all) {
	uint16_t sum = 0;
	/* They are somewhat long too */
	printf("\nStack operations instructions test.\n");
	for (uint32_t i = 0; i <= 0xFFFF; i++) {
		sum += test_ADD_HL_SP(system, i, print_all);
		sum += test_ADD_SP_e8(system, i, print_all);
		sum += test_DEC_SP(system, i, print_all);
		sum += test_INC_SP(system, i, print_all);
		sum += test_LD_SP_n16(system, i, print_all);
		sum += test_LD_n16_SP(system, i, print_all);
		sum += test_LD_HL_SP_e8(system, i, print_all);
		sum += test_LD_SP_HL(system, i, print_all);
		sum += test_POP_r16(system, i, print_all);
		sum += test_PUSH_r16(system, i, print_all);
	}

	/* Result */
	if (sum) {
		printf("\nStack operations instructions:\nTotal of %hu failed "
		       "tests.\n",
		       sum);
	} else {
		printf("\nStack operations instructions:\nNo failures!\n");
	}
	return sum;
}

bool test_misc(System *system, bool print_all) {
	uint16_t sum = 0;
	printf("\nMiscellaneous instructions test.\n");

	sum += test_CCF(system, print_all);
	sum += test_CPL(system, test_uint8, print_all);
	// I refuse to write a test for DAA

	/* Result */
	if (sum) {
		printf("\nMiscellaneous instructions:\nTotal of %hu failed "
		       "tests.\n",
		       sum);
	} else {
		printf("\nMiscellaneous instructions:\nNo failures!\n");
	}
	return sum;
}
/* 8-bit arithmetic and logic instructions */

bool test_ADC_A_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("ADC A,r8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->registers[test_r8_1] = test_value;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		ADC_A_r8(system, test_r8_1);
		uint16_t res = (uint8_t)test_value + i;
		zero = !res;
		sub = 0;
		if (res > 0xFFU) {
			carry = true;
		} else {
			carry = false;
		}
		if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) {
			halfcarry = true;
		} else {
			halfcarry = false;
		}
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("ADC A,r8: %hhu (no carry) passed\n", i);
		} else {
			printf(
			    "ADC A,r8: %hhu %hhu (no carry) failed\nExpected: "
			    "%u z: %u n: %u "
			    "hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			    i, test_value, res, zero, sub, halfcarry, carry,
			    system->registers[A], GET_CPU_FLAG(ZERO),
			    GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			    GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->registers[test_r8_1] = test_value;
		SET_CPU_FLAG(HALFCARRY, false);
		SET_CPU_FLAG(CARRY, true);
		ADC_A_r8(system, test_r8_1);
		uint16_t res = (uint8_t)test_value + i + 1;
		if (res > 0xFF) {
			carry = true;
		} else {
			carry = false;
		}
		if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) {
			halfcarry = true;
		} else {
			halfcarry = false;
		}
		zero = !res;
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("ADC A,r8: %hhu (carry) passed\n", i);
		} else {
			printf("ADC A,r8: %hhu %hhu (carry) failed\nExpected: "
			       "%u z: %u n: %u hc: "
			       "%u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_ADC_A_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("ADC A,[HL] test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->memory[test_address] = test_value;
		SET_16BIT_REGISTER(HL, test_address);
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		ADC_A_HL(system);
		uint16_t res = (uint8_t)test_value + i;
		zero = !res;
		sub = 0;
		// Calcuating flags
		if (res > 0xFF) {
			carry = true;
		} else {
			carry = false;
		}
		if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) {
			halfcarry = true;
		} else {
			halfcarry = false;
		}

		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("ADC A,[HL]: %hhu (no carry) passed\n",
				       i);
		} else {
			printf("ADC A,[HL]: %hhu %hhu (no carry) "
			       "failed\nExpected: %u z: %u n: "
			       "%u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: "
			       "%u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->memory[test_address] = test_value;
		SET_16BIT_REGISTER(HL, test_address);
		SET_CPU_FLAG(CARRY, true);
		SET_CPU_FLAG(HALFCARRY, false);
		ADC_A_HL(system);
		uint16_t res = (uint8_t)test_value + i + 1;
		zero = !res;
		sub = 0;
		if (res > 0xFF) {
			carry = true;
		} else {
			carry = false;
		}
		if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) {
			halfcarry = true;
		} else {
			halfcarry = false;
		}
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("ADC A,[HL]: %hhu (carry) passed\n", i);
		} else {
			printf(
			    "ADC A,[HL]: %hhu %hhu (carry) failed\nExpected: "
			    "%u z: %u n: %u "
			    "hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			    i, test_value, res, zero, sub, halfcarry, carry,
			    system->registers[A], GET_CPU_FLAG(ZERO),
			    GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			    GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_ADC_A_n8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("ADC A,n8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		ADC_A_n8(system, test_value);
		uint16_t res = (uint8_t)test_value + i;
		if (res > 0xFF) {
			carry = true;
		} else {
			carry = false;
		}
		zero = !res;
		sub = 0;
		if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) {
			halfcarry = true;
		} else {
			halfcarry = false;
		}
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("ADC A,n8: %hhu (no carry) passed\n", i);
		} else {
			printf(
			    "ADC A,n8: %hhu %hhu (no carry) failed\nExpected: "
			    "%u z: %u n: %u "
			    "hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			    i, test_value, res, zero, sub, halfcarry, carry,
			    system->registers[A], GET_CPU_FLAG(ZERO),
			    GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			    GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		SET_CPU_FLAG(CARRY, true);
		SET_CPU_FLAG(HALFCARRY, false);
		ADC_A_n8(system, test_value);
		uint16_t res = (uint8_t)test_value + i + 1;
		zero = !res;
		sub = 0;
		if (res > 0xFF) {
			carry = true;
		} else {
			carry = false;
		}
		if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) {
			halfcarry = true;
		} else {
			halfcarry = false;
		}
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("ADC A,n8: %hhu (carry) passed\n", i);
		} else {
			printf("ADC A,n8: %hhu %hhu (carry) failed\nExpected: "
			       "%u z: %u n: %u hc: "
			       "%u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_ADD_A_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("ADD A,r8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->registers[test_r8_1] = test_value;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		ADD_A_r8(system, test_r8_1);
		uint16_t res = (uint8_t)test_value + i;
		zero = !res;
		sub = 0;
		if (res > 0xFF) {
			carry = true;
		} else {
			carry = false;
		}
		if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) {
			halfcarry = true;
		} else {
			halfcarry = false;
		}
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("ADD A,r8: %hhu passed\n", i);
		} else {
			printf("ADD A,r8: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_ADD_A_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("ADD A,[HL] test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->memory[0xFFF] = test_value;
		system->registers[H] = 0x0F;
		system->registers[L] = 0xFF;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		ADD_A_HL(system);
		uint16_t res = (uint8_t)test_value + i;
		zero = !res;
		sub = 0;
		if (res > 0xFF) {
			carry = true;
		} else {
			carry = false;
		}
		if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) {
			halfcarry = true;
		} else {
			halfcarry = false;
		}
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("ADD A,[HL]: %hhu passed\n", i);
		} else {
			printf("ADD A,[HL]: %hhu %hhu failed\nExpected: %u z: "
			       "%u n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_ADD_A_n8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("ADD A,n8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		ADD_A_n8(system, test_value);
		uint16_t res = (uint8_t)test_value + i;
		zero = !res;
		sub = 0;
		if (res > 0xFF) {
			carry = true;
		} else {
			carry = false;
		}
		if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) {
			halfcarry = true;
		} else {
			halfcarry = false;
		}
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("ADD A,n8: %hhu passed\n", i);
		} else {
			printf("ADD A,n8: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_AND_A_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("AND A,r8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->registers[test_r8_1] = test_value;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		AND_A_r8(system, test_r8_1);
		uint16_t res = (uint8_t)test_value & i;
		zero = !res;
		sub = 0;
		carry = false;
		halfcarry = true;
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("AND A,r8: %hhu (no carry) passed\n", i);
		} else {
			printf("AND A,r8: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_AND_A_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("AND A,[HL] test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->memory[test_address] = test_value;
		SET_16BIT_REGISTER(HL, test_address);
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		AND_A_HL(system);
		uint16_t res = (uint8_t)test_value & i;
		zero = !res;
		sub = 0;
		carry = false;
		halfcarry = true;
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("ADC A,[HL]: %hhu passed\n", i);
		} else {
			printf("AND A,[HL]: %hhu %hhu failed\nExpected: %u z: "
			       "%u n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_AND_A_n8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("AND A,n8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		AND_A_n8(system, test_value);
		uint16_t res = (uint8_t)test_value & i;
		zero = !res;
		sub = 0;
		carry = false;
		halfcarry = true;
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("ADC A,n8: %hhu passed\n", i);
		} else {
			printf("AND A,n8: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_CP_A_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("CP A,r8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->registers[test_r8_1] = test_value;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		CP_A_r8(system, test_r8_1);
		uint16_t res = (uint8_t)i - test_value;
		zero = !res;
		sub = 1;
		if (i < test_value) {
			carry = true;
		} else {
			carry = false;
		}
		halfcarry = (i & 0xF) < (test_value & 0xF);
		if (carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("CP A,r8: %hhu passed\n", i);
		} else {
			printf("CP A,r8: %hhu %hhu failed\nExpected: z: %u n: "
			       "%u hc: %u c: %u, "
			       "got: z: %u n: %u hc: %u c: %u\n",
			       i, test_value, zero, sub, halfcarry, carry,
			       GET_CPU_FLAG(ZERO), GET_CPU_FLAG(SUB),
			       GET_CPU_FLAG(HALFCARRY), GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_CP_A_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("CP A,HL test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->memory[test_address] = test_value;
		SET_16BIT_REGISTER(HL, test_address);
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		CP_A_HL(system);
		uint16_t res = (uint8_t)i - test_value;
		zero = !res;
		sub = 1;
		if (i < test_value) {
			carry = true;
		} else {
			carry = false;
		}
		halfcarry = (i & 0xF) < (test_value & 0xF);

		if (carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("CP A,[HL]: %hhu passed\n", i);
		} else {
			printf("CP A,[HL]: %hhu %hhu failed\nExpected: z: %u "
			       "n: %u hc: %u c: %u, "
			       "got: z: %u n: %u hc: %u c: %u\n",
			       i, test_value, zero, sub, halfcarry, carry,
			       GET_CPU_FLAG(ZERO), GET_CPU_FLAG(SUB),
			       GET_CPU_FLAG(HALFCARRY), GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_CP_A_n8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("CP A,n8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		CP_A_n8(system, test_value);
		uint16_t res = (uint8_t)i - test_value;
		zero = !res;
		sub = 1;
		if (i < test_value) {
			carry = true;
		} else {
			carry = false;
		}
		halfcarry = (i & 0xF) < (test_value & 0xF);

		if (carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("CP A,r8: %hhu passed\n", i);
		} else {
			printf("CP A,n8: %hhu %hhu failed\nExpected: z: %u n: "
			       "%u hc: %u c: %u, "
			       "got: z: %u n: %u hc: %u c: %u\n",
			       i, test_value, zero, sub, halfcarry, carry,
			       GET_CPU_FLAG(ZERO), GET_CPU_FLAG(SUB),
			       GET_CPU_FLAG(HALFCARRY), GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_DEC_r8(System *system, bool print_all) {
	if (print_all)
		printf("DEC r8 test:\n");
	bool failed = false;
	bool sub = false;
	bool zero = false;
	bool halfcarry = false;
	bool carry = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[test_r8_1] = i;
		SET_CPU_FLAG(SUB, false);
		SET_CPU_FLAG(HALFCARRY, false);
		SET_CPU_FLAG(ZERO, false);
		carry = GET_CPU_FLAG(CARRY);
		DEC_r8(system, test_r8_1);
		uint8_t res = i - 1;
		zero = res == 0;
		halfcarry = ((res)&0xF == 0b1111);
		sub = true;
		if ((uint8_t)system->registers[test_r8_1] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("DEC r8: %hhu passed\n", i);
		} else {
			printf("DEC r8: %hhu failed\nExpected: %u z: %u n: %u "
			       "hc: %u c: %u, got: "
			       "%u z: %u n: %u hc: %u c: %u\n",
			       i, res, zero, sub, halfcarry, carry,
			       system->registers[test_r8_1], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_DEC_HL(System *system, bool print_all) {
	if (print_all)
		printf("DEC r8 test:\n");
	bool failed = false;
	bool sub = false;
	bool zero = false;
	bool halfcarry = false;
	bool carry = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->memory[test_address] = i;
		SET_16BIT_REGISTER(HL, test_address);
		SET_CPU_FLAG(SUB, false);
		SET_CPU_FLAG(HALFCARRY, false);
		SET_CPU_FLAG(ZERO, false);
		carry = GET_CPU_FLAG(CARRY);
		DEC_HL(system);
		uint8_t res = i - 1;
		zero = res == 0;
		halfcarry = ((res)&0xF == 0b1111);
		sub = true;
		if ((uint8_t)system->memory[test_address] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("DEC [HL]: %hhu passed\n", i);
		} else {
			printf("DEC [HL]: %hhu failed\nExpected: %u z: %u n: "
			       "%u hc: %u c: %u, "
			       "got: %u z: %u n: %u hc: %u c: %u\n",
			       i, res, zero, sub, halfcarry, carry,
			       system->memory[test_address], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_INC_r8(System *system, bool print_all) {
	if (print_all)
		printf("INC r8 test:\n");
	bool failed = false;
	bool sub = false;
	bool zero = false;
	bool halfcarry = false;
	bool carry = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[test_r8_1] = i;
		SET_CPU_FLAG(SUB, false);
		SET_CPU_FLAG(HALFCARRY, false);
		SET_CPU_FLAG(ZERO, false);
		carry = GET_CPU_FLAG(CARRY);
		INC_r8(system, test_r8_1);
		uint8_t res = i + 1;
		zero = res == 0;
		halfcarry = ((res - 1) & 0xF == 0b1111);
		sub = false;
		if ((uint8_t)system->registers[test_r8_1] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("INC r8: %hhu passed\n", i);
		} else {
			printf("INC r8: %hhu failed\nExpected: %u z: %u n: %u "
			       "hc: %u c: %u, got: "
			       "%u z: %u n: %u hc: %u c: %u\n",
			       i, res, zero, sub, halfcarry, carry,
			       system->registers[test_r8_1], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_INC_HL(System *system, bool print_all) {
	if (print_all)
		printf("INC [HL] test:\n");
	bool failed = false;
	bool sub = false;
	bool zero = false;
	bool halfcarry = false;
	bool carry = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		/* Default values */
		system->memory[test_address] = i;
		SET_16BIT_REGISTER(HL, test_address);
		system->registers[F] = 0x00;
		carry = GET_CPU_FLAG(CARRY);
		/* Function to test */
		INC_HL(system);
		uint8_t res = i + 1;
		/* Expected flags */
		zero = res == 0;
		halfcarry = ((res - 1) & 0xF == 0b1111);
		sub = false;
		/* Test */
		if ((uint8_t)system->memory[test_address] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("INC [HL]: %hhu passed\n", i);
		} else {
			printf("INC [HL]: %hhu failed\nExpected: %u z: %u n: "
			       "%u hc: %u c: %u, "
			       "got: %u z: %u n: %u hc: %u c: %u\n",
			       i, res, zero, sub, halfcarry, carry,
			       system->memory[test_address], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_OR_A_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("OR A,r8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->registers[test_r8_1] = test_value;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		bool carry = GET_CPU_FLAG(CARRY);
		OR_A_r8(system, test_r8_1);
		uint8_t res = (uint8_t)i | test_value;
		carry = false;
		halfcarry = false;
		zero = res == 0 ? true : false;
		sub = false;
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("OR A,r8: %hhu passed\n", i);
		} else {
			printf("OR A,r8: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_OR_A_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("OR A,[HL] test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->memory[test_address] = test_value;
		SET_16BIT_REGISTER(HL, test_address);
		system->registers[F] = 0x00;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		OR_A_HL(system);
		uint8_t res = (uint8_t)i | test_value;
		carry = false;
		halfcarry = false;
		zero = res == 0 ? true : false;
		sub = false;
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO)) {
			if (print_all)
				printf("OR A,[HL]: %hhu passed\n", i);
		} else {
			printf("OR A,[HL]: %hhu %hhu failed\nExpected: %u z: "
			       "%u n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_OR_A_n8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("OR A,n8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		OR_A_n8(system, test_value);
		uint8_t res = (uint8_t)i | test_value;
		carry = false;
		halfcarry = false;
		zero = res == 0 ? true : false;
		sub = false;
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("OR A,n8: %hhu passed\n", i);
		} else {
			printf("OR A,n8: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SBC_A_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SBC A,r8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->registers[test_r8_1] = test_value;
		SET_CPU_FLAG(CARRY, 0);
		SET_CPU_FLAG(HALFCARRY, false);
		SBC_A_r8(system, test_r8_1);
		uint8_t res = (uint8_t)i - test_value;
		zero = !res;
		sub = 1;
		if (i < test_value) {
			carry = true;
		} else {
			carry = false;
		}
		// if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry
		// = true; } else { halfcarry = false; }
		halfcarry = (i & 0xF) < (test_value & 0xF);
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("SBC A,r8: %hhu (no carry) passed\n", i);
		} else {
			printf(
			    "SBC A,r8: %hhu %hhu (no carry) failed\nExpected: "
			    "%u z: %u n: %u "
			    "hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			    i, test_value, res, zero, sub, halfcarry, carry,
			    system->registers[A], GET_CPU_FLAG(ZERO),
			    GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			    GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->registers[test_r8_1] = test_value;
		SET_CPU_FLAG(HALFCARRY, false);
		SET_CPU_FLAG(CARRY, true);
		SBC_A_r8(system, test_r8_1);
		uint8_t res = (uint8_t)i - (uint8_t)test_value - 1;
		sub = 1;
		zero = !res;
		carry = (uint8_t)i < ((uint8_t)test_value + 1);
		halfcarry =
		    ((uint8_t)i & 0xF) < ((uint8_t)(test_value & 0xF) + 1);

		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("SBC A,r8: %hhu (carry) passed\n", i);
		} else {
			printf("SBC A,r8: %hhu %hhu (carry) failed\nExpected: "
			       "%u z: %u n: %u hc: "
			       "%u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SBC_A_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SBC A,[HL] test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->memory[test_address] = test_value;
		SET_16BIT_REGISTER(HL, test_address);
		SET_CPU_FLAG(CARRY, 0);
		SET_CPU_FLAG(HALFCARRY, false);
		SBC_A_HL(system);
		uint8_t res = (uint8_t)i - test_value;
		zero = !res;
		sub = 1;
		if (i < test_value) {
			carry = true;
		} else {
			carry = false;
		}
		// if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry
		// = true; } else { halfcarry = false; }
		halfcarry = (i & 0xF) < (test_value & 0xF);
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("SBC A,[HL]: %hhu (no carry) passed\n",
				       i);
		} else {
			printf("SBC A,[HL]: %hhu %hhu (no carry) "
			       "failed\nExpected: %u z: %u n: "
			       "%u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: "
			       "%u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->memory[test_address] = test_value;
		SET_16BIT_REGISTER(HL, test_address);
		SET_CPU_FLAG(CARRY, 1);
		SET_CPU_FLAG(HALFCARRY, false);
		SBC_A_HL(system);
		uint8_t res = (uint8_t)i - (uint8_t)test_value - 1;
		sub = 1;
		zero = !res;
		carry = (uint8_t)i < ((uint8_t)test_value + 1);
		halfcarry =
		    ((uint8_t)i & 0xF) < ((uint8_t)(test_value & 0xF) + 1);

		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("SBC A,[HL]: %hhu (carry) passed\n", i);
		} else {
			printf(
			    "SBC A,[HL]: %hhu %hhu (carry) failed\nExpected: "
			    "%u z: %u n: %u "
			    "hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			    i, test_value, res, zero, sub, halfcarry, carry,
			    system->registers[A], GET_CPU_FLAG(ZERO),
			    GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			    GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SBC_A_n8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SBC A,n8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		SET_CPU_FLAG(CARRY, 0);
		SET_CPU_FLAG(HALFCARRY, false);
		SBC_A_n8(system, test_value);
		uint8_t res = (uint8_t)i - test_value;
		zero = !res;
		sub = 1;
		if (i < test_value) {
			carry = true;
		} else {
			carry = false;
		}
		// if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry
		// = true; } else { halfcarry = false; }
		halfcarry = (i & 0xF) < (test_value & 0xF);
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("SBC A,n8: %hhu (no carry) passed\n", i);
		} else {
			printf(
			    "SBC A,n8: %hhu %hhu (no carry) failed\nExpected: "
			    "%u z: %u n: %u "
			    "hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			    i, test_value, res, zero, sub, halfcarry, carry,
			    system->registers[A], GET_CPU_FLAG(ZERO),
			    GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			    GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;

		SET_CPU_FLAG(HALFCARRY, false);
		SET_CPU_FLAG(CARRY, true);
		SBC_A_n8(system, test_value);
		uint8_t res = (uint8_t)i - (uint8_t)test_value - 1;
		sub = 1;
		zero = !res;
		carry = (uint8_t)i < ((uint8_t)test_value + 1);
		halfcarry =
		    ((uint8_t)i & 0xF) < ((uint8_t)(test_value & 0xF) + 1);

		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("SBC A,n8: %hhu (carry) passed\n", i);
		} else {
			printf("SBC A,n8: %hhu %hhu (carry) failed\nExpected: "
			       "%u z: %u n: %u hc: "
			       "%u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SUB_A_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SBC A,r8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->registers[test_r8_1] = test_value;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		SUB_A_r8(system, test_r8_1);
		uint8_t res = (uint8_t)i - test_value;
		zero = !res;
		sub = 1;
		if (i < test_value) {
			carry = true;
		} else {
			carry = false;
		}
		// if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry
		// = true; } else { halfcarry = false; }
		halfcarry = (i & 0xF) < (test_value & 0xF);
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("SUB A,r8: %hhu passed\n", i);
		} else {
			printf("SUB A,r8: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SUB_A_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SBC A,[HL] test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->memory[test_address] = test_value;
		SET_16BIT_REGISTER(HL, test_address);
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		SUB_A_HL(system);
		uint8_t res = (uint8_t)i - test_value;
		zero = !res;
		sub = 1;
		if (i < test_value) {
			carry = true;
		} else {
			carry = false;
		}
		// if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry
		// = true; } else { halfcarry = false; }
		halfcarry = (i & 0xF) < (test_value & 0xF);
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("SUB A,[HL]: %hhu (no carry) passed\n",
				       i);
		} else {
			printf("SUB A,[HL]: %hhu %hhu (no carry) "
			       "failed\nExpected: %u z: %u n: "
			       "%u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: "
			       "%u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SUB_A_n8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SBC A,n8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		SUB_A_n8(system, test_value);
		uint8_t res = (uint8_t)i - test_value;
		zero = !res;
		sub = 1;
		if (i < test_value) {
			carry = true;
		} else {
			carry = false;
		}
		// if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry
		// = true; } else { halfcarry = false; }
		halfcarry = (i & 0xF) < (test_value & 0xF);
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("SUB A,n8: %hhu passed\n", i);
		} else {
			printf("SUB A,n8: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_XOR_A_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("XOR A,r8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->registers[test_r8_1] = test_value;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		bool carry = GET_CPU_FLAG(CARRY);
		XOR_A_r8(system, test_r8_1);
		uint8_t res = (uint8_t)i ^ test_value;
		carry = false;
		halfcarry = false;
		zero = res == 0 ? true : false;
		sub = false;
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("XOR A,r8: %hhu passed\n", i);
		} else {
			printf("XOR A,r8: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_XOR_A_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("XOR A,[HL] test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		system->memory[test_address] = test_value;
		SET_16BIT_REGISTER(HL, test_address);
		system->registers[F] = 0x00;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		XOR_A_HL(system);
		uint8_t res = (uint8_t)i ^ test_value;
		carry = false;
		halfcarry = false;
		zero = res == 0 ? true : false;
		sub = false;
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO)) {
			if (print_all)
				printf("XOR A,[HL]: %hhu passed\n", i);
		} else {
			printf("XOR A,[HL]: %hhu %hhu failed\nExpected: %u z: "
			       "%u n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_XOR_A_n8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("XOR A,n8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[A] = i;
		SET_CPU_FLAG(CARRY, false);
		SET_CPU_FLAG(HALFCARRY, false);
		XOR_A_n8(system, test_value);
		uint8_t res = (uint8_t)i ^ test_value;
		carry = false;
		halfcarry = false;
		zero = res == 0 ? true : false;
		sub = false;
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("XOR A,n8: %hhu passed\n", i);
		} else {
			printf("XOR A,n8: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

/* 16-bit arithmetic instructions */

bool test_ADD_HL_r16(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("ADD [HL],r16 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint32_t i = 0; i <= 0xFFFF; i++) {
		zero = GET_CPU_FLAG(ZERO);
		SET_CPU_FLAG(SUB, true);
		SET_CPU_FLAG(HALFCARRY, false);
		SET_CPU_FLAG(CARRY, false);
		SET_16BIT_REGISTER(HL, i);
		SET_16BIT_REGISTER(BC, test_value);
		ADD_HL_r16(system, BC);
		sub = false;
		uint16_t res = i + test_value;
		carry = (i + test_value) > 0xFFFF;
		halfcarry = ((i & 0xFFF) + (test_value & 0xFFF)) > 0xFFF;

		if (GET_16BIT_REGISTER(HL) == res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("ADD [HL],r16: %hhu passed\n", i);
		} else {
			printf("ADD [HL],r16: %hu %hu failed\nExpected: %u z: "
			       "%u n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       GET_16BIT_REGISTER(HL), GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}

	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_DEC_r16(System *system, bool print_all) {
	if (print_all)
		printf("DEC r16 test:\n");
	bool failed = false;

	for (uint32_t i = 0; i <= 0xFFFF; i++) {
		SET_16BIT_REGISTER(BC, i);
		DEC_r16(system, BC);
		uint16_t res = i - 1;

		if (GET_16BIT_REGISTER(BC) == res) {
			if (print_all)
				printf("DEC r16: %hhu passed\n", i);
		} else {
			printf("DEC r16: %hu failed\nExpected: %u got: %u\n", i,
			       res, GET_16BIT_REGISTER(BC));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_INC_r16(System *system, bool print_all) {
	if (print_all)
		printf("INC r16 test:\n");
	bool failed = false;

	for (uint32_t i = 0; i <= 0xFFFF; i++) {
		SET_16BIT_REGISTER(BC, i);
		INC_r16(system, BC);
		uint16_t res = i + 1;

		if (GET_16BIT_REGISTER(BC) == res) {
			if (print_all)
				printf("INC r16: %hhu passed\n", i);
		} else {
			printf("INC r16: %hu failed\nExpected: %u got: %u\n", i,
			       res, GET_16BIT_REGISTER(BC));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

/* Bit operations instructions */

bool test_BIT_u3_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("BIT u3,r8 test:\n");
	bool failed = false;
	bool zero = false;

	for (int i = 0; i < 8; i++) {
		system->registers[test_r8_1] = test_value;
		BIT_u3_r8(system, i, test_r8_1);
		zero = !(test_value & (1 << i));
		if (GET_CPU_FLAG(ZERO) == zero) {
			if (print_all)
				printf("BIT u3,r8: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf("BIT u3,r8: %hhu %hhu failed\nExpected: z: %u "
			       "got: z: %u\n",
			       i, test_value, zero, GET_CPU_FLAG(ZERO));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_BIT_u3_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("BIT u3,[HL] test:\n");
	bool failed = false;
	bool zero = false;

	for (int i = 0; i < 8; i++) {
		system->memory[test_address] = test_value;
		SET_16BIT_REGISTER(HL, test_address);
		BIT_u3_HL(system, i);
		zero = !(test_value & (1 << i));
		if (GET_CPU_FLAG(ZERO) == zero) {
			if (print_all)
				printf("BIT u3,[HL]: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf("BIT u3,[HL]: %hhu %hhu failed\nExpected: z: %u "
			       "got: z: %u\n",
			       i, test_value, zero, GET_CPU_FLAG(ZERO));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_RES_u3_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("RES u3,r8 test:\n");
	bool failed = false;

	for (int i = 0; i < 8; i++) {
		system->registers[test_r8_1] = test_value;
		RES_u3_r8(system, i, test_r8_1);
		uint8_t res = test_value & ~(1 << i);
		if (res == system->registers[test_r8_1]) {
			if (print_all)
				printf("RES u3,r8: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf("RES u3,r8: %hhu %hhu failed\nExpected: %u got: "
			       "%u\n",
			       i, test_value, res,
			       system->registers[test_r8_1]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_RES_u3_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("RES u3,[HL] test:\n");
	bool failed = false;

	for (int i = 0; i < 8; i++) {
		system->memory[test_address] = test_value;
		SET_16BIT_REGISTER(HL, test_address);
		RES_u3_HL(system, i);
		uint8_t res = test_value & ~(1 << i);
		if (res == system->memory[test_address]) {
			if (print_all)
				printf("RES u3,[HL]: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf("RES u3,[HL]: %hhu %hhu failed\nExpected: %u "
			       "got: %u\n",
			       i, test_value, res, system->registers[A]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SET_u3_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SET u3,r8 test:\n");
	bool failed = false;

	for (int i = 0; i < 8; i++) {
		system->registers[test_r8_1] = test_value;
		SET_u3_r8(system, i, test_r8_1);
		uint8_t res = test_value | (1 << i);
		if (res == system->registers[test_r8_1]) {
			if (print_all)
				printf("SET u3,r8: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf("SET u3,r8: %hhu %hhu failed\nExpected: %u got: "
			       "%u\n",
			       i, test_value, res,
			       system->registers[test_r8_1]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SET_u3_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SET u3,[HL] test:\n");
	bool failed = false;

	for (int i = 0; i < 8; i++) {
		system->memory[test_address] = test_value;
		SET_16BIT_REGISTER(HL, test_address);
		SET_u3_HL(system, i);
		uint8_t res = test_value | (1 << i);
		if (res == system->memory[test_address]) {
			if (print_all)
				printf("SET u3,[HL]: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf("SET u3,[HL]: %hhu %hhu failed\nExpected: %u "
			       "got: %u\n",
			       i, test_value, res,
			       system->memory[test_address]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SWAP_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SWAP r8 test:\n");
	bool failed = false;
	bool zero = false;

	system->registers[test_r8_1] = test_value;
	SWAP_r8(system, test_r8_1);

	uint8_t temp = test_value & 0xF;
	uint8_t res = (test_value >> 4) + (test_value << 4);
	zero = !res;
	if ((uint8_t)system->registers[test_r8_1] == (uint8_t)res &&
	    0 == GET_CPU_FLAG(CARRY) && 0 == GET_CPU_FLAG(HALFCARRY) &&
	    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
		if (print_all)
			printf("SWAP r8: %hhu (no carry) passed\n", test_value);
	} else {
		printf("SWAP r8: %hhu (no carry) failed\nExpected: %u z: %u n: "
		       "%u hc: %u "
		       "c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
		       test_value, res, zero, 0, 0, 0,
		       system->registers[test_r8_1], GET_CPU_FLAG(ZERO),
		       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
		       GET_CPU_FLAG(CARRY));
		failed = true;
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SWAP_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SWAP [HL] test:\n");
	bool failed = false;
	bool zero = false;

	system->memory[test_address] = test_value;
	SET_16BIT_REGISTER(HL, test_address);
	SWAP_HL(system);
	uint8_t temp = test_value & 0xF;
	uint8_t res = (test_value >> 4) + (test_value << 4);
	zero = !res;
	if ((uint8_t)system->memory[test_address] == (uint8_t)res &&
	    0 == GET_CPU_FLAG(CARRY) && 0 == GET_CPU_FLAG(HALFCARRY) &&
	    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
		if (print_all)
			printf("SWAP [HL]: %hhu (no carry) passed\n",
			       test_value);
	} else {
		printf("SWAP [HL]: %hhu (no carry) failed\nExpected: %u z: %u "
		       "n: %u hc: %u "
		       "c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
		       test_value, res, zero, 0, 0, 0,
		       system->memory[test_address], GET_CPU_FLAG(ZERO),
		       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
		       GET_CPU_FLAG(CARRY));
		failed = true;
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

/* Bit shift instructions */

bool test_RL_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("RL r8 test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;

	system->registers[test_r8_1] = test_value;
	for (uint8_t i = 1; i < 9; i++) {
		carry = system->registers[test_r8_1] & (1 << 7);
		SET_CPU_FLAG(CARRY, false);
		uint8_t res = (system->registers[test_r8_1] << 1) + 0;
		RL_r8(system, test_r8_1);
		zero = !res;
		if ((uint8_t)system->registers[test_r8_1] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RL r8: %hhu (no carry) passed\n",
				       test_value);
		} else {
			printf("RL r8: %hhu %hhu (no carry) failed\nExpected: "
			       "%u z: %u n: %u hc: "
			       "%u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->registers[test_r8_1], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	system->registers[test_r8_1] = test_value;
	for (uint8_t i = 1; i < 9; i++) {
		SET_CPU_FLAG(CARRY, true);
		carry = system->registers[test_r8_1] & (1 << 7);
		uint8_t res = (system->registers[test_r8_1] << 1) + 1;
		RL_r8(system, test_r8_1);
		zero = !res;
		if ((uint8_t)system->registers[test_r8_1] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RL r8: %hhu (no carry) passed\n",
				       test_value);
		} else {
			printf("RL r8: %hhu %hhu (no carry) failed\nExpected: "
			       "%u z: %u n: %u hc: "
			       "%u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->registers[test_r8_1], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_RL_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("RL [HL] test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;

	system->memory[test_address] = test_value;
	SET_16BIT_REGISTER(HL, test_address);
	for (uint8_t i = 1; i < 9; i++) {
		SET_CPU_FLAG(CARRY, false);
		carry = system->memory[test_address] & (1 << 7);
		uint8_t res = (system->memory[test_address] << 1) + 0;
		RL_HL(system);
		zero = !res;
		if ((uint8_t)system->memory[test_address] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RL [HL]: %hhu (no carry) passed\n",
				       test_value);
		} else {
			printf(
			    "RL [HL]: %hhu %hhu (no carry) failed\nExpected: "
			    "%u z: %u n: %u "
			    "hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			    i, test_value, res, zero, 0, 0, carry,
			    system->memory[test_address], GET_CPU_FLAG(ZERO),
			    GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			    GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	system->memory[test_address] = test_value;
	for (uint8_t i = 1; i < 9; i++) {
		SET_CPU_FLAG(CARRY, true);
		carry = system->memory[test_address] & (1 << 7);
		uint8_t res = (system->memory[test_address] << 1) + 1;
		RL_HL(system);
		zero = !res;
		if ((uint8_t)system->memory[test_address] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RL [HL]: %hhu (carry) passed\n",
				       test_value);
		} else {
			printf("RL [HL]: %hhu %hhu (carry) failed\nExpected: "
			       "%u z: %u n: %u hc: "
			       "%u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->memory[test_address], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_RLA(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("RLA test:\n");
	bool failed = false;
	bool carry = false;
	system->registers[A] = test_value;
	for (uint8_t i = 1; i < 9; i++) {
		SET_CPU_FLAG(CARRY, false);
		carry = system->registers[A] & (1 << 7);
		uint8_t res = (system->registers[A] << 1) + 0;
		RLA(system);
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) && 0 == GET_CPU_FLAG(ZERO) &&
		    0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RLA: %hhu (no carry) passed\n",
				       test_value);
		} else {
			printf("RLA: %hhu %hhu (no carry) failed\nExpected: %u "
			       "z: %u n: %u hc: "
			       "%u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, 0, 0, 0, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	system->registers[A] = test_value;
	for (uint8_t i = 1; i < 9; i++) {
		SET_CPU_FLAG(CARRY, true);
		carry = system->registers[A] & (1 << 7);
		uint8_t res = (system->registers[A] << 1) + 1;
		RLA(system);
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) && 0 == GET_CPU_FLAG(ZERO) &&
		    0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RLA: %hhu (carry) passed\n",
				       test_value);
		} else {
			printf("RLA: %hhu %hhu (carry) failed\nExpected: %u z: "
			       "%u n: %u hc: %u "
			       "c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, 0, 0, 0, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_RLC_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("RLC r8 test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;
	system->registers[test_r8_1] = test_value;

	for (uint8_t i = 1; i < 9; i++) {
		carry = system->registers[test_r8_1] & (1 << 7);
		uint8_t res = (system->registers[test_r8_1] << 1) + carry;
		RLC_r8(system, test_r8_1);
		zero = !res;
		if ((uint8_t)system->registers[test_r8_1] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RLC r8: %hhu passed\n", test_value);
		} else {
			printf("RLC r8: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: %u, "
			       "got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->registers[test_r8_1], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_RLC_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("RLC [HL] test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;

	system->memory[test_address] = test_value;
	SET_16BIT_REGISTER(HL, test_address);

	for (uint8_t i = 1; i < 9; i++) {
		carry = system->memory[test_address] & (1 << 7);
		uint8_t res = (system->memory[test_address] << 1) + carry;
		RLC_HL(system);
		zero = !res;
		if ((uint8_t)system->memory[test_address] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RLC [HL]: %hhu passed\n", test_value);
		} else {
			printf("RLC [HL]: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->memory[test_address], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_RLCA(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("RLCA test:\n");
	bool failed = false;
	bool carry = false;
	system->registers[A] = test_value;

	for (uint8_t i = 1; i < 9; i++) {
		carry = system->registers[A] & (1 << 7);
		uint8_t res = (system->registers[A] << 1) + carry;
		RLCA(system);
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) && 0 == GET_CPU_FLAG(ZERO) &&
		    0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RLCA: %hhu passed\n", test_value);
		} else {
			printf("RLCA: %hhu %hhu failed\nExpected: %u z: %u n: "
			       "%u hc: %u c: %u, "
			       "got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, 0, 0, 0, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_RR_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("RR r8 test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;

	system->registers[test_r8_1] = test_value;
	for (uint8_t i = 1; i < 9; i++) {
		carry = system->registers[test_r8_1] & 1;
		SET_CPU_FLAG(CARRY, false);
		uint8_t res = (system->registers[test_r8_1] >> 1);
		RR_r8(system, test_r8_1);
		zero = !res;
		if ((uint8_t)system->registers[test_r8_1] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RR r8: %hhu (no carry) passed\n",
				       test_value);
		} else {
			printf("RR r8: %hhu %hhu (no carry) failed\nExpected: "
			       "%u z: %u n: %u hc: "
			       "%u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->registers[test_r8_1], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	system->registers[A] = test_value;
	for (uint8_t i = 1; i < 9; i++) {
		SET_CPU_FLAG(CARRY, true);
		carry = system->registers[test_r8_1] & 1;
		uint8_t res = (system->registers[test_r8_1] >> 1) + (1 << 7);
		RR_r8(system, test_r8_1);
		zero = !res;
		if ((uint8_t)system->registers[test_r8_1] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RR r8: %hhu (carry) passed\n",
				       test_value);
		} else {
			printf("RR r8: %hhu %hhu (carry) failed\nExpected: %u "
			       "z: %u n: %u hc: %u "
			       "c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->registers[test_r8_1], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_RR_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("RR [HL] test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;

	system->memory[test_address] = test_value;
	SET_16BIT_REGISTER(HL, test_address);
	for (uint8_t i = 1; i < 9; i++) {
		SET_CPU_FLAG(CARRY, false);
		carry = system->memory[test_address] & 1;
		uint8_t res = (system->memory[test_address] >> 1);
		RR_HL(system);
		zero = !res;
		if ((uint8_t)system->memory[test_address] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RR [HL]: %hhu (no carry) passed\n",
				       test_value);
		} else {
			printf(
			    "RR [HL]: %hhu %hhu (no carry) failed\nExpected: "
			    "%u z: %u n: %u "
			    "hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			    i, test_value, res, zero, 0, 0, carry,
			    system->memory[test_address], GET_CPU_FLAG(ZERO),
			    GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			    GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	system->memory[test_address] = test_value;
	for (uint8_t i = 1; i < 9; i++) {
		SET_CPU_FLAG(CARRY, true);
		carry = system->memory[test_address] & 1;
		uint8_t res = (system->memory[test_address] >> 1) + (1 << 7);
		RR_HL(system);
		zero = !res;
		if ((uint8_t)system->memory[test_address] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RR [HL]: %hhu (carry) passed\n",
				       test_value);
		} else {
			printf("RR [HL]: %hhu %hhu (carry) failed\nExpected: "
			       "%u z: %u n: %u hc: "
			       "%u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->memory[test_address], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_RRA(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("RRA test:\n");
	bool failed = false;
	bool carry = false;
	system->registers[A] = test_value;
	for (uint8_t i = 1; i < 9; i++) {
		SET_CPU_FLAG(CARRY, false);
		carry = system->registers[A] & 1;
		uint8_t res = (system->registers[A] >> 1);
		RRA(system);
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) && 0 == GET_CPU_FLAG(ZERO) &&
		    0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RRA: %hhu (no carry) passed\n",
				       test_value);
		} else {
			printf("RRA: %hhu %hhu (no carry) failed\nExpected: %u "
			       "z: %u n: %u hc: "
			       "%u c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, 0, 0, 0, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	system->registers[A] = test_value;
	for (uint8_t i = 1; i < 9; i++) {
		SET_CPU_FLAG(CARRY, true);
		carry = system->registers[A] & 1;
		uint8_t res = (system->registers[A] >> 1) + (1 << 7);
		RRA(system);
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) && 0 == GET_CPU_FLAG(ZERO) &&
		    0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RRA: %hhu (carry) passed\n",
				       test_value);
		} else {
			printf("RRA: %hhu %hhu (carry) failed\nExpected: %u z: "
			       "%u n: %u hc: %u "
			       "c: %u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, 0, 0, 0, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_RRC_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("RRC r8 test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;
	system->registers[test_r8_1] = test_value;

	for (uint8_t i = 1; i < 9; i++) {
		carry = system->registers[test_r8_1] & 1;
		uint8_t res =
		    (system->registers[test_r8_1] >> 1) + (carry << 7);
		RRC_r8(system, test_r8_1);
		zero = !res;
		if ((uint8_t)system->registers[test_r8_1] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RRC r8: %hhu passed\n", test_value);
		} else {
			printf("RRC r8: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: %u, "
			       "got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->registers[test_r8_1], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_RRC_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("RRC [HL] test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;

	system->memory[test_address] = test_value;
	SET_16BIT_REGISTER(HL, test_address);

	for (uint8_t i = 1; i < 9; i++) {
		carry = system->memory[test_address] & 1;
		uint8_t res =
		    (system->memory[test_address] >> 1) + (carry << 7);
		RRC_HL(system);
		zero = !res;
		if ((uint8_t)system->memory[test_address] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RRC [HL]: %hhu passed\n", test_value);
		} else {
			printf("RRC [HL]: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->memory[test_address], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_RRCA(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("RRCA test:\n");
	bool failed = false;
	bool carry = false;
	system->registers[A] = test_value;

	for (uint8_t i = 1; i < 9; i++) {
		carry = system->registers[A] & 1;
		uint8_t res = (system->registers[A] >> 1) + (carry << 7);
		RRCA(system);
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) && 0 == GET_CPU_FLAG(ZERO) &&
		    0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("RRCA: %hhu passed\n", test_value);
		} else {
			printf("RRCA: %hhu %hhu failed\nExpected: %u z: %u n: "
			       "%u hc: %u c: %u, "
			       "got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, 0, 0, 0, carry,
			       system->registers[A], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SLA_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SLA r8 test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;
	system->registers[test_r8_1] = test_value;

	for (uint8_t i = 1; i < 9; i++) {
		carry = system->registers[test_r8_1] & (1 << 7);
		uint8_t res = (system->registers[test_r8_1] << 1);
		SLA_r8(system, test_r8_1);
		zero = !res;
		if ((uint8_t)system->registers[test_r8_1] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("SLA r8: %hhu passed\n", test_value);
		} else {
			printf("SLA r8: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: %u, "
			       "got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->registers[test_r8_1], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SLA_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SLA [HL] test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;

	system->memory[test_address] = test_value;
	SET_16BIT_REGISTER(HL, test_address);
	for (uint8_t i = 1; i < 9; i++) {
		carry = system->memory[test_address] & (1 << 7);
		uint8_t res = (system->memory[test_address] << 1);
		SLA_HL(system);
		zero = !res;
		if ((uint8_t)system->memory[test_address] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("SLA [HL]: %hhu passed\n", test_value);
		} else {
			printf("SLA [HL]: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->memory[test_address], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SRA_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SRA r8 test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;
	system->registers[test_r8_1] = test_value;

	for (uint8_t i = 1; i < 9; i++) {
		carry = system->registers[test_r8_1] & 1;
		uint8_t res = (system->registers[test_r8_1] >> 1) +
			      (system->registers[A] & (1 << 7));
		SRA_r8(system, test_r8_1);
		zero = !res;
		if ((uint8_t)system->registers[test_r8_1] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("SRA r8: %hhu passed\n", test_value);
		} else {
			printf("SRA r8: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: %u, "
			       "got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->registers[test_r8_1], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SRA_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SRA [HL] test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;

	system->memory[test_address] = test_value;
	SET_16BIT_REGISTER(HL, test_address);

	for (uint8_t i = 1; i < 9; i++) {
		carry = system->memory[test_address] & 1;
		uint8_t res = (system->memory[test_address] >> 1) +
			      (system->memory[test_address] & (1 << 7));
		SRA_HL(system);
		zero = !res;
		if ((uint8_t)system->memory[test_address] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("SRA [HL]: %hhu passed\n", test_value);
		} else {
			printf("SRA [HL]: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->memory[test_address], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SRL_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SRL r8 test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;
	system->registers[test_r8_1] = test_value;

	for (uint8_t i = 1; i < 9; i++) {
		carry = system->registers[test_r8_1] & 1;
		uint8_t res = (system->registers[test_r8_1] >> 1);
		SRL_r8(system, test_r8_1);
		zero = !res;
		if ((uint8_t)system->registers[test_r8_1] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("SRL r8: %hhu passed\n", test_value);
		} else {
			printf("SRL r8: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: %u, "
			       "got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->registers[test_r8_1], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_SRL_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("SRL [HL] test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;
	system->memory[test_address] = test_value;
	SET_16BIT_REGISTER(HL, test_address);

	for (uint8_t i = 1; i < 9; i++) {
		carry = system->memory[test_address] & 1;
		uint8_t res = (system->memory[test_address] >> 1);
		SRL_HL(system);
		zero = !res;
		if ((uint8_t)system->memory[test_address] == (uint8_t)res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    0 == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && 0 == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("SRL [HL]: %hhu passed\n", test_value);
		} else {
			printf("SRL [HL]: %hhu %hhu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, 0, 0, carry,
			       system->memory[test_address], GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

/* Load instructions */

bool test_LD_r8_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LD r8,r8 test:\n");
	bool failed = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[test_r8_1] = test_value;
		system->registers[test_r8_2] = i;
		LD_r8_r8(system, test_r8_1, test_r8_2);
		uint8_t res = i;
		if ((uint8_t)system->registers[test_r8_1] == (uint8_t)res) {
			if (print_all)
				printf("LD r8,r8: %hhu passed\n", test_value);
		} else {
			printf("LD r8,r8: %hhu %hhu failed\nExpected: %u, got: "
			       "%u\n",
			       i, test_value, res,
			       system->registers[test_r8_1]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_r8_n8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LD r8,n8 test:\n");
	bool failed = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->registers[test_r8_1] = test_value;
		LD_r8_n8(system, test_r8_1, i);
		uint8_t res = i;
		if ((uint8_t)system->registers[test_r8_1] == (uint8_t)res) {
			if (print_all)
				printf("LD r8,n8: %hhu passed\n", test_value);
		} else {
			printf("LD r8,n8: %hhu %hhu failed\nExpected: %u, got: "
			       "%u\n",
			       i, test_value, res,
			       system->registers[test_r8_1]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_r16_n16(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("LD r16,n16 test:\n");
	bool failed = false;

	for (uint32_t i = 0; i <= 0xFFFF; i++) {
		SET_16BIT_REGISTER(test_r16, test_value);
		LD_r16_n16(system, test_r16, i);
		uint16_t res = i;
		if ((uint16_t)GET_16BIT_REGISTER(test_r16) == (uint16_t)res) {
			if (print_all)
				printf("LD r16,n16: %hu %hu passed\n", i,
				       test_value);
		} else {
			printf("LD r16,n16: %hhu %hhu failed\nExpected: %u, "
			       "got: %u\n",
			       i, test_value, res,
			       GET_16BIT_REGISTER(test_r16));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_HL_r8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LD [HL],r8 test:\n");
	bool failed = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		SET_16BIT_REGISTER(HL, test_address);
		system->memory[test_address] = test_value;
		system->registers[test_r8_1] = i;
		LD_HL_r8(system, test_r8_1);
		uint8_t res = i;
		if ((uint8_t)system->memory[test_address] == (uint8_t)res) {
			if (print_all)
				printf("LD [HL],r8: %hhu passed\n", test_value);
		} else {
			printf("LD [HL],r8: %hhu %hhu failed\nExpected: %u, "
			       "got: %u\n",
			       i, test_value, res,
			       system->memory[test_address]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_HL_n8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LD [HL],n8 test:\n");
	bool failed = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		SET_16BIT_REGISTER(HL, test_address);
		system->memory[test_address] = test_value;
		LD_HL_n8(system, i);
		uint8_t res = i;
		if ((uint8_t)system->memory[test_address] == (uint8_t)res) {
			if (print_all)
				printf("LD [HL],n8: %hhu passed\n", test_value);
		} else {
			printf("LD [HL],n8: %hhu %hhu failed\nExpected: %u, "
			       "got: %u\n",
			       i, test_value, res,
			       system->memory[test_address]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_r8_HL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LD r8,[HL] test:\n");
	bool failed = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		SET_16BIT_REGISTER(HL, test_address);
		system->memory[test_address] = i;
		system->registers[test_r8_1] = test_value;
		LD_r8_HL(system, test_r8_1);
		uint8_t res = i;
		if ((uint8_t)system->registers[test_r8_1] == (uint8_t)res) {
			if (print_all)
				printf("LD r8,[HL]: %hhu passed\n", test_value);
		} else {
			printf("LD r8,[HL]: %hhu %hhu failed\nExpected: %u, "
			       "got: %u\n",
			       i, test_value, res,
			       system->registers[test_r8_1]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_r16_A(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LD r16,A test:\n");
	bool failed = false;

	for (uint32_t i = 0; i <= 0xFFFF; i++) {
		system->registers[A] = i;
		SET_16BIT_REGISTER(test_r16, test_address);
		system->memory[test_address] = test_value;
		LD_r16_A(system, test_r16);
		uint8_t res = i;
		if (system->memory[test_address] == (uint8_t)res) {
			if (print_all)
				printf("LD r16,A: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf("LD r16,A: %hhu %hhu failed\nExpected: %u, got: "
			       "%u\n",
			       i, test_value, res,
			       system->memory[test_address]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_n16_A(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LD n16,A test:\n");
	bool failed = false;

	for (uint32_t i = 0; i <= 0xFFFF; i++) {
		system->registers[A] = i;
		system->memory[test_address] = test_value;
		LD_n16_A(system, test_address);
		uint8_t res = i;
		if (system->memory[test_address] == (uint8_t)res) {
			if (print_all)
				printf("LD n16,A: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf("LD n16,A: %hhu %hhu failed\nExpected: %u, got: "
			       "%u\n",
			       i, test_value, res,
			       system->memory[test_address]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LDH_n8_A(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LDH n8,A test:\n");
	bool failed = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->memory[test_address] = test_value;
		system->registers[A] = i;
		LDH_n8_A(system, test_address & 0xFF);
		uint8_t res = i;

		if (system->memory[test_address] == (uint8_t)res) {
			if (print_all)
				printf("LDH n8,A: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf("LDH n8,A: %hhu %hhu failed\nExpected: %u, got: "
			       "%u\n",
			       i, test_value, res,
			       system->memory[test_address]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LDH_C_A(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LDH C,A test:\n");
	bool failed = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->memory[test_address] = test_value;
		system->registers[C] = test_address & 0xFF;
		system->registers[A] = i;
		LDH_C_A(system);
		uint8_t res = i;

		if (system->memory[test_address] == (uint8_t)res) {
			if (print_all)
				printf("LDH C,A: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf("LDH C,A: %hhu %hhu failed\nExpected: %u, got: "
			       "%u\n",
			       i, test_value, res,
			       system->memory[test_address]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_A_r16(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LD A,r16 test:\n");
	bool failed = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->memory[test_address] = i;
		system->registers[A] = test_value;
		SET_16BIT_REGISTER(test_r16, test_address);
		LD_A_r16(system, test_r16);
		uint8_t res = i;

		if (system->registers[A] == (uint8_t)res) {
			if (print_all)
				printf("LD A,r16: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf("LD A,r16: %hhu %hhu failed\nExpected: %u, got: "
			       "%u\n",
			       i, test_value, res, system->registers[A]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_A_n16(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LD A,n16 test:\n");
	bool failed = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->memory[test_address] = i;
		system->registers[A] = test_value;
		LD_A_n16(system, test_address);
		uint8_t res = i;

		if (system->registers[A] == (uint8_t)res) {
			if (print_all)
				printf("LD A,n16: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf("LD A,n16: %hhu %hhu failed\nExpected: %u, got: "
			       "%u\n",
			       i, test_value, res, system->registers[A]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LDH_A_n8(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LDH A,n8 test:\n");
	bool failed = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->memory[test_address] = i;
		system->registers[A] = test_value;
		LDH_A_n8(system, test_address & 0xFF);
		uint8_t res = i;

		if (system->registers[A] == res) {
			if (print_all)
				printf("LDH A,n8: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf("LDH A,n8: %hhu %hhu failed\nExpected: %u, got: "
			       "%u\n",
			       i, test_value, res, system->registers[A]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LDH_A_C(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LDH A,C test:\n");
	bool failed = false;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		system->memory[test_address] = i;
		system->registers[A] = test_value;
		system->registers[C] = test_address & 0xFF;
		LDH_A_C(system);
		uint8_t res = i;

		if (system->registers[A] == res) {
			if (print_all)
				printf("LDH A,C: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf("LDH A,C: %hhu %hhu failed\nExpected: %u, got: "
			       "%u\n",
			       i, test_value, res, system->registers[A]);
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_HLI_A(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LD [HLI],A test:\n");
	bool failed = false;
	uint16_t hl = 0;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		SET_16BIT_REGISTER(HL, test_address);
		system->memory[test_address] = test_value;
		system->registers[A] = i;
		LD_HLI_A(system);
		hl = test_address + 1;
		uint8_t res = i;
		if ((uint8_t)system->memory[test_address] == (uint8_t)res &&
		    hl == GET_16BIT_REGISTER(HL)) {
			if (print_all)
				printf("LD [HLI],A: %hhu passed\n", test_value);
		} else {
			printf("LD [HLI],A: %hhu %hhu failed\nExpected: %u, "
			       "HL: %x got: %u, HL: "
			       "%x\n",
			       i, test_value, res, hl,
			       system->memory[test_address],
			       GET_16BIT_REGISTER(HL));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_HLD_A(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LD [HLD],A test:\n");
	bool failed = false;
	uint16_t hl = 0;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		SET_16BIT_REGISTER(HL, test_address);
		system->memory[test_address] = test_value;
		system->registers[A] = i;
		LD_HLD_A(system);
		hl = test_address - 1;
		uint8_t res = i;
		if ((uint8_t)system->memory[test_address] == (uint8_t)res &&
		    hl == GET_16BIT_REGISTER(HL)) {
			if (print_all)
				printf("LD [HLD],A: %hhu passed\n", test_value);
		} else {
			printf("LD [HLD],A: %hhu %hhu failed\nExpected: %u, "
			       "HL: 0x%x got: %u, "
			       "HL: 0x%x\n",
			       i, test_value, res, hl,
			       system->memory[test_address],
			       GET_16BIT_REGISTER(HL));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_A_HLI(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LD A,[HLI] test:\n");
	bool failed = false;
	uint16_t hl = 0;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		SET_16BIT_REGISTER(HL, test_address);
		system->memory[test_address] = i;
		system->registers[A] = test_value;
		LD_A_HLI(system);
		hl = test_address + 1;
		uint8_t res = i;
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    hl == GET_16BIT_REGISTER(HL)) {
			if (print_all)
				printf("LD A,[HLI]: %hhu passed\n", test_value);
		} else {
			printf("LD A,[HLI]: %hhu %hhu failed\nExpected: %u, "
			       "HL: %x got: %u, HL: "
			       "%x\n",
			       i, test_value, res, hl, system->registers[A],
			       GET_16BIT_REGISTER(HL));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_A_HLD(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("LD [HLD],A test:\n");
	bool failed = false;
	uint16_t hl = 0;

	for (uint16_t i = 0; i <= 0xFF; i++) {
		SET_16BIT_REGISTER(HL, test_address);
		system->memory[test_address] = i;
		system->registers[A] = test_value;
		LD_A_HLD(system);
		hl = test_address - 1;
		uint8_t res = i;
		if ((uint8_t)system->registers[A] == (uint8_t)res &&
		    hl == GET_16BIT_REGISTER(HL)) {
			if (print_all)
				printf("LD [HLI],A: %hhu passed\n", test_value);
		} else {
			printf("LD [HLI],A: %hhu %hhu failed\nExpected: %u, "
			       "HL: %x got: %u, HL: "
			       "%x\n",
			       i, test_value, res, hl, system->registers[A],
			       GET_16BIT_REGISTER(HL));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

/* Jumps and Subroutines */

bool test_JP_HL(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("JP [HL] test:\n");
	bool failed = false;

	SET_16BIT_REGISTER(HL, test_value);
	JP_HL(system);

	if (GET_16BIT_REGISTER(PC) == test_value) {
		if (print_all)
			printf("JP [HL]: %hhu passed\n", test_value);
	} else {
		printf("JP [HL]: %hu failed\nExpected: %u got: %u\n",
		       test_value, test_value, GET_16BIT_REGISTER(PC));
		failed = true;
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_JP_n16(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("JP n16 test:\n");
	bool failed = false;

	JP_n16(system, test_value);

	if (GET_16BIT_REGISTER(PC) == test_value) {
		if (print_all)
			printf("JP n16: %hhu passed\n", test_value);
	} else {
		printf("JP n16: %hu failed\nExpected: %u got: %u\n", test_value,
		       test_value, GET_16BIT_REGISTER(PC));
		failed = true;
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_JP_cc_n16(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("JP сс,n16 test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;

	for (uint8_t i = 0; i < 4; i++) {
		SET_16BIT_REGISTER(PC, test_uint16);
		uint16_t res = test_uint16;
		switch (i) {
		case NZ:
			zero = false;
			SET_CPU_FLAG(ZERO, zero);
			if (zero == false)
				res = test_value;
			break;
		case Z:
			zero = true;
			SET_CPU_FLAG(ZERO, zero);
			if (zero == true)
				res = test_value;
			break;
		case NC:
			carry = false;
			SET_CPU_FLAG(CARRY, carry);
			if (carry == false)
				res = test_value;
			break;
		case Cc:
			carry = true;
			SET_CPU_FLAG(CARRY, carry);
			if (carry == true)
				res = test_value;
			break;
		default:
			printf("WHAT?\n");
			break;
		}
		JP_cc_n16(system, i, test_value);

		if (GET_16BIT_REGISTER(PC) == res) {
			if (print_all)
				printf("JP сс,n16: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf("JP сс,n16: %hhu %hu failed\nExpected: %u got: "
			       "%u\n",
			       i, test_value, res, GET_16BIT_REGISTER(PC));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_JR_n16(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("JR n16 test:\n");
	bool failed = false;

	for (int i = -128; i <= 127; i++) {
		SET_16BIT_REGISTER(PC, test_address);
		JR_n16(system, i);
		uint16_t res = test_address + i + 2;

		if (GET_16BIT_REGISTER(PC) == res) {
			if (print_all)
				printf("JR n16: %d %hhu passed\n", i,
				       test_value);
		} else {
			printf("JR n16: %hu failed\nExpected: %u got: %u\n",
			       test_value, test_value, GET_16BIT_REGISTER(PC));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_JR_cc_n16(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("JR cc,n16 test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;

	for (int j = -128; j <= 127; j++) {
		for (uint8_t i = 0; i < 4; i++) {
			SET_16BIT_REGISTER(PC, test_uint16);
			uint16_t res = test_uint16;
			switch (i) {
			case NZ:
				zero = false;
				SET_CPU_FLAG(ZERO, zero);
				if (zero == false)
					res = test_uint16 + j + 2;
				break;
			case Z:
				zero = true;
				SET_CPU_FLAG(ZERO, zero);
				if (zero == true)
					res = test_uint16 + j + 2;
				break;
			case NC:
				carry = false;
				SET_CPU_FLAG(CARRY, carry);
				if (carry == false)
					res = test_uint16 + j + 2;
				break;
			case Cc:
				carry = true;
				SET_CPU_FLAG(CARRY, carry);
				if (carry == true)
					res = test_uint16 + j + 2;
				break;
			default:
				printf("WHAT?\n");
				break;
			}
			JR_cc_n16(system, i, (signed char)j);

			if (GET_16BIT_REGISTER(PC) == res) {
				if (print_all)
					printf("JR сс,n16: %hhu %hhu passed\n",
					       i, test_value);
			} else {
				printf(
				    "JR сс,n16: %hhu %hu %d failed\nExpected: "
				    "%u got: %u\n",
				    i, test_value, j, res,
				    GET_16BIT_REGISTER(PC));
				failed = true;
			}
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_RET(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("RET test:\n");
	bool failed = false;

	system->memory[test_address] = test_value & 0xFF;
	system->memory[test_address + 1] = (test_value & 0xFF00) >> 8;
	SET_16BIT_REGISTER(SP, test_address);
	RET(system);

	if (GET_16BIT_REGISTER(PC) == test_value) {
		if (print_all)
			printf("RET: %hhu passed\n", test_value);
	} else {
		printf("RET: %hu failed\nExpected: %u got: %u\n", test_value,
		       test_value, GET_16BIT_REGISTER(PC));
		failed = true;
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_RET_cc(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("RET cc test:\n");
	bool failed = false;
	bool zero = false;
	bool carry = false;

	for (uint8_t i = 0; i < 4; i++) {
		uint16_t res = test_uint16;
		switch (i) {
		case NZ:
			zero = false;
			SET_CPU_FLAG(ZERO, zero);
			if (zero == false)
				res = test_value;
			break;
		case Z:
			zero = true;
			SET_CPU_FLAG(ZERO, zero);
			if (zero == true)
				res = test_value;
			break;
		case NC:
			carry = false;
			SET_CPU_FLAG(CARRY, carry);
			if (carry == false)
				res = test_value;
			break;
		case Cc:
			carry = true;
			SET_CPU_FLAG(CARRY, carry);
			if (carry == true)
				res = test_value;
			break;
		default:
			printf("WHAT?\n");
			break;
		}
		system->memory[test_address] = test_value & 0xFF;
		system->memory[test_address + 1] = (test_value & 0xFF00) >> 8;
		SET_16BIT_REGISTER(PC, test_uint16);
		SET_16BIT_REGISTER(SP, test_address);
		RET_cc(system, i);

		if (GET_16BIT_REGISTER(PC) == res) {
			if (print_all)
				printf("RET cc: %hhu %hhu passed\n", i,
				       test_value);
		} else {
			printf(
			    "RET cc: %hhu %hu failed\nExpected: %u got: %u\n",
			    i, test_value, res, GET_16BIT_REGISTER(PC));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

/* Stack operations instructions */

bool test_ADD_HL_SP(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("ADD [HL],SP test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (uint32_t i = 0; i <= 0xFFFF; i++) {
		zero = GET_CPU_FLAG(ZERO);
		SET_CPU_FLAG(SUB, true);
		SET_CPU_FLAG(HALFCARRY, false);
		SET_CPU_FLAG(CARRY, false);
		SET_16BIT_REGISTER(HL, i);
		SET_16BIT_REGISTER(SP, test_value);
		ADD_HL_SP(system);
		sub = false;
		uint16_t res = i + test_value;
		carry = (i + test_value) > 0xFFFF;
		halfcarry = ((i & 0xFFF) + (test_value & 0xFFF)) > 0xFFF;

		if (GET_16BIT_REGISTER(HL) == res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("ADD [HL],SP: %hhu passed\n", i);
		} else {
			printf("ADD [HL],SP: %hu %hu failed\nExpected: %u z: "
			       "%u n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       GET_16BIT_REGISTER(HL), GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}

	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_ADD_SP_e8(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("ADD SP+e8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (int i = -128; i <= 127; i++) {
		SET_CPU_FLAG(SUB, true);
		SET_16BIT_REGISTER(SP, test_value);
		ADD_SP_e8(system, i);
		zero = 0;
		sub = false;
		uint16_t res = test_value + i;
		halfcarry = i >= 0 ? (i & 0xF) + (test_value & 0xF) > 0xF
				   : (test_value & 0xF) < ((-1 * i) & 0xF);
		carry = i >= 0 ? (i + (test_value & 0xFF)) > 0xFF
			       : (test_value & 0xFF) < (-1 * i);

		if (GET_16BIT_REGISTER(SP) == res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("ADD SP,e8: %d passed\n", i);
		} else {
			printf("ADD SP,e8: %d %hu failed\nExpected: %u z: %u "
			       "n: %u hc: %u c: %u, "
			       "got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       GET_16BIT_REGISTER(SP), GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}

	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_DEC_SP(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("DEC SP test:\n");
	bool failed = false;

	SET_16BIT_REGISTER(SP, test_value);
	DEC_SP(system);
	uint16_t res = test_value - 1;

	if (GET_16BIT_REGISTER(SP) == res) {
		if (print_all)
			printf("DEC SP: %hhu passed\n", test_value);
	} else {
		printf("DEC SP: %hhu failed\nExpected: %u, got: %u\n",
		       test_value, res, GET_16BIT_REGISTER(SP));
		failed = true;
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_INC_SP(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("INC SP test:\n");
	bool failed = false;

	SET_16BIT_REGISTER(SP, test_value);
	INC_SP(system);
	uint16_t res = test_value + 1;

	if (GET_16BIT_REGISTER(SP) == res) {
		if (print_all)
			printf("INC SP: %hhu passed\n", test_value);
	} else {
		printf("INC SP: %hhu failed\nExpected: %u, got: %u\n",
		       test_value, res, GET_16BIT_REGISTER(SP));
		failed = true;
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_SP_n16(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("LD SP,n16 test:\n");
	bool failed = false;

	LD_SP_n16(system, test_value);

	if (GET_16BIT_REGISTER(SP) == test_value) {
		if (print_all)
			printf("LD SP,n16: %hhu passed\n", test_value);
	} else {
		printf("LD SP,n16: %hhu failed\nExpected: %u, got: %u\n",
		       test_value, test_value, GET_16BIT_REGISTER(SP));
		failed = true;
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_n16_SP(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("LD SP,n16 test:\n");
	bool failed = false;

	LD_n16_SP(system, test_value);

	uint16_t loaded =
	    system->memory[test_address] + system->memory[test_address + 1]
	    << 8;
	if (GET_16BIT_REGISTER(SP) == test_value) {
		if (print_all)
			printf("LD SP,n16: %hhu passed\n", test_value);
	} else {
		printf("LD SP,n16: %hhu failed\nExpected: %u, got: %u\n",
		       test_value, test_value, GET_16BIT_REGISTER(SP));
		failed = true;
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_HL_SP_e8(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("LD [HL],SP+e8 test:\n");
	bool failed = false;
	bool carry = false;
	bool halfcarry = false;
	bool zero = false;
	bool sub = false;

	for (int i = -128; i <= 127; i++) {
		SET_CPU_FLAG(SUB, true);
		SET_16BIT_REGISTER(SP, test_value);
		LD_HL_SP_e8(system, i);
		zero = 0;
		sub = false;
		uint16_t res = test_value + i;
		halfcarry = i >= 0 ? (i & 0xF) + (test_value & 0xF) > 0xF
				   : (test_value & 0xF) < ((-1 * i) & 0xF);
		carry = i >= 0 ? (i + (test_value & 0xFF)) > 0xFF
			       : (test_value & 0xFF) < (-1 * i);

		if (GET_16BIT_REGISTER(HL) == res &&
		    carry == GET_CPU_FLAG(CARRY) &&
		    halfcarry == GET_CPU_FLAG(HALFCARRY) &&
		    zero == GET_CPU_FLAG(ZERO) && sub == GET_CPU_FLAG(SUB)) {
			if (print_all)
				printf("LD [HL],SP+e8: %d passed\n", i);
		} else {
			printf("LD [HL],SP+e8: %d %hu failed\nExpected: %u z: "
			       "%u n: %u hc: %u c: "
			       "%u, got: %u z: %u n: %u hc: %u c: %u\n",
			       i, test_value, res, zero, sub, halfcarry, carry,
			       GET_16BIT_REGISTER(HL), GET_CPU_FLAG(ZERO),
			       GET_CPU_FLAG(SUB), GET_CPU_FLAG(HALFCARRY),
			       GET_CPU_FLAG(CARRY));
			failed = true;
		}
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_LD_SP_HL(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("LD SP,[HL] test:\n");
	bool failed = false;

	SET_16BIT_REGISTER(HL, test_value);
	LD_SP_HL(system);
	uint16_t res = test_value;

	if (GET_16BIT_REGISTER(SP) == res) {
		if (print_all)
			printf("LD SP,[HL]: %hhu passed\n", test_value);
	} else {
		printf("LD SP,[HL]: %hu failed\nExpected: %u got: %u\n",
		       test_value, res, GET_16BIT_REGISTER(SP));
		failed = true;
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_POP_r16(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("POP r16 test:\n");
	bool failed = false;

	system->memory[test_address] = test_value & 0xFF;
	system->memory[test_address + 1] = (test_value & 0xFF00) >> 8;
	SET_16BIT_REGISTER(SP, test_address);
	uint16_t res = test_value;

	POP_r16(system, AF);

	if (GET_16BIT_REGISTER(AF) == res) {
		if (print_all)
			printf("POP r16: %hhu passed\n", test_value);
	} else {
		printf("POP r16: %hu failed\nExpected: %u got: %u\n",
		       test_value, res, GET_16BIT_REGISTER(AF));
		failed = true;
	}
	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_PUSH_r16(System *system, uint16_t test_value, bool print_all) {
	if (print_all)
		printf("POP r16 test:\n");
	bool failed = false;

	SET_16BIT_REGISTER(SP, test_address);
	SET_16BIT_REGISTER(AF, test_value);
	uint16_t res = test_value;

	PUSH_r16(system, AF);

	uint16_t ret = (system->memory[test_address - 1] << 8) +
		       system->memory[test_address - 2];

	if (ret == res) {
		if (print_all)
			printf("PUSH r16: %hhu passed\n", test_value);
	} else {
		printf("PUSH r16: %hu failed\nExpected: %u got: %u\n",
		       test_value, res, GET_16BIT_REGISTER(SP));
		failed = true;
	}

	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

/* Miscellaneous Instructions */

bool test_CCF(System *system, bool print_all) {
	if (print_all)
		printf("CCF test:\n");
	bool failed = false;

	bool carry = !GET_CPU_FLAG(CARRY);
	CCF(system);

	if (GET_CPU_FLAG(CARRY) == carry && GET_CPU_FLAG(SUB) == 0 &&
	    GET_CPU_FLAG(HALFCARRY) == 0) {
		if (print_all)
			printf("CCF: passed\n");
	} else {
		printf("CCF: failed\nExpected: c: %u h: %u n: %u got: c: %u h: "
		       "%u n: %u\n",
		       carry, 0, 0, GET_CPU_FLAG(CARRY),
		       GET_CPU_FLAG(HALFCARRY), GET_CPU_FLAG(SUB));
		failed = true;
	}

	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}

bool test_CPL(System *system, uint8_t test_value, bool print_all) {
	if (print_all)
		printf("CPL test:\n");
	bool failed = false;

	uint8_t res = ~system->registers[A];
	CPL(system);

	if (system->registers[A] == res && GET_CPU_FLAG(SUB) == 1 &&
	    GET_CPU_FLAG(HALFCARRY) == 1) {
		if (print_all)
			printf("CPL: passed\n");
	} else {
		printf("CPL: failed\nExpected: A: %hhu h: %u n: %u got: A: "
		       "%hhu h: %u n: %u\n",
		       res, 1, 1, system->registers[A], GET_CPU_FLAG(HALFCARRY),
		       GET_CPU_FLAG(SUB));
		failed = true;
	}

	if (!failed) {
		if (print_all)
			printf("Success!\n");
		return 0;
	} else
		return 1;
}
