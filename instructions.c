#include "instructions.h"

/* Flags */

void static ADD_flags(System *system, uint8_t a, uint8_t b, bool carry) {
	uint16_t result = a + b;
	if (carry)
		result += GET_CPU_FLAG(CARRY);
	SET_CPU_FLAG(ZERO, !result);
	SET_CPU_FLAG(SUB, 0);
	SET_CPU_FLAG(HALFCARRY, (a & 0xF + b & 0xF) & 0x10 == 0x10);
	if (result > 0xFFU) {
		SET_CPU_FLAG(CARRY, 1);
	} else
		SET_CPU_FLAG(CARRY, 0);
}

void static AND_flags(System *system, uint8_t result) {
	if ((uint8_t)result == 0) {
		SET_CPU_FLAG(ZERO, 1);
	} else {
		SET_CPU_FLAG(ZERO, 0);
	};
	SET_CPU_FLAG(SUB, 0);
	SET_CPU_FLAG(HALFCARRY, 1);
	SET_CPU_FLAG(CARRY, 0);
}

void static SUB_flags(System *system, uint8_t a, uint8_t b) {
	bool carry = GET_CPU_FLAG(CARRY);
	uint8_t result = a - b;
	SET_CPU_FLAG(SUB, 1);
	SET_CPU_FLAG(ZERO, !result);
	SET_CPU_FLAG(CARRY, a < b);
	SET_CPU_FLAG(HALFCARRY, ((a & 0xF) < (b & 0xF)));
}

void static SBC_flags(System *system, uint8_t a, uint8_t b) {
	bool carry = GET_CPU_FLAG(CARRY);
	uint8_t result = a - b - carry;
	SET_CPU_FLAG(SUB, 1);
	SET_CPU_FLAG(ZERO, !result);
	SET_CPU_FLAG(CARRY, a < (b + carry));
	SET_CPU_FLAG(HALFCARRY, ((a & 0xF) < ((b & 0xF) + carry)));
}

void static DEC_flags(System *system, uint8_t result) {
	SET_CPU_FLAG(SUB, true);

	if (result == 0) {
		SET_CPU_FLAG(ZERO, true);
	} else
		SET_CPU_FLAG(ZERO, false);

	if (result & 0xF == 0b1111) {
		SET_CPU_FLAG(HALFCARRY, true);
	} else
		SET_CPU_FLAG(HALFCARRY, false);
}

void static INC_flags(System *system, uint8_t result) {
	SET_CPU_FLAG(SUB, false);
	if (result == 0) {
		SET_CPU_FLAG(ZERO, true);
	} else
		SET_CPU_FLAG(ZERO, false);
	if ((result - 1) & 0xF == 0b1111) {
		SET_CPU_FLAG(HALFCARRY, true);
	} else {
		SET_CPU_FLAG(HALFCARRY, false);
	}
}

void static OR_flags(System *system, uint8_t result) {
	if ((uint8_t)result == 0) {
		SET_CPU_FLAG(ZERO, 1);
	} else {
		SET_CPU_FLAG(ZERO, 0);
	};
	SET_CPU_FLAG(SUB, 0);
	SET_CPU_FLAG(HALFCARRY, 0);
	SET_CPU_FLAG(CARRY, 0);
}

void static XOR_flags(System *system, uint8_t result) {
	SET_CPU_FLAG(ZERO, !result);
	SET_CPU_FLAG(SUB, false);
	SET_CPU_FLAG(HALFCARRY, false);
	SET_CPU_FLAG(CARRY, false);
}

void static ADD_HL_flags(System *system, uint16_t a, uint16_t b) {
	SET_CPU_FLAG(SUB, false);
	SET_CPU_FLAG(HALFCARRY, (a & 0xFFF) + (b & 0xFFF) > 0xFFF);
	SET_CPU_FLAG(CARRY, (a + b) > 0xFFFF);
}

