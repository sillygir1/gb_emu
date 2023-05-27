#include "instructions.h"

/* Flags */

void static ADD_flags(System* system, uint8_t a, uint8_t b, bool carry) {
    uint16_t result = a + b;
    if (carry) result += GET_FLAG(CARRY);
    SET_FLAG(ZERO, !result);
    SET_FLAG(SUB, 0);
    SET_FLAG(HALFCARRY, (a & 0xF + b & 0xF) & 0x10 == 0x10);
    if (result > 0xFFU) { SET_FLAG(CARRY, 1); } else SET_FLAG(CARRY, 0);
}

void static AND_flags(System* system, uint8_t result) {
    if ((uint8_t)result == 0) { SET_FLAG(ZERO, 1); } else { SET_FLAG(ZERO, 0); };
    SET_FLAG(SUB, 0);
    SET_FLAG(HALFCARRY, 1);
    SET_FLAG(CARRY, 0);
}

void static SUB_flags(System* system, uint8_t a, uint8_t b) {
    bool carry = GET_FLAG(CARRY);
    uint8_t result = a - b;
    SET_FLAG(SUB, 1);
    SET_FLAG(ZERO, !result);
    SET_FLAG(CARRY, a < b);
    SET_FLAG(HALFCARRY, ((a & 0xF) < (b & 0xF)));
}

void static SBC_flags(System* system, uint8_t a, uint8_t b) {
    bool carry = GET_FLAG(CARRY);
    uint8_t result = a - b - carry;
    SET_FLAG(SUB, 1);
    SET_FLAG(ZERO, !result);
    SET_FLAG(CARRY, a < (b + carry));
    SET_FLAG(HALFCARRY, ((a & 0xF) < ((b & 0xF) + carry)));
}

void static DEC_flags(System* system, uint8_t result) {
    SET_FLAG(SUB, true);

    if (result == 0) {
        SET_FLAG(ZERO, true);
    } else SET_FLAG(ZERO, false);

    if (result & 0xF == 0b1111) {
        SET_FLAG(HALFCARRY, true);
    } else SET_FLAG(HALFCARRY, false);

}

void static INC_flags(System* system, uint8_t result) {
    SET_FLAG(SUB, false);
    if (result == 0) { SET_FLAG(ZERO, true); } else SET_FLAG(ZERO, false);
    if ((result - 1) & 0xF == 0b1111) { SET_FLAG(HALFCARRY, true); } else { SET_FLAG(HALFCARRY, false); }
}

void static OR_flags(System* system, uint8_t result) {
    if ((uint8_t)result == 0) { SET_FLAG(ZERO, 1); } else { SET_FLAG(ZERO, 0); };
    SET_FLAG(SUB, 0);
    SET_FLAG(HALFCARRY, 0);
    SET_FLAG(CARRY, 0);
}

void static XOR_flags(System* system, uint8_t result) {
    SET_FLAG(ZERO, !result);
    SET_FLAG(SUB, false);
    SET_FLAG(HALFCARRY, false);
    SET_FLAG(CARRY, false);
}

void static ADD_HL_flags(System* system, uint16_t a, uint16_t b) {
    SET_FLAG(SUB, false);
    SET_FLAG(HALFCARRY, (a & 0xFFF) + (b & 0xFFF) > 0xFFF);
    SET_FLAG(CARRY, (a + b) > 0xFFFF);
}

void static BIT_flags(System* system, bool value) {
    SET_FLAG(ZERO, !value);
    SET_FLAG(SUB, false);
    SET_FLAG(HALFCARRY, true);
}

void static SWAP_flags(System* system, bool value) {
    SET_FLAG(ZERO, !value);
    SET_FLAG(SUB, false);
    SET_FLAG(HALFCARRY, false);
    SET_FLAG(CARRY, false);
}

void static BITSHIFT_flags(System* system, uint8_t result, bool carry) {
    SET_FLAG(ZERO, !result);
    SET_FLAG(SUB, false);
    SET_FLAG(HALFCARRY, false);
    SET_FLAG(CARRY, carry);
}

/* 8-bit arithmetic and logic instructions */

void ADC_A_r8(System* system, uint8_t S, uint8_t r8) {
    uint16_t result = system->registers[S] + system->registers[r8] + GET_FLAG(CARRY);

    ADD_flags(system, system->registers[S], system->registers[r8], 1);
    system->registers[S] = result;
}

