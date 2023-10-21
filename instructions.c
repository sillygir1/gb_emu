#include "instructions.h"

/* Flags */

void static ADD_flags(System *system, uint8_t a, uint8_t b, bool carry) {
	uint16_t result = a + b;
	if (carry)
		result += GET_CPU_FLAG(CARRY);
	SET_FLAG(ZERO, !result);
	SET_FLAG(SUB, 0);
	SET_FLAG(HALFCARRY, (a & 0xF + b & 0xF) & 0x10 == 0x10);
	if (result > 0xFFU) {
		SET_FLAG(CARRY, 1);
	} else
		SET_FLAG(CARRY, 0);
}

void static AND_flags(System *system, uint8_t result) {
	if ((uint8_t)result == 0) {
		SET_FLAG(ZERO, 1);
	} else {
		SET_FLAG(ZERO, 0);
	};
	SET_FLAG(SUB, 0);
	SET_FLAG(HALFCARRY, 1);
	SET_FLAG(CARRY, 0);
}

void static SUB_flags(System *system, uint8_t a, uint8_t b) {
	bool carry = GET_CPU_FLAG(CARRY);
	uint8_t result = a - b;
	SET_FLAG(SUB, 1);
	SET_FLAG(ZERO, !result);
	SET_FLAG(CARRY, a < b);
	SET_FLAG(HALFCARRY, ((a & 0xF) < (b & 0xF)));
}

void static SBC_flags(System *system, uint8_t a, uint8_t b) {
	bool carry = GET_CPU_FLAG(CARRY);
	uint8_t result = a - b - carry;
	SET_FLAG(SUB, 1);
	SET_FLAG(ZERO, !result);
	SET_FLAG(CARRY, a < (b + carry));
	SET_FLAG(HALFCARRY, ((a & 0xF) < ((b & 0xF) + carry)));
}

void static DEC_flags(System *system, uint8_t result) {
	SET_FLAG(SUB, true);

	if (result == 0) {
		SET_FLAG(ZERO, true);
	} else
		SET_FLAG(ZERO, false);

	if (result & 0xF == 0b1111) {
		SET_FLAG(HALFCARRY, true);
	} else
		SET_FLAG(HALFCARRY, false);
}

void static INC_flags(System *system, uint8_t result) {
	SET_FLAG(SUB, false);
	if (result == 0) {
		SET_FLAG(ZERO, true);
	} else
		SET_FLAG(ZERO, false);
	if ((result - 1) & 0xF == 0b1111) {
		SET_FLAG(HALFCARRY, true);
	} else {
		SET_FLAG(HALFCARRY, false);
	}
}

void static OR_flags(System *system, uint8_t result) {
	if ((uint8_t)result == 0) {
		SET_FLAG(ZERO, 1);
	} else {
		SET_FLAG(ZERO, 0);
	};
	SET_FLAG(SUB, 0);
	SET_FLAG(HALFCARRY, 0);
	SET_FLAG(CARRY, 0);
}

void static XOR_flags(System *system, uint8_t result) {
	SET_FLAG(ZERO, !result);
	SET_FLAG(SUB, false);
	SET_FLAG(HALFCARRY, false);
	SET_FLAG(CARRY, false);
}

void static ADD_HL_flags(System *system, uint16_t a, uint16_t b) {
	SET_FLAG(SUB, false);
	SET_FLAG(HALFCARRY, (a & 0xFFF) + (b & 0xFFF) > 0xFFF);
	SET_FLAG(CARRY, (a + b) > 0xFFFF);
}

void static BIT_flags(System *system, bool value) {
	SET_FLAG(ZERO, !value);
	SET_FLAG(SUB, false);
	SET_FLAG(HALFCARRY, true);
}

void static SWAP_flags(System *system, bool value) {
	SET_FLAG(ZERO, !value);
	SET_FLAG(SUB, false);
	SET_FLAG(HALFCARRY, false);
	SET_FLAG(CARRY, false);
}

void static BITSHIFT_flags(System *system, uint8_t result, bool carry) {
	SET_FLAG(ZERO, !result);
	SET_FLAG(SUB, false);
	SET_FLAG(HALFCARRY, false);
	SET_FLAG(CARRY, carry);
}

