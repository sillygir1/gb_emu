#include "instructions.h"

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

void ADC_A_r8(System* system, uint8_t S, uint8_t r8) {
    uint16_t result = system->registers[S] + system->registers[r8] + GET_FLAG(CARRY);

    ADD_flags(system, system->registers[S], system->registers[r8], 1);
    system->registers[S] = result;
}

void ADC_A_HL(System* system, uint8_t S) {
    uint16_t address = get_GPR16bit(system->registers, HL);
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
    uint16_t address = get_GPR16bit(system->registers, HL);
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
    uint16_t address = get_GPR16bit(system->registers, HL);
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
    uint16_t address = get_GPR16bit(system->registers, HL);
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
    uint16_t address = get_GPR16bit(system->registers, HL);
    system->memory[address] -= 1;
    DEC_flags(system, system->memory[address]);
}

void INC_r8(System* system, uint8_t r8) {
    system->registers[r8] += 1;
    INC_flags(system, system->registers[r8]);
}

void INC_HL(System* system) {
    uint16_t address = get_GPR16bit(system->registers, HL);
    system->memory[address] += 1;
    INC_flags(system, system->memory[address]);
}

void OR_A_r8(System* system, uint8_t S, uint8_t r8) {
    uint8_t result = system->registers[S] | system->registers[r8];

    OR_flags(system, result);
    system->registers[S] = result;
}

void OR_A_HL(System* system, uint8_t S) {
    uint16_t address = get_GPR16bit(system->registers, HL);
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
    uint16_t address = get_GPR16bit(system->registers, HL);
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
    uint16_t address = get_GPR16bit(system->registers, HL);
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
    uint16_t address = get_GPR16bit(system->registers, HL);
    uint8_t result = system->registers[S] ^ system->memory[address];

    XOR_flags(system, result);
    system->registers[S] = result;
}

void XOR_A_n8(System* system, uint8_t S, uint8_t n8) {
    uint8_t result = system->registers[S] ^ n8;

    XOR_flags(system, result);
    system->registers[S] = result;
}