void ADC_A_HL(System* system, uint8_t S) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    uint16_t result = system->registers[S] + system->memory[address] + GET_FLAG(CARRY);

    ADD_flags(system, system->registers[S], system->memory[address], 1);
    system->registers[S] = result;
}

void ADC_A_n8(System* system, uint8_t S, uint8_t n8) {
    uint16_t result = system->registers[S] + n8 + GET_FLAG(CARRY);

    ADD_flags(system, system->registers[S], n8, 1);
    system->registers[S] = result;
}

void ADD_A_r8(System* system, uint8_t S, uint8_t r8) {
    uint16_t result = system->registers[S] + system->registers[r8];

    ADD_flags(system, system->registers[S], system->registers[r8], 0);
    system->registers[S] = result;
}

void ADD_A_HL(System* system, uint8_t S) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    uint16_t result = system->registers[S] + system->memory[address];

    ADD_flags(system, system->registers[S], system->memory[address], 0);
    system->registers[S] = result;
}

void ADD_A_n8(System* system, uint8_t S, uint8_t n8) {
    uint16_t result = system->registers[S] + n8;

    ADD_flags(system, system->registers[S], n8, 0);
    system->registers[S] = result;
}

void AND_A_r8(System* system, uint8_t S, uint8_t r8) {
    uint8_t result = system->registers[S] & system->registers[r8];

    AND_flags(system, result);
    system->registers[S] = result;
}

void AND_A_HL(System* system, uint8_t S) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    uint8_t result = system->registers[S] & system->memory[address];

    AND_flags(system, result);
    system->registers[S] = result;
}

void AND_A_n8(System* system, uint8_t S, uint8_t n8) {
    uint8_t result = system->registers[S] & n8;

    AND_flags(system, result);
    system->registers[S] = result;
}

void CP_A_r8(System* system, uint8_t S, uint8_t r8) {
    SUB_flags(system, system->registers[S], system->registers[r8]);
}

void CP_A_HL(System* system, uint8_t S) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    SUB_flags(system, system->registers[S], system->memory[address]);
}

void CP_A_n8(System* system, uint8_t S, uint8_t n8) {
    SUB_flags(system, system->registers[S], n8);
}

void DEC_r8(System* system, uint8_t r8) {
    system->registers[r8] -= 1;
    DEC_flags(system, system->registers[r8]);
}

void DEC_HL(System* system) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    system->memory[address] -= 1;
    DEC_flags(system, system->memory[address]);
}

void INC_r8(System* system, uint8_t r8) {
    system->registers[r8] += 1;
    INC_flags(system, system->registers[r8]);
}

void INC_HL(System* system) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    system->memory[address] += 1;
    INC_flags(system, system->memory[address]);
}

void OR_A_r8(System* system, uint8_t S, uint8_t r8) {
    uint8_t result = system->registers[S] | system->registers[r8];

    OR_flags(system, result);
    system->registers[S] = result;
}

void OR_A_HL(System* system, uint8_t S) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    uint8_t result = system->registers[S] | system->memory[address];

    OR_flags(system, result);
    system->registers[S] = result;
}

void OR_A_n8(System* system, uint8_t S, uint8_t n8) {
    uint8_t result = system->registers[S] | n8;

    OR_flags(system, result);
    system->registers[S] = result;
}

void SBC_A_r8(System* system, uint8_t S, uint8_t r8) {
    uint8_t result = system->registers[S] - system->registers[r8] - GET_FLAG(CARRY);

    SBC_flags(system, system->registers[S], system->registers[r8]);
    system->registers[S] = result;
}

void SBC_A_HL(System* system, uint8_t S) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    uint8_t result = system->registers[S] - system->memory[address] - GET_FLAG(CARRY);

    SBC_flags(system, system->registers[S], system->memory[address]);
    system->registers[S] = result;
}

void SBC_A_n8(System* system, uint8_t S, uint8_t n8) {
    uint8_t result = system->registers[S] - n8 - GET_FLAG(CARRY);

    SBC_flags(system, system->registers[S], n8);
    system->registers[S] = result;
}

void SUB_A_r8(System* system, uint8_t S, uint8_t r8) {
    uint8_t result = system->registers[S] - system->registers[r8];

    SUB_flags(system, system->registers[S], system->registers[r8]);
    system->registers[S] = result;
}

void SUB_A_HL(System* system, uint8_t S) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    uint8_t result = system->registers[S] - system->memory[address];

    SUB_flags(system, system->registers[S], system->memory[address]);
    system->registers[S] = result;
}