void static BIT_flags(System *system, bool value) {
	SET_CPU_FLAG(ZERO, !value);
	SET_CPU_FLAG(SUB, false);
	SET_CPU_FLAG(HALFCARRY, true);
}

void static SWAP_flags(System *system, bool value) {
	SET_CPU_FLAG(ZERO, !value);
	SET_CPU_FLAG(SUB, false);
	SET_CPU_FLAG(HALFCARRY, false);
	SET_CPU_FLAG(CARRY, false);
}

void static BITSHIFT_flags(System *system, uint8_t result, bool carry) {
	SET_CPU_FLAG(ZERO, !result);
	SET_CPU_FLAG(SUB, false);
	SET_CPU_FLAG(HALFCARRY, false);
	SET_CPU_FLAG(CARRY, carry);
}

void static SP_e8_flags(System *system, uint16_t sp, char e8) {
	SET_CPU_FLAG(ZERO, false);
	SET_CPU_FLAG(SUB, false);
	bool hc = e8 >= 0 ? (sp & 0xF) + (e8 & 0xF) > 0xF
			  : (sp & 0xF) < ((-1 * e8) & 0xF);
	SET_CPU_FLAG(HALFCARRY, hc);
	bool c =
	    e8 >= 0 ? (sp & 0xFF) + (e8) > 0xFF : (sp & 0xFF) < ((-1 * e8));
	SET_CPU_FLAG(CARRY, c);
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
	SET_CPU_FLAG(ZERO, false);
	SET_CPU_FLAG(SUB, false);
	SET_CPU_FLAG(HALFCARRY, false);
	SET_CPU_FLAG(CARRY, carry);
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
	SET_CPU_FLAG(ZERO, false);
	SET_CPU_FLAG(SUB, false);
	SET_CPU_FLAG(HALFCARRY, false);
	SET_CPU_FLAG(CARRY, carry);
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
	SET_CPU_FLAG(ZERO, false);
	SET_CPU_FLAG(SUB, false);
	SET_CPU_FLAG(HALFCARRY, false);
	SET_CPU_FLAG(CARRY, carry);
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
	SET_CPU_FLAG(ZERO, false);
	SET_CPU_FLAG(SUB, false);
	SET_CPU_FLAG(HALFCARRY, false);
	SET_CPU_FLAG(CARRY, carry);
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

void CALL_n16(System *system, uint16_t n16){}; // TODO

void CALL_cc_n16(System *system, uint8_t condition, uint16_t n16){}; // TODO

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

void JR_cc_n16(System *system, uint8_t condition, signed char e8) {
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
	uint16_t sp = GET_16BIT_REGISTER(SP);
	uint16_t pc = system->memory[sp++] + (system->memory[sp++] << 8);
	SET_16BIT_REGISTER(SP, sp);
	SET_16BIT_REGISTER(PC, pc);
}

void RETI(System *system){}; // TODO

void RST_vec(System *system){}; // TODO

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
			system->registers[F] =
			    system->memory[sp++]; // Flags register
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
	SET_CPU_FLAG(CARRY, !c);
	SET_CPU_FLAG(HALFCARRY, false);
	SET_CPU_FLAG(SUB, false);
}

void CPL(System *system) {
	uint8_t a = system->registers[A];
	system->registers[A] = ~a;
	SET_CPU_FLAG(HALFCARRY, true);
	SET_CPU_FLAG(SUB, true);
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
			SET_CPU_FLAG(CARRY, true);
		}
		if (h || (system->registers[A] & 0xF) > 0x9)
			system->registers[A] += 0x6;
	}
}

void DI(System *system) { system->IME = false; }

void EI(System *system){};

void HALT(System *system){};

void NOP(System *system) {
	// Literally do nothing but waste a cpu cycle or something
}

void SCF(System *system){};

void STOP(System *system){};

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