void static SP_e8_flags(System *system, uint16_t sp, char e8) {
	SET_FLAG(ZERO, false);
	SET_FLAG(SUB, false);
	bool hc = e8 >= 0 ? (sp & 0xF) + (e8 & 0xF) > 0xF
			  : (sp & 0xF) < ((-1 * e8) & 0xF);
	SET_FLAG(HALFCARRY, hc);
	bool c =
	    e8 >= 0 ? (sp & 0xFF) + (e8) > 0xFF : (sp & 0xFF) < ((-1 * e8));
	SET_FLAG(CARRY, c);
}
/* 8-bit arithmetic and logic instructions */

void ADC_A_r8(System *system, uint8_t r8) {
	uint16_t result =
	    system->registers[A] + system->registers[r8] + GET_CPU_FLAG(CARRY);

	ADD_flags(system, system->registers[A], system->registers[r8], 1);
	system->registers[A] = result;
}

void ADC_A_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	uint16_t result = system->registers[A] + system->memory[address] +
			  GET_CPU_FLAG(CARRY);

	ADD_flags(system, system->registers[A], system->memory[address], 1);
	system->registers[A] = result;
}

void ADC_A_n8(System *system, uint8_t n8) {
	uint16_t result = system->registers[A] + n8 + GET_CPU_FLAG(CARRY);

	ADD_flags(system, system->registers[A], n8, 1);
	system->registers[A] = result;
}

void ADD_A_r8(System *system, uint8_t r8) {
	uint16_t result = system->registers[A] + system->registers[r8];

	ADD_flags(system, system->registers[A], system->registers[r8], 0);
	system->registers[A] = result;
}

void ADD_A_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	uint16_t result = system->registers[A] + system->memory[address];

	ADD_flags(system, system->registers[A], system->memory[address], 0);
	system->registers[A] = result;
}

void ADD_A_n8(System *system, uint8_t n8) {
	uint16_t result = system->registers[A] + n8;

	ADD_flags(system, system->registers[A], n8, 0);
	system->registers[A] = result;
}

void AND_A_r8(System *system, uint8_t r8) {
	uint8_t result = system->registers[A] & system->registers[r8];

	AND_flags(system, result);
	system->registers[A] = result;
}

void AND_A_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	uint8_t result = system->registers[A] & system->memory[address];

	AND_flags(system, result);
	system->registers[A] = result;
}

void AND_A_n8(System *system, uint8_t n8) {
	uint8_t result = system->registers[A] & n8;

	AND_flags(system, result);
	system->registers[A] = result;
}

void CP_A_r8(System *system, uint8_t r8) {
	SUB_flags(system, system->registers[A], system->registers[r8]);
}

void CP_A_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	SUB_flags(system, system->registers[A], system->memory[address]);
}

void CP_A_n8(System *system, uint8_t n8) {
	SUB_flags(system, system->registers[A], n8);
}

void DEC_r8(System *system, uint8_t r8) {
	system->registers[r8] -= 1;
	DEC_flags(system, system->registers[r8]);
}

void DEC_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	system->memory[address] -= 1;
	DEC_flags(system, system->memory[address]);
}

void INC_r8(System *system, uint8_t r8) {
	system->registers[r8] += 1;
	INC_flags(system, system->registers[r8]);
}

void INC_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	system->memory[address] += 1;
	INC_flags(system, system->memory[address]);
}

void OR_A_r8(System *system, uint8_t r8) {
	uint8_t result = system->registers[A] | system->registers[r8];

	OR_flags(system, result);
	system->registers[A] = result;
}

void OR_A_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	uint8_t result = system->registers[A] | system->memory[address];

	OR_flags(system, result);
	system->registers[A] = result;
}

void OR_A_n8(System *system, uint8_t n8) {
	uint8_t result = system->registers[A] | n8;

	OR_flags(system, result);
	system->registers[A] = result;
}

void SBC_A_r8(System *system, uint8_t r8) {
	uint8_t result =
	    system->registers[A] - system->registers[r8] - GET_CPU_FLAG(CARRY);

	SBC_flags(system, system->registers[A], system->registers[r8]);
	system->registers[A] = result;
}

