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

void CALL_n16(System *system, uint16_t n16) {
	uint16_t sp = GET_16BIT_REGISTER(SP);
	uint16_t pc = GET_16BIT_REGISTER(PC);

	system->memory[--sp] = system->registers[pc >> 8];
	system->memory[--sp] = system->registers[pc & 0xFF];

	SET_16BIT_REGISTER(SP, sp);
	SET_16BIT_REGISTER(PC, n16);
};

void CALL_cc_n16(System *system, uint8_t condition, uint16_t n16) {
	if ((condition == NZ && GET_CPU_FLAG(ZERO) == true) ||
	    (condition == Z && GET_CPU_FLAG(ZERO) == false) ||
	    (condition == NC && GET_CPU_FLAG(CARRY) == true) ||
	    (condition = Cc && GET_CPU_FLAG(CARRY) == false)) {
		system->current_instruction_duration = 12;
		return;
	}

	system->current_instruction_duration = 24;

	uint16_t sp = GET_16BIT_REGISTER(SP);
	uint16_t pc = GET_16BIT_REGISTER(PC);

	system->memory[--sp] = system->registers[pc >> 8];
	system->memory[--sp] = system->registers[pc & 0xFF];

	SET_16BIT_REGISTER(SP, sp);
	SET_16BIT_REGISTER(PC, n16);
};

void JP_HL(System *system) {
	uint16_t address = GET_16BIT_REGISTER(HL);
	SET_16BIT_REGISTER(PC, address);
}

void JP_n16(System *system, uint16_t n16) { SET_16BIT_REGISTER(PC, n16); }

void JP_cc_n16(System *system, uint8_t condition, uint16_t n16) {
	if ((condition == NZ && GET_CPU_FLAG(ZERO) == true) ||
	    (condition == Z && GET_CPU_FLAG(ZERO) == false) ||
	    (condition == NC && GET_CPU_FLAG(CARRY) == true) ||
	    (condition == Cc && GET_CPU_FLAG(CARRY) == false)) {
		system->current_instruction_duration = 12;
		return;
	}
	system->current_instruction_duration = 16;
	SET_16BIT_REGISTER(PC, n16);
}

void JR_n16(System *system, char e8) {
	uint16_t address = GET_16BIT_REGISTER(PC) + e8;
	SET_16BIT_REGISTER(PC, address);
}