void SUB_A_n8(System* system, uint8_t S, uint8_t n8) {
    uint8_t result = system->registers[S] - n8;

    SUB_flags(system, system->registers[S], n8);
    system->registers[S] = result;
}

void XOR_A_r8(System* system, uint8_t S, uint8_t r8) {
    uint8_t result = system->registers[S] ^ system->registers[r8];

    XOR_flags(system, result);
    system->registers[S] = result;
}

void XOR_A_HL(System* system, uint8_t S) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    uint8_t result = system->registers[S] ^ system->memory[address];

    XOR_flags(system, result);
    system->registers[S] = result;
}

void XOR_A_n8(System* system, uint8_t S, uint8_t n8) {
    uint8_t result = system->registers[S] ^ n8;

    XOR_flags(system, result);
    system->registers[S] = result;
}

/* 16-bit arithmetic instructions */

void ADD_HL_r16(System* system, uint8_t r16) {
    uint16_t result = GET_16BIT_REGISTER(HL) + GET_16BIT_REGISTER(r16);
    ADD_HL_flags(system, GET_16BIT_REGISTER(HL), GET_16BIT_REGISTER(r16));
    SET_16BIT_REGISTER(HL, result);
}

void DEC_r16(System* system, uint8_t r16) {
    SET_16BIT_REGISTER(r16, GET_16BIT_REGISTER(r16) - 1);
}

void INC_r16(System* system, uint8_t r16) {
    SET_16BIT_REGISTER(r16, GET_16BIT_REGISTER(r16) + 1);
}

/* Bit operations instructions */

void BIT_u3_r8(System* system, uint8_t u3, uint8_t r8) {
    bool result = system->registers[r8] & (1 << u3);
    BIT_flags(system, result);
}

void BIT_u3_HL(System* system, uint8_t u3) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    bool result = system->memory[address] & (1 << u3);
    BIT_flags(system, result);
}

void RES_u3_r8(System* system, uint8_t u3, uint8_t r8) {
    uint8_t result = system->registers[r8] & ~(1 << u3);
    system->registers[r8] = result;
}

void RES_u3_HL(System* system, uint8_t u3) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    uint8_t result = system->memory[address] & ~(1 << u3);
    system->memory[address] = result;
}

void SET_u3_r8(System* system, uint8_t u3, uint8_t r8) {
    uint8_t result = system->registers[r8] | (1 << u3);
    system->registers[r8] = result;
}

void SET_u3_HL(System* system, uint8_t u3) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    uint8_t result = system->memory[address] | (1 << u3);
    system->memory[address] = result;
}

void SWAP_r8(System* system, uint8_t r8) {
    uint8_t temp = system->registers[r8] & 0xF;
    uint8_t result = (temp << 4) + (system->registers[r8] >> 4);
    SWAP_flags(system, result);
    system->registers[r8] = result;
}

void SWAP_HL(System* system) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    uint8_t temp = system->memory[address] & 0xF;
    uint8_t result = (temp << 4) + (system->memory[address] >> 4);
    SWAP_flags(system, result);
    system->memory[address] = result;
}

/* Bit shift instructions */

void RL_r8(System* system, uint8_t r8) {
    bool carry = system->registers[r8] & (1 << 7);
    uint8_t result = (system->registers[r8] << 1) + GET_FLAG(CARRY);
    BITSHIFT_flags(system, result, carry);
    system->registers[r8] = result;
}

void RL_HL(System* system) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    bool carry = system->memory[address] & (1 << 7);
    uint8_t result = (system->memory[address] << 1) + GET_FLAG(CARRY);
    BITSHIFT_flags(system, result, carry);
    system->memory[address] = result;
}

void RLA(System* system) {
    bool carry = system->registers[A] & (1 << 7);
    uint8_t result = (system->registers[A] << 1) + GET_FLAG(CARRY);
    SET_FLAG(ZERO, false);
    SET_FLAG(SUB, false);
    SET_FLAG(HALFCARRY, false);
    SET_FLAG(CARRY, carry);
    system->registers[A] = result;
}

void RLC_r8(System* system, uint8_t r8) {
    bool carry = system->registers[r8] & (1 << 7);
    uint8_t result = (system->registers[r8] << 1) + carry;
    BITSHIFT_flags(system, result, carry);
    system->registers[r8] = result;
}