void SBC_A_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	uint8_t result = system->registers[A] - system->memory[address] -
			 GET_CPU_FLAG(CARRY);

	SBC_flags(system, system->registers[A], system->memory[address]);
	system->registers[A] = result;
}

void SBC_A_n8(System *system, uint8_t n8) {
	uint8_t result = system->registers[A] - n8 - GET_CPU_FLAG(CARRY);

	SBC_flags(system, system->registers[A], n8);
	system->registers[A] = result;
}

void SUB_A_r8(System *system, uint8_t r8) {
	uint8_t result = system->registers[A] - system->registers[r8];

	SUB_flags(system, system->registers[A], system->registers[r8]);
	system->registers[A] = result;
}

void SUB_A_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	uint8_t result = system->registers[A] - system->memory[address];

	SUB_flags(system, system->registers[A], system->memory[address]);
	system->registers[A] = result;
}

void SUB_A_n8(System *system, uint8_t n8) {
	uint8_t result = system->registers[A] - n8;

	SUB_flags(system, system->registers[A], n8);
	system->registers[A] = result;
}

void XOR_A_r8(System *system, uint8_t r8) {
	uint8_t result = system->registers[A] ^ system->registers[r8];

	XOR_flags(system, result);
	system->registers[A] = result;
}

void XOR_A_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	uint8_t result = system->registers[A] ^ system->memory[address];

	XOR_flags(system, result);
	system->registers[A] = result;
}

void XOR_A_n8(System *system, uint8_t n8) {
	uint8_t result = system->registers[A] ^ n8;

	XOR_flags(system, result);
	system->registers[A] = result;
}

/* 16-bit arithmetic instructions */

void ADD_HL_r16(System *system, uint8_t r16) {
	uint16_t result = GET_16BIT_REGISTER(HL) + GET_16BIT_REGISTER(r16);
	ADD_HL_flags(system, GET_16BIT_REGISTER(HL), GET_16BIT_REGISTER(r16));
	SET_16BIT_REGISTER(HL, result);
}

void DEC_r16(System *system, uint8_t r16) {
	SET_16BIT_REGISTER(r16, GET_16BIT_REGISTER(r16) - 1);
}

void INC_r16(System *system, uint8_t r16) {
	SET_16BIT_REGISTER(r16, GET_16BIT_REGISTER(r16) + 1);
}

/* Bit operations instructions */

void BIT_u3_r8(System *system, uint8_t u3, uint8_t r8) {
	bool result = system->registers[r8] & (1 << u3);
	BIT_flags(system, result);
}

void BIT_u3_HL(System *system, uint8_t u3) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	bool result = system->memory[address] & (1 << u3);
	BIT_flags(system, result);
}

void RES_u3_r8(System *system, uint8_t u3, uint8_t r8) {
	uint8_t result = system->registers[r8] & ~(1 << u3);
	system->registers[r8] = result;
}

void RES_u3_HL(System *system, uint8_t u3) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	uint8_t result = system->memory[address] & ~(1 << u3);
	system->memory[address] = result;
}

void SET_u3_r8(System *system, uint8_t u3, uint8_t r8) {
	uint8_t result = system->registers[r8] | (1 << u3);
	system->registers[r8] = result;
}

void SET_u3_HL(System *system, uint8_t u3) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	uint8_t result = system->memory[address] | (1 << u3);
	system->memory[address] = result;
}

void SWAP_r8(System *system, uint8_t r8) {
	uint8_t temp = system->registers[r8] & 0xF;
	uint8_t result = (temp << 4) + (system->registers[r8] >> 4);
	SWAP_flags(system, result);
	system->registers[r8] = result;
}

void SWAP_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	uint8_t temp = system->memory[address] & 0xF;
	uint8_t result = (temp << 4) + (system->memory[address] >> 4);
	SWAP_flags(system, result);
	system->memory[address] = result;
}

/* Bit shift instructions */

void RL_r8(System *system, uint8_t r8) {
	bool carry = system->registers[r8] & (1 << 7);
	uint8_t result = (system->registers[r8] << 1) + GET_CPU_FLAG(CARRY);
	BITSHIFT_flags(system, result, carry);
	system->registers[r8] = result;
}