void execute_regular(System *system) {
	if (system->current_instruction > 0xFF) {
		// Throw an error
	}

	uint16_t pc = GET_16BIT_REGISTER(PC);
	uint16_t sp = GET_16BIT_REGISTER(SP);

	uint16_t n16 = system->memory[pc + 1] + (system->memory[pc + 2] << 8);

	// Taking naive approach
	switch (system->current_instruction) {
		case 0x0:
			NOP(system);
			break;
		case 0x1:
			// LD BC,d16
			LD_r16_n16(system, BC, n16);
			break;
		case 0x2:
			// LD (BC),A
			LD_r16_A(system, BC);
			break;
		case 0x3:
			// INC BC
			INC_r16(system, BC);
			break;
		case 0x4:
			// INC B
			INC_r8(system, B);
			break;
		case 0x5:
			// DEC B
			DEC_r8(system, B);
			break;
		case 0x6:
			// LD B,d8
			LD_r8_n8(system, B, system->memory[pc + 1]);
			break;
		case 0x7:
			// RLCA
			RLCA(system);
			break;
		case 0x8:
			// LD (a16),SP
			LD_n16_SP(system, n16);
			break;
		case 0x9:
			// ADD HL,BC
			ADD_HL_r16(system, BC);
			break;
		case 0xa:
			// LD A,(BC)
			LD_A_r16(system, BC);
			break;
		case 0xb:
			// DEC BC
			DEC_r16(system, BC);
			break;
		case 0xc:
			// INC C
			INC_r8(system, C);
			break;
		case 0xd:
			// DEC C
			DEC_r8(system, C);
			break;
		case 0xe:
			// LD C,d8
			LD_r8_n8(system, C, system->memory[pc + 1]);
			break;
		case 0xf:
			// RRCA
			RRCA(system);
			break;
		case 0x10:
			// STOP 0
			STOP(system);
			break;
		case 0x11:
			// LD DE,d16
			LD_r16_n16(system, DE, n16);
			break;
		case 0x12:
			// LD (DE),A
			LD_r16_A(system, DE);
			break;
		case 0x13:
			// INC DE
			INC_r16(system, DE);
			break;
		case 0x14:
			// INC D
			INC_r8(system, D);
			break;
		case 0x15:
			// DEC D
			DEC_r8(system, D);
			break;
		case 0x16:
			// LD D,d8
			LD_r8_n8(system, D, system->memory[pc + 1]);
			break;
		case 0x17:
			// RLA
			RLA(system);
			break;
		case 0x18:
			// JR r8
			JR_n16(system, system->memory[pc + 1]);
			break;
		case 0x19:
			// ADD HL,DE
			ADD_HL_r16(system, DE);
			break;
		case 0x1a:
			// LD A,(DE)
			LD_A_r16(system, DE);
			break;
		case 0x1b:
			// DEC DE
			DEC_r16(system, DE);
			break;
		case 0x1c:
			// INC E
			INC_r8(system, E);
			break;
		case 0x1d:
			// DEC E
			DEC_r8(system, E);
			break;
		case 0x1e:
			// LD E,d8
			LD_r8_n8(system, E, system->memory[pc + 1]);
			break;
		case 0x1f:
			// RRA
			RRA(system);
			break;
		case 0x20:
			// JR NZ,r8
			JR_cc_n16(system, NZ, system->memory[pc + 1]);
			break;
		case 0x21:
			// LD HL,d16
			LD_r16_n16(system, HL, n16);
			break;
		case 0x22:
			// LD (HL+),A
			LD_HLI_A(system);
			break;
		case 0x23:
			// INC HL
			INC_r16(system, HL);
			break;
		case 0x24:
			// INC H
			INC_r8(system, H);
			break;
		case 0x25:
			// DEC H
			DEC_r8(system, H);
			break;
		case 0x26:
			// LD H,d8
			LD_r8_n8(system, H, system->memory[pc + 1]);
			break;
		case 0x27:
			// DAA
			DAA(system);
			break;
		case 0x28:
			// JR Z,r8
			JR_cc_n16(system, Z, system->memory[pc + 1]);
			break;
		case 0x29:
			// ADD HL,HL
			ADD_HL_r16(system, HL);
			break;
		case 0x2a:
			// LD A,(HL+)
			LD_A_HLI(system);
			break;
		case 0x2b:
			// DEC HL
			DEC_r16(system, HL);
			break;
		case 0x2c:
			// INC L
			INC_r8(system, L);
			break;
		case 0x2d:
			// DEC L
			DEC_r8(system, L);
			break;
		case 0x2e:
			// LD L,d8
			LD_r8_n8(system, L, system->memory[pc + 1]);
			break;
		case 0x2f:
			// CPL
			CPL(system);
			break;
		case 0x30:
			// JR NC,r8
			break;
		case 0x31:
			// LD SP,d16
			break;
		case 0x32:
			// LD (HL-),A
			break;
		case 0x33:
			// INC SP
			break;
		case 0x34:
			// INC (HL)
			break;
		case 0x35:
			// DEC (HL)
			break;
		case 0x36:
			// LD (HL),d8
			break;
		case 0x37:
			// SCF
			break;
		case 0x38:
			// JR C,r8
			break;
		case 0x39:
			// ADD HL,SP
			break;
		case 0x3a:
			// LD A,(HL-)
			break;
		case 0x3b:
			// DEC SP
			break;
		case 0x3c:
			// INC A
			break;
		case 0x3d:
			// DEC A
			break;
		case 0x3e:
			// LD A,d8
			break;
		case 0x3f:
			// CCF
			break;
		case 0x40:
			// LD B,B
			break;
		case 0x41:
			// LD B,C
			break;
		case 0x42:
			// LD B,D
			break;
		case 0x43:
			// LD B,E
			break;
		case 0x44:
			// LD B,H
			break;
		case 0x45:
			// LD B,L
			break;
		case 0x46:
			// LD B,(HL)
			break;
		case 0x47:
			// LD B,A
			break;
		case 0x48:
			// LD C,B
			break;
		case 0x49:
			// LD C,C
			break;
		case 0x4a:
			// LD C,D
			break;
		case 0x4b:
			// LD C,E
			break;
		case 0x4c:
			// LD C,H
			break;
		case 0x4d:
			// LD C,L
			break;
		case 0x4e:
			// LD C,(HL)
			break;
		case 0x4f:
			// LD C,A
			break;
		case 0x50:
			// LD D,B
			break;
		case 0x51:
			// LD D,C
			break;
		case 0x52:
			// LD D,D
			break;
		case 0x53:
			// LD D,E
			break;
		case 0x54:
			// LD D,H
			break;
		case 0x55:
			// LD D,L
			break;
		case 0x56:
			// LD D,(HL)
			break;
		case 0x57:
			// LD D,A
			break;
		case 0x58:
			// LD E,B
			break;
		case 0x59:
			// LD E,C
			break;
		case 0x5a:
			// LD E,D
			break;
		case 0x5b:
			// LD E,E
			break;
		case 0x5c:
			// LD E,H
			break;
		case 0x5d:
			// LD E,L
			break;
		case 0x5e:
			// LD E,(HL)
			break;
		case 0x5f:
			// LD E,A
			break;
		case 0x60:
			// LD H,B
			break;
		case 0x61:
			// LD H,C
			break;
		case 0x62:
			// LD H,D
			break;
		case 0x63:
			// LD H,E
			break;
		case 0x64:
			// LD H,H
			break;
		case 0x65:
			// LD H,L
			break;
		case 0x66:
			// LD H,(HL)
			break;
		case 0x67:
			// LD H,A
			break;
		case 0x68:
			// LD L,B
			break;
		case 0x69:
			// LD L,C
			break;
		case 0x6a:
			// LD L,D
			break;
		case 0x6b:
			// LD L,E
			break;
		case 0x6c:
			// LD L,H
			break;
		case 0x6d:
			// LD L,L
			break;
		case 0x6e:
			// LD L,(HL)
			break;
		case 0x6f:
			// LD L,A
			break;
		case 0x70:
			// LD (HL),B
			break;
		case 0x71:
			// LD (HL),C
			break;
		case 0x72:
			// LD (HL),D
			break;
		case 0x73:
			// LD (HL),E
			break;
		case 0x74:
			// LD (HL),H
			break;
		case 0x75:
			// LD (HL),L
			break;
		case 0x76:
			// HALT
			break;
		case 0x77:
			// LD (HL),A
			break;
		case 0x78:
			// LD A,B
			break;
		case 0x79:
			// LD A,C
			break;
		case 0x7a:
			// LD A,D
			break;
		case 0x7b:
			// LD A,E
			break;
		case 0x7c:
			// LD A,H
			break;
		case 0x7d:
			// LD A,L
			break;
		case 0x7e:
			// LD A,(HL)
			break;
		case 0x7f:
			// LD A,A
			break;
		case 0x80:
			// ADD A,B
			break;
		case 0x81:
			// ADD A,C
			break;
		case 0x82:
			// ADD A,D
			break;
		case 0x83:
			// ADD A,E
			break;
		case 0x84:
			// ADD A,H
			break;
		case 0x85:
			// ADD A,L
			break;
		case 0x86:
			// ADD A,(HL)
			break;
		case 0x87:
			// ADD A,A
			break;
		case 0x88:
			// ADC A,B
			break;
		case 0x89:
			// ADC A,C
			break;
		case 0x8a:
			// ADC A,D
			break;
		case 0x8b:
			// ADC A,E
			break;
		case 0x8c:
			// ADC A,H
			break;
		case 0x8d:
			// ADC A,L
			break;
		case 0x8e:
			// ADC A,(HL)
			break;
		case 0x8f:
			// ADC A,A
			break;
		case 0x90:
			// SUB B
			break;
		case 0x91:
			// SUB C
			break;
		case 0x92:
			// SUB D
			break;
		case 0x93:
			// SUB E
			break;
		case 0x94:
			// SUB H
			break;
		case 0x95:
			// SUB L
			break;
		case 0x96:
			// SUB (HL)
			break;
		case 0x97:
			// SUB A
			break;
		case 0x98:
			// SBC A,B
			break;
		case 0x99:
			// SBC A,C
			break;
		case 0x9a:
			// SBC A,D
			break;
		case 0x9b:
			// SBC A,E
			break;
		case 0x9c:
			// SBC A,H
			break;
		case 0x9d:
			// SBC A,L
			break;
		case 0x9e:
			// SBC A,(HL)
			break;
		case 0x9f:
			// SBC A,A
			break;
		case 0xa0:
			// AND B
			break;
		case 0xa1:
			// AND C
			break;
		case 0xa2:
			// AND D
			break;
		case 0xa3:
			// AND E
			break;
		case 0xa4:
			// AND H
			break;
		case 0xa5:
			// AND L
			break;
		case 0xa6:
			// AND (HL)
			break;
		case 0xa7:
			// AND A
			break;
		case 0xa8:
			// XOR B
			break;
		case 0xa9:
			// XOR C
			break;
		case 0xaa:
			// XOR D
			break;
		case 0xab:
			// XOR E
			break;
		case 0xac:
			// XOR H
			break;
		case 0xad:
			// XOR L
			break;
		case 0xae:
			// XOR (HL)
			break;
		case 0xaf:
			// XOR A
			break;
		case 0xb0:
			// OR B
			break;
		case 0xb1:
			// OR C
			break;
		case 0xb2:
			// OR D
			break;
		case 0xb3:
			// OR E
			break;
		case 0xb4:
			// OR H
			break;
		case 0xb5:
			// OR L
			break;
		case 0xb6:
			// OR (HL)
			break;
		case 0xb7:
			// OR A
			break;
		case 0xb8:
			// CP B
			break;
		case 0xb9:
			// CP C
			break;
		case 0xba:
			// CP D
			break;
		case 0xbb:
			// CP E
			break;
		case 0xbc:
			// CP H
			break;
		case 0xbd:
			// CP L
			break;
		case 0xbe:
			// CP (HL)
			break;
		case 0xbf:
			// CP A
			break;
		case 0xc0:
			// RET NZ
			break;
		case 0xc1:
			// POP BC
			break;
		case 0xc2:
			// JP NZ,a16
			break;
		case 0xc3:
			// JP a16
			break;
		case 0xc4:
			// CALL NZ,a16
			break;
		case 0xc5:
			// PUSH BC6
			break;
		case 0xc6:
			// ADD A,d8
			break;
		case 0xc7:
			// RST 00H
			break;
		case 0xc8:
			// RET Z
			break;
		case 0xc9:
			// RET
			break;
		case 0xca:
			// JP Z,a16
			break;
		case 0xcb:
			// PREFIX CB
			break;
		case 0xcc:
			// CALL Z,a16
			break;
		case 0xcd:
			// CALL a16
			break;
		case 0xce:
			// ADC A,d8
			break;
		case 0xcf:
			// RST 08H
			break;
		case 0xd0:
			// RET NC
			break;
		case 0xd1:
			// POP DE
			break;
		case 0xd2:
			// JP NC,a16
			break;
		case 0xd3:
			// No instruction
			break;
		case 0xd4:
			// CALL NC,a16
			break;
		case 0xd5:
			// PUSH DE6
			break;
		case 0xd6:
			// SUB d8
			break;
		case 0xd7:
			// RST 10H
			break;
		case 0xd8:
			// RET C
			break;
		case 0xd9:
			// RETI6
			break;
		case 0xda:
			// JP C,a16
			break;
		case 0xdb:
			// No instruction
			break;
		case 0xdc:
			// CALL C,a16
			break;
		case 0xdd:
			// No instruction
			break;
		case 0xde:
			// SBC A,d8
			break;
		case 0xdf:
			// RST 18H
			break;
		case 0xe0:
			// LDH (a8),A
			break;
		case 0xe1:
			// POP HL
			break;
		case 0xe2:
			// LD (C),A
			break;
		case 0xe3:
			// No instruction
			break;
		case 0xe4:
			// No instruction
			break;
		case 0xe5:
			// PUSH HL6
			break;
		case 0xe6:
			// AND d8
			break;
		case 0xe7:
			// RST 20H
			break;
		case 0xe8:
			// ADD SP,r8
			break;
		case 0xe9:
			// JP (HL)
			break;
		case 0xea:
			// LD (a16),A
			break;
		case 0xeb:
			// No instruction
			break;
		case 0xec:
			// No instruction
			break;
		case 0xed:
			// No instruction
			break;
		case 0xee:
			// XOR d8
			break;
		case 0xef:
			// RST 28H
			break;
		case 0xf0:
			// LDH A,(a8)
			break;
		case 0xf1:
			// POP AF
			break;
		case 0xf2:
			// LD A,(C)
			break;
		case 0xf3:
			// DI
			break;
		case 0xf4:
			// No instruction
			break;
		case 0xf5:
			// PUSH AF
			break;
		case 0xf6:
			// OR d8
			break;
		case 0xf7:
			// RST 30H
			break;
		case 0xf8:
			// LD HL,SP+r8
			break;
		case 0xf9:
			// LD SP,HL
			break;
		case 0xfa:
			// LD A,(a16)
			break;
		case 0xfb:
			// EI
			break;
		case 0xfc:
			// No instruction
			break;
		case 0xfd:
			// No instruction
			break;
		case 0xfe:
			// CP d8
			break;
		case 0xff:
			// RST 38H
			break;

		default:
			// Throw an error
			break;
	}
}

void execute_extended(System *system) {
	if (system->current_instruction && 0xFF00 != 0xCB00) {
		// Throw an error
	}
	switch (system->current_instruction && 0xFF) {
		default:
			// Throw an error
			break;
	}
}
