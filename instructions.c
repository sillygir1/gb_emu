#include "instructions.h"

void static ADD_flags(System* system, uint8_t a, uint8_t b, bool carry) {
    uint16_t result = a + b;
    if (carry) result += GET_FLAG(CARRY);
    if ((uint8_t)result == 0) { SET_FLAG(ZERO, 1); } else { SET_FLAG(ZERO, 0); };
    SET_FLAG(SUB, 0);
    if ((a & 0xF + b & 0xF) & 0x10 == 0x10) {
        SET_FLAG(HALFCARRY, true);
    } else {
        SET_FLAG(HALFCARRY, false);
    }
    if (result > 0xFFU) { SET_FLAG(CARRY, 1); } else SET_FLAG(CARRY, 0);
}

void static AND_flags(System* system, uint8_t result) {
    if ((uint8_t)result == 0) { SET_FLAG(ZERO, 1); } else { SET_FLAG(ZERO, 0); };
    SET_FLAG(SUB, 0);
    SET_FLAG(HALFCARRY, 1);
    SET_FLAG(CARRY, 0);
}

void static CP_flags(System* system, uint8_t a, uint8_t b) {
    uint8_t result = a - b;
    if ((uint8_t)result == 0) { SET_FLAG(ZERO, 1); } else { SET_FLAG(ZERO, 0); };
    if ((a & 0xF < b & 0xF)) { SET_FLAG(HALFCARRY, true); } else { SET_FLAG(HALFCARRY, false); }
    if (a < b) { SET_FLAG(CARRY, true); } else { SET_FLAG(CARRY, false); }
    SET_FLAG(SUB, 1);
}

void static DEC_flags(System* system, uint8_t value) {
    SET_FLAG(SUB, true);

    if (value == 0) {
        SET_FLAG(ZERO, true);
    } else SET_FLAG(ZERO, false);

    if (value & 0xF == 0b1111) {
        SET_FLAG(HALFCARRY, true);
    } else SET_FLAG(HALFCARRY, false);

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
    uint16_t result = system->registers[S] & system->memory[address];

    AND_flags(system, result);
    system->registers[S] = result;
}

void AND_A_n8(System* system, uint8_t S, uint8_t n8) {
    uint8_t result = system->registers[S] & n8;

    AND_flags(system, result);
    system->registers[S] = result;
}

void CP_A_r8(System* system, uint8_t S, uint8_t r8) {
    CP_flags(system, system->registers[S], system->registers[r8]);
}

void CP_A_HL(System* system, uint8_t S) {
    uint16_t address = get_GPR16bit(system->registers, HL);
    CP_flags(system, system->registers[S], system->memory[address]);
}

void CP_A_n8(System* system, uint8_t S, uint8_t n8) {
    CP_flags(system, system->registers[S], n8);
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