void RL_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	bool carry = system->memory[address] & (1 << 7);
	uint8_t result = (system->memory[address] << 1) + GET_CPU_FLAG(CARRY);
	BITSHIFT_flags(system, result, carry);
	system->memory[address] = result;
}

void RLA(System *system) {
	bool carry = system->registers[A] & (1 << 7);
	uint8_t result = (system->registers[A] << 1) + GET_CPU_FLAG(CARRY);
	SET_FLAG(ZERO, false);
	SET_FLAG(SUB, false);
	SET_FLAG(HALFCARRY, false);
	SET_FLAG(CARRY, carry);
	system->registers[A] = result;
}

void RLC_r8(System *system, uint8_t r8) {
	bool carry = system->registers[r8] & (1 << 7);
	uint8_t result = (system->registers[r8] << 1) + carry;
	BITSHIFT_flags(system, result, carry);
	system->registers[r8] = result;
}

void RLC_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	bool carry = system->memory[address] & (1 << 7);
	uint8_t result = (system->memory[address] << 1) + carry;
	BITSHIFT_flags(system, result, carry);
	system->memory[address] = result;
}

void RLCA(System *system) {
	bool carry = system->registers[A] & (1 << 7);
	uint8_t result = (system->registers[A] << 1) + carry;
	SET_FLAG(ZERO, false);
	SET_FLAG(SUB, false);
	SET_FLAG(HALFCARRY, false);
	SET_FLAG(CARRY, carry);
	system->registers[A] = result;
}

void RR_r8(System *system, uint8_t r8) {
	bool carry = system->registers[r8] & 1;
	uint8_t result =
	    (system->registers[r8] >> 1) + (GET_CPU_FLAG(CARRY) << 7);
	BITSHIFT_flags(system, result, carry);
	system->registers[r8] = result;
}

void RR_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	bool carry = system->memory[address] & 1;
	uint8_t result =
	    (system->memory[address] >> 1) + (GET_CPU_FLAG(CARRY) << 7);
	BITSHIFT_flags(system, result, carry);
	system->memory[address] = result;
}

void RRA(System *system) {
	bool carry = system->registers[A] & 1;
	uint8_t result =
	    (system->registers[A] >> 1) + (GET_CPU_FLAG(CARRY) << 7);
	SET_FLAG(ZERO, false);
	SET_FLAG(SUB, false);
	SET_FLAG(HALFCARRY, false);
	SET_FLAG(CARRY, carry);
	system->registers[A] = result;
}

void RRC_r8(System *system, uint8_t r8) {
	bool carry = system->registers[r8] & 1;
	uint8_t result = (system->registers[r8] >> 1) + (carry << 7);
	BITSHIFT_flags(system, result, carry);
	system->registers[r8] = result;
}

void RRC_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	bool carry = system->memory[address] & 1;
	uint8_t result = (system->memory[address] >> 1) + (carry << 7);
	BITSHIFT_flags(system, result, carry);
	system->memory[address] = result;
}

void RRCA(System *system) {
	bool carry = system->registers[A] & 1;
	uint8_t result = (system->registers[A] >> 1) + (carry << 7);
	SET_FLAG(ZERO, false);
	SET_FLAG(SUB, false);
	SET_FLAG(HALFCARRY, false);
	SET_FLAG(CARRY, carry);
	system->registers[A] = result;
}

void SLA_r8(System *system, uint8_t r8) {
	bool carry = system->registers[r8] & (1 << 7);
	uint8_t result = system->registers[r8] << 1;
	BITSHIFT_flags(system, result, carry);
	system->registers[r8] = result;
}

void SLA_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	bool carry = system->memory[address] & (1 << 7);
	uint8_t result = system->memory[address] << 1;
	BITSHIFT_flags(system, result, carry);
	system->memory[address] = result;
}

void SRA_r8(System *system, uint8_t r8) {
	bool carry = system->registers[r8] & 1;
	uint8_t result =
	    (system->registers[r8] >> 1) + (system->registers[r8] & (1 << 7));
	BITSHIFT_flags(system, result, carry);
	system->registers[r8] = result;
}

void SRA_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	bool carry = system->memory[address] & 1;
	uint8_t result = (system->memory[address] >> 1) +
			 (system->memory[address] & (1 << 7));
	BITSHIFT_flags(system, result, carry);
	system->memory[address] = result;
}