void RLC_HL(System* system) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    bool carry = system->memory[address] & (1 << 7);
    uint8_t result = (system->memory[address] << 1) + carry;
    BITSHIFT_flags(system, result, carry);
    system->memory[address] = result;
}

void RLCA(System* system) {
    bool carry = system->registers[A] & (1 << 7);
    uint8_t result = (system->registers[A] << 1) + carry;
    SET_FLAG(ZERO, false);
    SET_FLAG(SUB, false);
    SET_FLAG(HALFCARRY, false);
    SET_FLAG(CARRY, carry);
    system->registers[A] = result;
}

void RR_r8(System* system, uint8_t r8) {
    bool carry = system->registers[r8] & 1;
    uint8_t result = (system->registers[r8] >> 1) + (GET_FLAG(CARRY) << 7);
    BITSHIFT_flags(system, result, carry);
    system->registers[r8] = result;
}

void RR_HL(System* system) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    bool carry = system->memory[address] & 1;
    uint8_t result = (system->memory[address] >> 1) + (GET_FLAG(CARRY) << 7);
    BITSHIFT_flags(system, result, carry);
    system->memory[address] = result;
}

void RRA(System* system) {
    bool carry = system->registers[A] & 1;
    uint8_t result = (system->registers[A] >> 1) + (GET_FLAG(CARRY) << 7);
    SET_FLAG(ZERO, false);
    SET_FLAG(SUB, false);
    SET_FLAG(HALFCARRY, false);
    SET_FLAG(CARRY, carry);
    system->registers[A] = result;
}

void RRC_r8(System* system, uint8_t r8) {
    bool carry = system->registers[r8] & 1;
    uint8_t result = (system->registers[r8] >> 1) + (carry << 7);
    BITSHIFT_flags(system, result, carry);
    system->registers[r8] = result;
}

void RRC_HL(System* system) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    bool carry = system->memory[address] & 1;
    uint8_t result = (system->memory[address] >> 1) + (carry << 7);
    BITSHIFT_flags(system, result, carry);
    system->memory[address] = result;
}

void RRCA(System* system) {
    bool carry = system->registers[A] & 1;
    uint8_t result = (system->registers[A] >> 1) + (carry << 7);
    SET_FLAG(ZERO, false);
    SET_FLAG(SUB, false);
    SET_FLAG(HALFCARRY, false);
    SET_FLAG(CARRY, carry);
    system->registers[A] = result;
}

void SLA_r8(System* system, uint8_t r8) {
    bool carry = system->registers[r8] & (1 << 7);
    uint8_t result = system->registers[r8] << 1;
    BITSHIFT_flags(system, result, carry);
    system->registers[r8] = result;
}

void SLA_HL(System* system) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    bool carry = system->memory[address] & (1 << 7);
    uint8_t result = system->memory[address] << 1;
    BITSHIFT_flags(system, result, carry);
    system->memory[address] = result;
}

void SRA_r8(System* system, uint8_t r8) {
    bool carry = system->registers[r8] & 1;
    uint8_t result = (system->registers[r8] >> 1) + (system->registers[r8] & (1 << 7));
    BITSHIFT_flags(system, result, carry);
    system->registers[r8] = result;
}

void SRA_HL(System* system) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    bool carry = system->memory[address] & 1;
    uint8_t result = (system->memory[address] >> 1) + (system->memory[address] & (1 << 7));
    BITSHIFT_flags(system, result, carry);
    system->memory[address] = result;
}

void SRL_r8(System* system, uint8_t r8) {
    bool carry = system->registers[r8] & 1;
    uint8_t result = system->registers[r8] >> 1;
    BITSHIFT_flags(system, result, carry);
    system->registers[r8] = result;
}

void SRL_HL(System* system) {
    uint16_t address = GET_16BIT_REGISTER(HL);
    bool carry = system->memory[address] & 1;
    uint8_t result = (system->memory[address] >> 1);
    BITSHIFT_flags(system, result, carry);
    system->memory[address] = result;
}

/* Stack operations instructions */

void ADD_HL_SP(System* system) {
    uint16_t result = GET_16BIT_REGISTER(HL) + GET_16BIT_REGISTER(SP);
    ADD_HL_flags(system, GET_16BIT_REGISTER(HL), GET_16BIT_REGISTER(SP));
    SET_16BIT_REGISTER(HL, result);
}

void ADD_SP_e8(System* system, uint8_t e8) {
    // TODO
}