void JR_cc_n16(System *system, uint8_t condition, signed char e8) {
	uint16_t address = GET_16BIT_REGISTER(PC) + e8;
	bool taken = false;
	if ((condition == NZ && GET_CPU_FLAG(ZERO) == false) ||
	    (condition == Z && GET_CPU_FLAG(ZERO) == true) ||
	    (condition == NC && GET_CPU_FLAG(CARRY) == false) ||
	    (condition == Cc && GET_CPU_FLAG(CARRY) == true)) {
		SET_16BIT_REGISTER(PC, address);
		taken = true;
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
	if ((condition == NZ && GET_CPU_FLAG(ZERO) == true) ||
	    (condition == Z && GET_CPU_FLAG(ZERO) == false) ||
	    (condition == NC && GET_CPU_FLAG(CARRY) == true) ||
	    (condition == Cc && GET_CPU_FLAG(CARRY) == false)) {
		system->current_instruction_duration = 8;
		return;
	}
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

void RETI(System *system) {
	system->interrupt_pending = true;
	uint16_t sp = GET_16BIT_REGISTER(SP);
	uint16_t pc = system->memory[sp++] + (system->memory[sp++] << 8);
	SET_16BIT_REGISTER(SP, sp);
	SET_16BIT_REGISTER(PC, pc);
};

void RST_vec(System *system, uint8_t vec) {
	uint16_t sp = GET_16BIT_REGISTER(SP);
	uint16_t pc = GET_16BIT_REGISTER(PC);

	system->memory[--sp] = system->registers[pc >> 8];
	system->memory[--sp] = system->registers[pc & 0xFF];

	SET_16BIT_REGISTER(SP, sp);
	SET_16BIT_REGISTER(PC, vec);
};

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

void EI(System *system) { system->interrupt_pending = true; };

void HALT(System *system){}; // TODO

void NOP(System *system) {
	// Literally do nothing
}

void SCF(System *system) { SET_CPU_FLAG(CARRY, true); };

void STOP(System *system){}; // TODO

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

	uint8_t n8 = system->n8;
	uint8_t e8 = ~(n8 - 1);
	uint16_t n16 = system->n16;

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
			// LD B,n8
			LD_r8_n8(system, B, n8);
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
			// LD C,n8
			LD_r8_n8(system, C, n8);
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
			// LD D,n8
			LD_r8_n8(system, D, n8);
			break;
		case 0x17:
			// RLA
			RLA(system);
			break;
		case 0x18:
			// JR e8
			JR_n16(system, e8);
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
			// LD E,n8
			LD_r8_n8(system, E, n8);
			break;
		case 0x1f:
			// RRA
			RRA(system);
			break;
		case 0x20:
			// JR NZ,e8
			JR_cc_n16(system, NZ, e8);
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
			// LD H,n8
			LD_r8_n8(system, H, n8);
			break;
		case 0x27:
			// DAA
			DAA(system);
			break;
		case 0x28:
			// JR Z,e8
			JR_cc_n16(system, Z, e8);
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
			// LD L,n8
			LD_r8_n8(system, L, n8);
			break;
		case 0x2f:
			// CPL
			CPL(system);
			break;
		case 0x30:
			// JR NC,e8
			JR_cc_n16(system, NC, e8);
			break;
		case 0x31:
			// LD SP,d16
			LD_SP_n16(system, n16);
			break;
		case 0x32:
			// LD (HL-),A
			LD_HLD_A(system);
			break;
		case 0x33:
			// INC SP
			INC_SP(system);
			break;
		case 0x34:
			// INC (HL)
			INC_r16(system, HL);
			break;
		case 0x35:
			// DEC (HL)
			DEC_HL(system);
			break;
		case 0x36:
			// LD (HL),n8
			LD_HL_n8(system, n8);
			break;
		case 0x37:
			// SCF
			SCF(system);
			break;
		case 0x38:
			// JR C,e8
			JR_cc_n16(system, Cc, e8);
			break;
		case 0x39:
			// ADD HL,SP
			ADD_HL_SP(system);
			break;
		case 0x3a:
			// LD A,(HL-)
			LD_A_HLD(system);
			break;
		case 0x3b:
			// DEC SP
			DEC_SP(system);
			break;
		case 0x3c:
			// INC A
			INC_r8(system, A);
			break;
		case 0x3d:
			// DEC A
			DEC_r8(system, A);
			break;
		case 0x3e:
			// LD A,n8
			LD_r8_n8(system, A, n8);
			break;
		case 0x3f:
			// CCF
			CCF(system);
			break;
		case 0x40:
			// LD B,B
			LD_r8_r8(system, B, B);
			break;
		case 0x41:
			// LD B,C
			LD_r8_r8(system, B, C);
			break;
		case 0x42:
			// LD B,D
			LD_r8_r8(system, B, D);
			break;
		case 0x43:
			// LD B,E
			LD_r8_r8(system, B, E);
			break;
		case 0x44:
			// LD B,H
			LD_r8_r8(system, B, H);
			break;
		case 0x45:
			// LD B,L
			LD_r8_r8(system, B, L);
			break;
		case 0x46:
			// LD B,(HL)
			LD_r8_HL(system, B);
			break;
		case 0x47:
			// LD B,A
			LD_r8_r8(system, B, A);
			break;
		case 0x48:
			// LD C,B
			LD_r8_r8(system, C, B);
			break;
		case 0x49:
			// LD C,C
			LD_r8_r8(system, C, C);
			break;
		case 0x4a:
			// LD C,D
			LD_r8_r8(system, C, D);
			break;
		case 0x4b:
			// LD C,E
			LD_r8_r8(system, C, E);
			break;
		case 0x4c:
			// LD C,H
			LD_r8_r8(system, C, H);
			break;
		case 0x4d:
			// LD C,L
			LD_r8_r8(system, C, L);
			break;
		case 0x4e:
			// LD C,(HL)
			LD_r8_HL(system, C);
			break;
		case 0x4f:
			// LD C,A
			LD_r8_r8(system, C, A);
			break;
		case 0x50:
			// LD D,B
			LD_r8_r8(system, D, B);
			break;
		case 0x51:
			// LD D,C
			LD_r8_r8(system, D, C);
			break;
		case 0x52:
			// LD D,D
			LD_r8_r8(system, D, D);
			break;
		case 0x53:
			// LD D,E
			LD_r8_r8(system, D, E);
			break;
		case 0x54:
			// LD D,H
			LD_r8_r8(system, D, H);
			break;
		case 0x55:
			// LD D,L
			LD_r8_r8(system, D, L);
			break;
		case 0x56:
			// LD D,(HL)
			LD_r8_HL(system, D);
			break;
		case 0x57:
			// LD D,A
			LD_r8_r8(system, D, A);
			break;
		case 0x58:
			// LD E,B
			LD_r8_r8(system, E, B);
			break;
		case 0x59:
			// LD E,C
			LD_r8_r8(system, E, C);
			break;
		case 0x5a:
			// LD E,D
			LD_r8_r8(system, E, D);
			break;
		case 0x5b:
			// LD E,E
			LD_r8_r8(system, E, E);
			break;
		case 0x5c:
			// LD E,H
			LD_r8_r8(system, E, H);
			break;
		case 0x5d:
			// LD E,L
			LD_r8_r8(system, E, L);
			break;
		case 0x5e:
			// LD E,(HL)
			LD_r8_HL(system, E);
			break;
		case 0x5f:
			// LD E,A
			LD_r8_r8(system, E, A);
			break;
		case 0x60:
			// LD H,B
			LD_r8_r8(system, H, B);
			break;
		case 0x61:
			// LD H,C
			LD_r8_r8(system, H, C);
			break;
		case 0x62:
			// LD H,D
			LD_r8_r8(system, H, D);
			break;
		case 0x63:
			// LD H,E
			LD_r8_r8(system, H, E);
			break;
		case 0x64:
			// LD H,H
			LD_r8_r8(system, H, H);
			break;
		case 0x65:
			// LD H,L
			LD_r8_r8(system, H, L);
			break;
		case 0x66:
			// LD H,(HL)
			LD_r8_HL(system, H);
			break;
		case 0x67:
			// LD H,A
			LD_r8_r8(system, H, A);
			break;
		case 0x68:
			// LD L,B
			LD_r8_r8(system, L, B);
			break;
		case 0x69:
			// LD L,C
			LD_r8_r8(system, L, C);
			break;
		case 0x6a:
			// LD L,D
			LD_r8_r8(system, L, D);
			break;
		case 0x6b:
			// LD L,E
			LD_r8_r8(system, L, E);
			break;
		case 0x6c:
			// LD L,H
			LD_r8_r8(system, L, H);
			break;
		case 0x6d:
			// LD L,L
			LD_r8_r8(system, L, L);
			break;
		case 0x6e:
			// LD L,(HL)
			LD_r8_HL(system, L);
			break;
		case 0x6f:
			// LD L,A
			LD_r8_r8(system, L, A);
			break;
		case 0x70:
			// LD (HL),B
			LD_HL_r8(system, B);
			break;
		case 0x71:
			// LD (HL),C
			LD_HL_r8(system, C);
			break;
		case 0x72:
			// LD (HL),D
			LD_HL_r8(system, D);
			break;
		case 0x73:
			// LD (HL),E
			LD_HL_r8(system, E);
			break;
		case 0x74:
			// LD (HL),H
			LD_HL_r8(system, H);
			break;
		case 0x75:
			// LD (HL),L
			LD_HL_r8(system, L);
			break;
		case 0x76:
			// HALT
			HALT(system);
			break;
		case 0x77:
			// LD (HL),A
			LD_HL_r8(system, A);
			break;
		case 0x78:
			// LD A,B
			LD_r8_r8(system, A, B);
			break;
		case 0x79:
			// LD A,C
			LD_r8_r8(system, A, A);
			break;
		case 0x7a:
			// LD A,D
			LD_r8_r8(system, A, D);
			break;
		case 0x7b:
			// LD A,E
			LD_r8_r8(system, A, E);
			break;
		case 0x7c:
			// LD A,H
			LD_r8_r8(system, A, H);
			break;
		case 0x7d:
			// LD A,L
			LD_r8_r8(system, A, L);
			break;
		case 0x7e:
			// LD A,(HL)
			LD_r8_HL(system, A);
			break;
		case 0x7f:
			// LD A,A
			LD_r8_r8(system, A, A);
			break;
		case 0x80:
			// ADD A,B
			ADD_A_r8(system, B);
			break;
		case 0x81:
			// ADD A,C
			ADD_A_r8(system, C);
			break;
		case 0x82:
			// ADD A,D
			ADD_A_r8(system, D);
			break;
		case 0x83:
			// ADD A,E
			ADD_A_r8(system, E);
			break;
		case 0x84:
			// ADD A,H
			ADD_A_r8(system, H);
			break;
		case 0x85:
			// ADD A,L
			ADD_A_r8(system, L);
			break;
		case 0x86:
			// ADD A,(HL)
			ADD_A_HL(system);
			break;
		case 0x87:
			// ADD A,A
			ADD_A_r8(system, A);
			break;
		case 0x88:
			// ADC A,B
			ADC_A_r8(system, B);
			break;
		case 0x89:
			// ADC A,C
			ADC_A_r8(system, C);
			break;
		case 0x8a:
			// ADC A,D
			ADC_A_r8(system, D);
			break;
		case 0x8b:
			// ADC A,E
			ADC_A_r8(system, E);
			break;
		case 0x8c:
			// ADC A,H
			ADC_A_r8(system, H);
			break;
		case 0x8d:
			// ADC A,L
			ADC_A_r8(system, L);
			break;
		case 0x8e:
			// ADC A,(HL)
			ADC_A_HL(system);
			break;
		case 0x8f:
			// ADC A,A
			ADC_A_r8(system, A);
			break;
		case 0x90:
			// SUB A,B
			SUB_A_r8(system, B);
			break;
		case 0x91:
			// SUB A,C
			SUB_A_r8(system, C);
			break;
		case 0x92:
			// SUB A,D
			SUB_A_r8(system, D);
			break;
		case 0x93:
			// SUB A,E
			SUB_A_r8(system, E);
			break;
		case 0x94:
			// SUB A,H
			SUB_A_r8(system, H);
			break;
		case 0x95:
			// SUB A,L
			SUB_A_r8(system, L);
			break;
		case 0x96:
			// SUB A,(HL)
			SUB_A_HL(system);
			break;
		case 0x97:
			// SUB A,A
			SUB_A_r8(system, A);
			break;
		case 0x98:
			// SBC A,B
			SBC_A_r8(system, B);
			break;
		case 0x99:
			// SBC A,C
			SBC_A_r8(system, C);
			break;
		case 0x9a:
			// SBC A,D
			SBC_A_r8(system, D);
			break;
		case 0x9b:
			// SBC A,E
			SBC_A_r8(system, E);
			break;
		case 0x9c:
			// SBC A,H
			SBC_A_r8(system, H);
			break;
		case 0x9d:
			// SBC A,L
			SBC_A_r8(system, L);
			break;
		case 0x9e:
			// SBC A,(HL)
			SBC_A_HL(system);
			break;
		case 0x9f:
			// SBC A,A
			SBC_A_r8(system, A);
			break;
		case 0xa0:
			// AND A,B
			AND_A_r8(system, B);
			break;
		case 0xa1:
			// AND A,C
			AND_A_r8(system, C);
			break;
		case 0xa2:
			// AND A,D
			AND_A_r8(system, D);
			break;
		case 0xa3:
			// AND A,E
			AND_A_r8(system, E);
			break;
		case 0xa4:
			// AND A,H
			AND_A_r8(system, H);
			break;
		case 0xa5:
			// AND A,L
			AND_A_r8(system, L);
			break;
		case 0xa6:
			// AND A,(HL)
			AND_A_HL(system);
			break;
		case 0xa7:
			// AND A,A
			AND_A_r8(system, A);
			break;
		case 0xa8:
			// XOR A,B
			XOR_A_r8(system, B);
			break;
		case 0xa9:
			// XOR A,C
			XOR_A_r8(system, C);
			break;
		case 0xaa:
			// XOR A,D
			XOR_A_r8(system, C);
			break;
		case 0xab:
			// XOR A,E
			XOR_A_r8(system, E);
			break;
		case 0xac:
			// XOR A,H
			XOR_A_r8(system, H);
			break;
		case 0xad:
			// XOR A,L
			XOR_A_r8(system, L);
			break;
		case 0xae:
			// XOR A,(HL)
			XOR_A_HL(system);
			break;
		case 0xaf:
			// XOR A,A
			XOR_A_r8(system, A);
			break;
		case 0xb0:
			// OR A,B
			OR_A_r8(system, B);
			break;
		case 0xb1:
			// OR A,C
			OR_A_r8(system, C);
			break;
		case 0xb2:
			// OR A,D
			OR_A_r8(system, D);
			break;
		case 0xb3:
			// OR A,E
			OR_A_r8(system, E);
			break;
		case 0xb4:
			// OR A,H
			OR_A_r8(system, H);
			break;
		case 0xb5:
			// OR A,L
			OR_A_r8(system, L);
			break;
		case 0xb6:
			// OR A,(HL)
			OR_A_HL(system);
			break;
		case 0xb7:
			// OR A,A
			OR_A_r8(system, A);
			break;
		case 0xb8:
			// CP A,B
			CP_A_r8(system, B);
			break;
		case 0xb9:
			// CP A,C
			CP_A_r8(system, C);
			break;
		case 0xba:
			// CP A,D
			CP_A_r8(system, D);
			break;
		case 0xbb:
			// CP A,E
			CP_A_r8(system, E);
			break;
		case 0xbc:
			// CP A,H
			CP_A_r8(system, H);
			break;
		case 0xbd:
			// CP A,L
			CP_A_r8(system, L);
			break;
		case 0xbe:
			// CP A,(HL)
			CP_A_HL(system);
			break;
		case 0xbf:
			// CP A,A
			CP_A_r8(system, A);
			break;
		case 0xc0:
			// RET NZ
			RET_cc(system, NZ);
			break;
		case 0xc1:
			// POP BC
			POP_r16(system, BC);
			break;
		case 0xc2:
			// JP NZ,a16
			JP_cc_n16(system, NZ, n16);
			break;
		case 0xc3:
			// JP a16
			JP_n16(system, n16);
			break;
		case 0xc4:
			// CALL NZ,a16
			CALL_cc_n16(system, NZ, n16);
			break;
		case 0xc5:
			// PUSH BC
			PUSH_r16(system, BC);
			break;
		case 0xc6:
			// ADD A,n8
			ADD_A_n8(system, n8);
			break;
		case 0xc7:
			// RST 00H
			RST_vec(system, 0);
			break;
		case 0xc8:
			// RET Z
			RET_cc(system, Z);
			break;
		case 0xc9:
			// RET
			RET(system);
			break;
		case 0xca:
			// JP Z,a16
			JP_cc_n16(system, Z, n16);
			break;
		case 0xcb:
			// PREFIX CB
			// Should not happen here
			// TODO
			// Throw an error
			break;
		case 0xcc:
			// CALL Z,a16
			CALL_cc_n16(system, Z, n16);
			break;
		case 0xcd:
			// CALL a16
			CALL_n16(system, n16);
			break;
		case 0xce:
			// ADC A,n8
			ADC_A_n8(system, n8);
			break;
		case 0xcf:
			// RST 08H
			RST_vec(system, 0x8);
			break;
		case 0xd0:
			// RET NC
			RET_cc(system, NC);
			break;
		case 0xd1:
			// POP DE
			POP_r16(system, DE);
			break;
		case 0xd2:
			// JP NC,a16
			JP_cc_n16(system, NC, n16);
			break;
		case 0xd3:
			// No instruction
			break;
		case 0xd4:
			// CALL NC,a16
			CALL_cc_n16(system, NC, n16);
			break;
		case 0xd5:
			// PUSH DE
			PUSH_r16(system, DE);
			break;
		case 0xd6:
			// SUB A,n8
			SUB_A_n8(system, n8);
			break;
		case 0xd7:
			// RST 10H
			RST_vec(system, 0x10);
			break;
		case 0xd8:
			// RET C
			RET_cc(system, Cc);
			break;
		case 0xd9:
			// RETI
			RETI(system);
			break;
		case 0xda:
			// JP C,a16
			JP_cc_n16(system, C, n16);
			break;
		case 0xdb:
			// No instruction
			break;
		case 0xdc:
			// CALL C,a16
			CALL_cc_n16(system, C, n16);
			break;
		case 0xdd:
			// No instruction
			break;
		case 0xde:
			// SBC A,n8
			SBC_A_n8(system, n8);
			break;
		case 0xdf:
			// RST 18H
			RST_vec(system, 0x18);
			break;
		case 0xe0:
			// LDH (a8),A
			LDH_n8_A(system, n8);
			break;
		case 0xe1:
			// POP HL
			POP_r16(system, HL);
			break;
		case 0xe2:
			// LD (C),A
			LDH_C_A(system);
			break;
		case 0xe3:
			// No instruction
			break;
		case 0xe4:
			// No instruction
			break;
		case 0xe5:
			// PUSH HL
			PUSH_r16(system, HL);
			break;
		case 0xe6:
			// AND A,n8
			AND_A_n8(system, n8);
			break;
		case 0xe7:
			// RST 20H
			RST_vec(system, 0x20);
			break;
		case 0xe8:
			// ADD SP,e8
			ADD_SP_e8(system, e8);
			break;
		case 0xe9:
			// JP (HL)
			JP_HL(system);
			break;
		case 0xea:
			// LD (a16),A
			LD_n16_A(system, n16);
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
			// XOR A,n8
			XOR_A_n8(system, n8);
			break;
		case 0xef:
			// RST 28H
			RST_vec(system, 0x28);
			break;
		case 0xf0:
			// LDH A,(a8)
			LDH_A_n8(system, n8);
			break;
		case 0xf1:
			// POP AF
			POP_r16(system, AF);
			break;
		case 0xf2:
			// LD A,(C)
			LDH_A_C(system);
			break;
		case 0xf3:
			// DI
			DI(system);
			break;
		case 0xf4:
			// No instruction
			break;
		case 0xf5:
			// PUSH AF
			PUSH_r16(system, AF);
			break;
		case 0xf6:
			// OR A,n8
			OR_A_n8(system, n8);
			break;
		case 0xf7:
			// RST 30H
			RST_vec(system, 0x30);
			break;
		case 0xf8:
			// LD HL,SP+e8
			LD_HL_SP_e8(system, e8);
			break;
		case 0xf9:
			// LD SP,HL
			LD_SP_HL(system);
			break;
		case 0xfa:
			// LD A,(a16)
			LD_A_n16(system, n16);
			break;
		case 0xfb:
			// EI
			EI(system);
			break;
		case 0xfc:
			// No instruction
			break;
		case 0xfd:
			// No instruction
			break;
		case 0xfe:
			// CP A,n8
			CP_A_n8(system, n8);
			break;
		case 0xff:
			// RST 38H
			RST_vec(system, 0x38);
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
	uint8_t inst = system->current_instruction & 0xFF;
	uint8_t inst_low = inst & 0b111;
	uint8_t param[8] = {B, C, D, E, H, L, 0xFF, A};
	uint8_t BIT = (inst & 0b00111000) >> 3;
	switch (inst) {
		case 0x0:
			// RLC B
		case 0x1:
			// RLC C
		case 0x2:
			// RLC D
		case 0x3:
			// RLC E
		case 0x4:
			// RLC H
		case 0x5:
			// RLC L
		case 0x7:
			// RLC A
			RLC_r8(system, param[inst_low]);
			break;
		case 0x6:
			// RLC (HL)
			RLC_HL(system);
			break;
		case 0x8:
			// RRC B
		case 0x9:
			// RRC C
		case 0xa:
			// RRC D
		case 0xb:
			// RRC E
		case 0xc:
			// RRC H
		case 0xd:
			// RRC L
		case 0xf:
			// RRC A
			RRC_r8(system, param[inst_low]);
			break;
		case 0xe:
			// RRC (HL)
			RRC_HL(system);
			break;
		case 0x10:
			// RL B
		case 0x11:
			// RL C
		case 0x12:
			// RL D
		case 0x13:
			// RL E
		case 0x14:
			// RL H
		case 0x15:
			// RL L
		case 0x17:
			// RL A
			RL_r8(system, param[inst_low]);
			break;
		case 0x16:
			// RL (HL)
			RL_HL(system);
			break;
		case 0x18:
			// RR B
		case 0x19:
			// RR C
		case 0x1a:
			// RR D
		case 0x1b:
			// RR E
		case 0x1c:
			// RR H
		case 0x1d:
			// RR L
		case 0x1f:
			// RR A
			RR_r8(system, param[inst_low]);
			break;
		case 0x1e:
			// RR (HL)
			RR_HL(system);
			break;
		case 0x20:
			// SLA B
		case 0x21:
			// SLA C
		case 0x22:
			// SLA D
		case 0x23:
			// SLA E
		case 0x24:
			// SLA H
		case 0x25:
			// SLA L
		case 0x27:
			// SLA A
			SLA_r8(system, param[inst_low]);
			break;
		case 0x26:
			// SLA (HL)
			SLA_HL(system);
			break;
		case 0x28:
			// SRA B
		case 0x29:
			// SRA C
		case 0x2a:
			// SRA D
		case 0x2b:
			// SRA E
		case 0x2c:
			// SRA H
		case 0x2d:
			// SRA L
		case 0x2f:
			// SRA A
			SRA_r8(system, param[inst_low]);
			break;
		case 0x2e:
			// SRA (HL)
			SRA_HL(system);
			break;
		case 0x30:
			// SWAP B
		case 0x31:
			// SWAP C
		case 0x32:
			// SWAP D
		case 0x33:
			// SWAP E
		case 0x34:
			// SWAP H
		case 0x35:
			// SWAP L
		case 0x37:
			// SWAP A
			SWAP_r8(system, param[inst_low]);
			break;
		case 0x36:
			// SWAP (HL)
			SWAP_HL(system);
			break;
		case 0x38:
			// SRL B
		case 0x39:
			// SRL C
		case 0x3a:
			// SRL D
		case 0x3b:
			// SRL E
		case 0x3c:
			// SRL H
		case 0x3d:
			// SRL L
		case 0x3f:
			// SRL A
			SRL_r8(system, param[inst_low]);
			break;
		case 0x3e:
			// SRL (HL)
			SRL_HL(system);
			break;
		case 0x46:
			// BIT 0,(HL)
		case 0x4e:
			// BIT 1,(HL)
		case 0x56:
			// BIT 2,(HL)
		case 0x5e:
			// BIT 3,(HL)
		case 0x66:
			// BIT 4,(HL)
		case 0x6e:
			// BIT 5,(HL)
		case 0x76:
			// BIT 6,(HL)
		case 0x7e:
			// BIT 7,(HL)
			BIT_u3_HL(system, BIT);
			break;
		case 0x40:
			// BIT 0,B
		case 0x41:
			// BIT 0,C
		case 0x42:
			// BIT 0,D
		case 0x43:
			// BIT 0,E
		case 0x44:
			// BIT 0,H
		case 0x45:
			// BIT 0,L
		case 0x47:
			// BIT 0,A
		case 0x48:
			// BIT 1,B
		case 0x49:
			// BIT 1,C
		case 0x4a:
			// BIT 1,D
		case 0x4b:
			// BIT 1,E
		case 0x4c:
			// BIT 1,H
		case 0x4d:
			// BIT 1,L
		case 0x4f:
			// BIT 1,A
		case 0x50:
			// BIT 2,B
		case 0x51:
			// BIT 2,C
		case 0x52:
			// BIT 2,D
		case 0x53:
			// BIT 2,E
		case 0x54:
			// BIT 2,H
		case 0x55:
			// BIT 2,L
		case 0x57:
			// BIT 2,A
		case 0x58:
			// BIT 3,B
		case 0x59:
			// BIT 3,C
		case 0x5a:
			// BIT 3,D
		case 0x5b:
			// BIT 3,E
		case 0x5c:
			// BIT 3,H
		case 0x5d:
			// BIT 3,L
		case 0x5f:
			// BIT 3,A
		case 0x60:
			// BIT 4,B
		case 0x61:
			// BIT 4,C
		case 0x62:
			// BIT 4,D
		case 0x63:
			// BIT 4,E
		case 0x64:
			// BIT 4,H
		case 0x65:
			// BIT 4,L
		case 0x67:
			// BIT 4,A
		case 0x68:
			// BIT 5,B
		case 0x69:
			// BIT 5,C
		case 0x6a:
			// BIT 5,D
		case 0x6b:
			// BIT 5,E
		case 0x6c:
			// BIT 5,H
		case 0x6d:
			// BIT 5,L
		case 0x6f:
			// BIT 5,A
		case 0x70:
			// BIT 6,B
		case 0x71:
			// BIT 6,C
		case 0x72:
			// BIT 6,D
		case 0x73:
			// BIT 6,E
		case 0x74:
			// BIT 6,H
		case 0x75:
			// BIT 6,L
		case 0x77:
			// BIT 6,A
		case 0x78:
			// BIT 7,B
		case 0x79:
			// BIT 7,C
		case 0x7a:
			// BIT 7,D
		case 0x7b:
			// BIT 7,E
		case 0x7c:
			// BIT 7,H
		case 0x7d:
			// BIT 7,L
		case 0x7f:
			// BIT 7,A
			BIT_u3_r8(system, BIT, param[inst_low]);
			break;
		case 0x86:
			// RES 0,(HL)
		case 0x8e:
			// RES 1,(HL)
		case 0x96:
			// RES 2,(HL)
		case 0x9e:
			// RES 3,(HL)
		case 0xa6:
			// RES 4,(HL)
		case 0xae:
			// RES 5,(HL)
		case 0xb6:
			// RES 6,(HL)
		case 0xbe:
			// RES 7,(HL)
			RES_u3_HL(system, BIT);
			break;
		case 0x80:
			// RES 0,B
		case 0x81:
			// RES 0,C
		case 0x82:
			// RES 0,D
		case 0x83:
			// RES 0,E
		case 0x84:
			// RES 0,H
		case 0x85:
			// RES 0,L
		case 0x87:
			// RES 0,A
		case 0x88:
			// RES 1,B
		case 0x89:
			// RES 1,C
		case 0x8a:
			// RES 1,D
		case 0x8b:
			// RES 1,E
		case 0x8c:
			// RES 1,H
		case 0x8d:
			// RES 1,L
		case 0x8f:
			// RES 1,A
		case 0x90:
			// RES 2,B
		case 0x91:
			// RES 2,C
		case 0x92:
			// RES 2,D
		case 0x93:
			// RES 2,E
		case 0x94:
			// RES 2,H
		case 0x95:
			// RES 2,L
		case 0x97:
			// RES 2,A
		case 0x98:
			// RES 3,B
		case 0x99:
			// RES 3,C
		case 0x9a:
			// RES 3,D
		case 0x9b:
			// RES 3,E
		case 0x9c:
			// RES 3,H
		case 0x9d:
			// RES 3,L
		case 0x9f:
			// RES 3,A
		case 0xa0:
			// RES 4,B
		case 0xa1:
			// RES 4,C
		case 0xa2:
			// RES 4,D
		case 0xa3:
			// RES 4,E
		case 0xa4:
			// RES 4,H
		case 0xa5:
			// RES 4,L
		case 0xa7:
			// RES 4,A
		case 0xa8:
			// RES 5,B
		case 0xa9:
			// RES 5,C
		case 0xaa:
			// RES 5,D
		case 0xab:
			// RES 5,E
		case 0xac:
			// RES 5,H
		case 0xad:
			// RES 5,L
		case 0xaf:
			// RES 5,A
		case 0xb0:
			// RES 6,B
		case 0xb1:
			// RES 6,C
		case 0xb2:
			// RES 6,D
		case 0xb3:
			// RES 6,E
		case 0xb4:
			// RES 6,H
		case 0xb5:
			// RES 6,L
		case 0xb7:
			// RES 6,A
		case 0xb8:
			// RES 7,B
		case 0xb9:
			// RES 7,C
		case 0xba:
			// RES 7,D
		case 0xbb:
			// RES 7,E
		case 0xbc:
			// RES 7,H
		case 0xbd:
			// RES 7,L
		case 0xbf:
			// RES 7,A
			RES_u3_r8(system, BIT, param[inst_low]);
			break;
		case 0xc6:
			// SET 0,(HL)
		case 0xce:
			// SET 1,(HL)
		case 0xd6:
			// SET 2,(HL)
		case 0xde:
			// SET 3,(HL)
		case 0xe6:
			// SET 4,(HL)
		case 0xee:
			// SET 5,(HL)
		case 0xf6:
			// SET 6,(HL)
		case 0xfe:
			// SET 7,(HL)
			SET_u3_HL(system, BIT);
			break;
		case 0xc0:
			// SET 0,B
		case 0xc1:
			// SET 0,C
		case 0xc2:
			// SET 0,D
		case 0xc3:
			// SET 0,E
		case 0xc4:
			// SET 0,H
		case 0xc5:
			// SET 0,L
		case 0xc7:
			// SET 0,A
		case 0xc8:
			// SET 1,B
		case 0xc9:
			// SET 1,C
		case 0xca:
			// SET 1,D
		case 0xcb:
			// SET 1,E
		case 0xcc:
			// SET 1,H
		case 0xcd:
			// SET 1,L
		case 0xcf:
			// SET 1,A
		case 0xd0:
			// SET 2,B
		case 0xd1:
			// SET 2,C
		case 0xd2:
			// SET 2,D
		case 0xd3:
			// SET 2,E
		case 0xd4:
			// SET 2,H
		case 0xd5:
			// SET 2,L
		case 0xd7:
			// SET 2,A
		case 0xd8:
			// SET 3,B
		case 0xd9:
			// SET 3,C
		case 0xda:
			// SET 3,D
		case 0xdb:
			// SET 3,E
		case 0xdc:
			// SET 3,H
		case 0xdd:
			// SET 3,L
		case 0xdf:
			// SET 3,A
		case 0xe0:
			// SET 4,B
		case 0xe1:
			// SET 4,C
		case 0xe2:
			// SET 4,D
		case 0xe3:
			// SET 4,E
		case 0xe4:
			// SET 4,H
		case 0xe5:
			// SET 4,L
		case 0xe7:
			// SET 4,A
		case 0xe8:
			// SET 5,B
		case 0xe9:
			// SET 5,C
		case 0xea:
			// SET 5,D
		case 0xeb:
			// SET 5,E
		case 0xec:
			// SET 5,H
		case 0xed:
			// SET 5,L
		case 0xef:
			// SET 5,A
		case 0xf0:
			// SET 6,B
		case 0xf1:
			// SET 6,C
		case 0xf2:
			// SET 6,D
		case 0xf3:
			// SET 6,E
		case 0xf4:
			// SET 6,H
		case 0xf5:
			// SET 6,L
		case 0xf7:
			// SET 6,A
		case 0xf8:
			// SET 7,B
		case 0xf9:
			// SET 7,C
		case 0xfa:
			// SET 7,D
		case 0xfb:
			// SET 7,E
		case 0xfc:
			// SET 7,H
		case 0xfd:
			// SET 7,L
		case 0xff:
			// SET 7,A
			SET_u3_r8(system, BIT, param[inst_low]);
			break;
		default:
			// Throw an error
			break;
	}
}