void SRL_r8(System *system, uint8_t r8) {
	bool carry = system->registers[r8] & 1;
	uint8_t result = system->registers[r8] >> 1;
	BITSHIFT_flags(system, result, carry);
	system->registers[r8] = result;
}

void SRL_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	bool carry = system->memory[address] & 1;
	uint8_t result = (system->memory[address] >> 1);
	BITSHIFT_flags(system, result, carry);
	system->memory[address] = result;
}

/* Load instructions */

void LD_r8_r8(System *system, uint8_t r8_1, uint8_t r8_2) {
	system->registers[r8_1] = system->registers[r8_2];
}

void LD_r8_n8(System *system, uint8_t r8, uint8_t n8) {
	system->registers[r8] = n8;
}

void LD_r16_n16(System *system, uint8_t r16, uint16_t n16) {
	SET_16BIT_REGISTER(r16, n16);
}

void LD_HL_r8(System *system, uint8_t r8) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	system->memory[address] = system->registers[r8];
}

void LD_HL_n8(System *system, uint8_t n8) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	system->memory[address] = n8;
}

void LD_r8_HL(System *system, uint8_t r8) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	system->registers[r8] = system->memory[address];
}

void LD_r16_A(System *system, uint8_t r16) {
	uint16_t address = GET_16BIT_REGISTER(r16);
	system->memory[address] = system->registers[A];
}

void LD_n16_A(System *system, uint16_t n16) {
	system->memory[n16] = system->registers[A];
}

void LDH_n8_A(System *system, uint8_t n8) {
	uint16_t address = 0xFF00 + n8;
	system->memory[address] = system->registers[A];
}

void LDH_C_A(System *system) {
	uint16_t address = 0xFF00 + system->registers[C];
	system->memory[address] = system->registers[A];
}

void LD_A_r16(System *system, uint8_t r16) {
	uint16_t address = GET_16BIT_REGISTER(r16);
	system->registers[A] = system->memory[address];
}

void LD_A_n16(System *system, uint16_t n16) {
	system->registers[A] = system->memory[n16];
}

void LDH_A_n8(System *system, uint8_t n8) {
	uint16_t address = 0xFF00 + n8;
	system->registers[A] = system->memory[address];
}

void LDH_A_C(System *system) {
	uint16_t address = 0xFF00 + system->registers[C];
	system->registers[A] = system->memory[address];
}

void LD_HLI_A(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	system->memory[address] = system->registers[A];
	SET_16BIT_REGISTER(HL, address + 1);
}

void LD_HLD_A(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	system->memory[address] = system->registers[A];
	SET_16BIT_REGISTER(HL, address - 1);
}

void LD_A_HLI(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	system->registers[A] = system->memory[address];
	SET_16BIT_REGISTER(HL, address + 1);
}

void LD_A_HLD(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	system->registers[A] = system->memory[address];
	SET_16BIT_REGISTER(HL, address - 1);
}

/* Jumps and Subroutines */

void CALL_n16(System *system, uint16_t n16); // TODO

void CALL_cc_n16(System *system, uint8_t condition, uint16_t n16); // TODO

void JP_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	SET_16BIT_REGISTER(PC, address);
}

void JP_n16(System *system, uint16_t n16) { SET_16BIT_REGISTER(PC, n16); }

void JP_cc_n16(System *system, uint8_t condition, uint16_t n16) {
	switch (condition) {
	case NZ:
		if (GET_CPU_FLAG(ZERO) == true) {
			system->current_instruction_duration = 12;
			return;
		}
		break;
	case Z:
		if (GET_CPU_FLAG(ZERO) == false) {
			system->current_instruction_duration = 12;
			return;
		}
		break;
	case NC:
		if (GET_CPU_FLAG(CARRY) == true) {
			system->current_instruction_duration = 12;
			return;
		}
		break;
	case Cc:
		if (GET_CPU_FLAG(CARRY) == false) {
			system->current_instruction_duration = 12;
			return;
		}
		break;
	default:
		// WHY?
		return;
	}
	system->current_instruction_duration = 16;
	SET_16BIT_REGISTER(PC, n16);
}

void JR_n16(System *system, char e8) {
	uint16_t address = GET_16BIT_REGISTER(PC) + e8 + 2;
	SET_16BIT_REGISTER(PC, address);
}

void JR_cc_n16(System *system, uint8_t condition, char e8) {
	uint16_t address = GET_16BIT_REGISTER(PC) + e8 + 2;
	bool taken = false;
	switch (condition) {
	case NZ:
		if (GET_CPU_FLAG(ZERO) == false) {
			SET_16BIT_REGISTER(PC, address);
			taken = true;
		}
		break;
	case Z:
		if (GET_CPU_FLAG(ZERO) == true) {
			SET_16BIT_REGISTER(PC, address);
			taken = true;
		}
		break;
	case NC:
		if (GET_CPU_FLAG(CARRY) == false) {
			SET_16BIT_REGISTER(PC, address);
			taken = true;
		}
		break;
	case Cc:
		if (GET_CPU_FLAG(CARRY) == true) {
			SET_16BIT_REGISTER(PC, address);
			taken = true;
		}
		break;
	default:
		// WHY?
		return;
	}
	system->current_instruction_duration = taken ? 12 : 8;
}

void RET(System *system) {
	uint16_t sp = GET_16BIT_REGISTER(SP);
	uint16_t pc = system->memory[sp++] + (system->memory[sp++] << 8);
	SET_16BIT_REGISTER(SP, sp);
	SET_16BIT_REGISTER(PC, pc);
}

void RET_cc(System *system, uint8_t condition) {
	switch (condition) {
	case NZ:
		if (GET_CPU_FLAG(ZERO) == true) {
			system->current_instruction_duration = 8;
			return;
		}
		break;
	case Z:
		if (GET_CPU_FLAG(ZERO) == false) {
			system->current_instruction_duration = 8;
			return;
		}
		break;
	case NC:
		if (GET_CPU_FLAG(CARRY) == true) {
			system->current_instruction_duration = 8;
			return;
		}
		break;
	case Cc:
		if (GET_CPU_FLAG(CARRY) == false) {
			system->current_instruction_duration = 8;
			return;
		}
		break;
	default:
		// WHY?
		return;
	}
	system->current_instruction_duration = 20;
	uint16_t sp = GET_16BIT_REGISTER(sp);
	uint16_t pc = system->memory[sp++] + (system->memory[sp++] << 8);
	SET_16BIT_REGISTER(SP, sp);
	SET_16BIT_REGISTER(PC, pc);
}

void RETI(System *system); // TODO

void RST_vec(System *system); // TODO

/* Stack operations instructions */

void ADD_HL_SP(System *system) {
	uint16_t result = GET_16BIT_REGISTER(HL) + GET_16BIT_REGISTER(SP);
	ADD_HL_flags(system, GET_16BIT_REGISTER(HL), GET_16BIT_REGISTER(SP));
	SET_16BIT_REGISTER(HL, result);
} // tested?

void ADD_SP_e8(System *system, char e8) {
	uint16_t sp = GET_16BIT_REGISTER(SP);
	uint16_t result = sp + e8;
	SP_e8_flags(system, sp, e8);
	SET_16BIT_REGISTER(SP, result);
} // not tested

void DEC_SP(System *system) {
	uint16_t result = GET_16BIT_REGISTER(SP) - 1;
	SET_16BIT_REGISTER(SP, result);
}

void INC_SP(System *system) {
	uint16_t result = GET_16BIT_REGISTER(SP) + 1;
	SET_16BIT_REGISTER(SP, result);
}

void LD_SP_n16(System *system, uint16_t n16) { SET_16BIT_REGISTER(SP, n16); }

void LD_n16_SP(System *system, uint16_t n16) {
	uint16_t sp = GET_16BIT_REGISTER(SP);
	system->memory[n16] = sp & 0xFF;
	system->memory[n16 + 1] = sp >> 8;
}

void LD_HL_SP_e8(System *system, char e8) {
	uint16_t sp = GET_16BIT_REGISTER(SP);
	uint16_t result = sp + e8;
	SP_e8_flags(system, sp, e8);
	SET_16BIT_REGISTER(HL, result);
}

void LD_SP_HL(System *system) {
	uint16_t hl = GET_16BIT_REGISTER(HL);
	SET_16BIT_REGISTER(SP, hl);
}

void POP_r16(System *system, uint8_t r16) {
	// Only used to load BC, DE and HL
	uint16_t sp = GET_16BIT_REGISTER(SP);
	switch (r16) {
	case AF:
		system->registers[F] = system->memory[sp++]; // Flags register
		system->registers[A] = system->memory[sp++];
		break;
	case BC:
		system->registers[C] = system->memory[sp++];
		system->registers[B] = system->memory[sp++];
		break;
	case DE:
		system->registers[E] = system->memory[sp++];
		system->registers[D] = system->memory[sp++];
		break;
	case HL:
		system->registers[L] = system->memory[sp++];
		system->registers[H] = system->memory[sp++];
		break;
	default:
		// WHAT?
		return;
	}
	SET_16BIT_REGISTER(SP, sp);
}

void PUSH_r16(System *system, uint8_t r16) {
	uint16_t sp = GET_16BIT_REGISTER(SP);
	switch (r16) {
	case AF:
		system->memory[--sp] = system->registers[A];
		system->memory[--sp] = system->registers[F];
		break;
	case BC:
		system->memory[--sp] = system->registers[B];
		system->memory[--sp] = system->registers[C];
		break;
	case DE:
		system->memory[--sp] = system->registers[D];
		system->memory[--sp] = system->registers[E];
		break;
	case HL:
		system->memory[--sp] = system->registers[H];
		system->memory[--sp] = system->registers[L];
		break;
	default:
		// HOW?
		return;
	}

	SET_16BIT_REGISTER(SP, sp);
}

/* Miscellaneous Instructions */

void CCF(System *system) {
	bool c = GET_CPU_FLAG(CARRY);
	SET_FLAG(CARRY, !c);
	SET_FLAG(HALFCARRY, false);
	SET_FLAG(SUB, false);
}

void CPL(System *system) {
	uint8_t a = system->registers[A];
	system->registers[A] = ~a;
	SET_FLAG(HALFCARRY, true);
	SET_FLAG(SUB, true);
}

void DAA(System *system) {
	// Thanks a lot to u/Pattern_Key, this is based on their implementation
	bool n = GET_CPU_FLAG(SUB);
	bool c = GET_CPU_FLAG(CARRY);
	bool h = GET_CPU_FLAG(HALFCARRY);
	if (n) {
		if (c)
			system->registers[A] -= 0x60;
		if (h)
			system->registers[A] -= 0x6;
	} else {
		if (c || system->registers[A] > 0x99) {
			system->registers[A] += 0x60;
			SET_FLAG(CARRY, true);
		}
		if (h || (system->registers[A] & 0xF) > 0x9)
			system->registers[A] += 0x6;
	}
}

void DI(System *system) { system->IME = false; }

void EI(System *system);

void HALT(System *system);

void NOP(System *system) {
	// Literally do nothing but waste a cpu cycle or something
}

void SCF(System *system);

void STOP(System *system);

void get_instruction_length(System *system) {
	static uint8_t length[256] = {
	    1, 3, 1, 1, 1, 1, 2, 1, 3, 1, 1, 1, 1, 1, 2, 1, 2, 3, 1, 1, 1, 1,
	    2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 3, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1,
	    1, 1, 2, 1, 2, 3, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1,
	    2, 1, 1, 1, 3, 2, 3, 3, 2, 1, 1, 1, 3, 0, 3, 1, 2, 1, 1, 1, 3, 0,
	    3, 0, 2, 1, 2, 1, 2, 0, 0, 1, 2, 1, 2, 1, 3, 0, 0, 0, 2, 1, 2, 1,
	    2, 1, 0, 1, 2, 1, 2, 1, 3, 1, 0, 0, 2, 1};
	uint16_t instruction = system->current_instruction;
	if (instruction > 0xFF)
		instruction = instruction >> 8;

	system->current_instruction_length = length[instruction];
}

void get_instruction_duration(System *system) {
	static uint8_t regular_duration[256] = {
	    4,	12, 8,	8,  4,	4,  8,	4,  20, 8,  8,	8,    4,  4,  8, 4,
	    4,	12, 8,	8,  4,	4,  8,	4,  12, 8,  8,	8,    4,  4,  8, 4,
	    ND, 12, 8,	8,  4,	4,  8,	4,  ND, 8,  8,	8,    4,  4,  8, 4,
	    ND, 12, 8,	8,  12, 12, 12, 4,  ND, 8,  8,	8,    4,  4,  8, 4,
	    4,	4,  4,	4,  4,	4,  8,	4,  4,	4,  4,	4,    4,  4,  8, 4,
	    4,	4,  4,	4,  4,	4,  8,	4,  4,	4,  4,	4,    4,  4,  8, 4,
	    4,	4,  4,	4,  4,	4,  8,	4,  4,	4,  4,	4,    4,  4,  8, 4,
	    8,	8,  8,	8,  8,	8,  4,	8,  4,	4,  4,	4,    4,  4,  8, 4,
	    4,	4,  4,	4,  4,	4,  8,	4,  4,	4,  4,	4,    4,  4,  8, 4,
	    4,	4,  4,	4,  4,	4,  8,	4,  4,	4,  4,	4,    4,  4,  8, 4,
	    4,	4,  4,	4,  4,	4,  8,	4,  4,	4,  4,	4,    4,  4,  8, 4,
	    4,	4,  4,	4,  4,	4,  8,	4,  4,	4,  4,	4,    4,  4,  8, 4,
	    ND, 12, ND, 16, ND, 16, 8,	16, ND, 16, ND, 0xCB, ND, 24, 8, 16,
	    ND, 12, ND, 0,  ND, 16, 8,	16, ND, 16, ND, 0,    ND, 0,  8, 16,
	    12, 12, 8,	0,  0,	16, 8,	16, 16, 4,  16, 0,    0,  0,  8, 16,
	    12, 12, 8,	4,  0,	16, 8,	16, 12, 8,  16, 4,    0,  0,  8, 16,
	};

	static uint8_t extended_duration[256] = {
	    8, 8, 8,  8, 8, 8, 16, 8, 8, 8, 8,	8, 8, 8, 16, 8, 8, 8, 8,  8,
	    8, 8, 16, 8, 8, 8, 8,  8, 8, 8, 16, 8, 8, 8, 8,  8, 8, 8, 16, 8,
	    8, 8, 8,  8, 8, 8, 16, 8, 8, 8, 8,	8, 8, 8, 16, 8, 8, 8, 8,  8,
	    8, 8, 16, 8, 8, 8, 8,  8, 8, 8, 16, 8, 8, 8, 8,  8, 8, 8, 16, 8,
	    8, 8, 8,  8, 8, 8, 16, 8, 8, 8, 8,	8, 8, 8, 16, 8, 8, 8, 8,  8,
	    8, 8, 16, 8, 8, 8, 8,  8, 8, 8, 16, 8, 8, 8, 8,  8, 8, 8, 16, 8,
	    8, 8, 8,  8, 8, 8, 16, 8, 8, 8, 8,	8, 8, 8, 16, 8, 8, 8, 8,  8,
	    8, 8, 16, 8, 8, 8, 8,  8, 8, 8, 16, 8, 8, 8, 8,  8, 8, 8, 16, 8,
	    8, 8, 8,  8, 8, 8, 16, 8, 8, 8, 8,	8, 8, 8, 16, 8, 8, 8, 8,  8,
	    8, 8, 16, 8, 8, 8, 8,  8, 8, 8, 16, 8, 8, 8, 8,  8, 8, 8, 16, 8,
	    8, 8, 8,  8, 8, 8, 16, 8, 8, 8, 8,	8, 8, 8, 16, 8, 8, 8, 8,  8,
	    8, 8, 16, 8, 8, 8, 8,  8, 8, 8, 16, 8, 8, 8, 8,  8, 8, 8, 16, 8,
	    8, 8, 8,  8, 8, 8, 16, 8, 8, 8, 8,	8, 8, 8, 16, 8,
	};

	uint16_t instruction = system->current_instruction;
	bool extended = instruction >> 8 == 0xCB;
	if (extended)
		system->current_instruction_duration =
		    extended_duration[instruction & 0xFF];
	else
		system->current_instruction_duration =
		    regular_duration[instruction];
}
