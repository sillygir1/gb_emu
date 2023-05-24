#include "instructions.h"

void static ADD_flags(System* system, uint16_t result) {
    SET_FLAG(SUB, false);
    if ((uint8_t)result == 0) SET_FLAG(ZERO, true);
    if (result > 0xFU) SET_FLAG(HALFCARRY, true);
    if (result > 0xFFU) { SET_FLAG(CARRY, true); } else SET_FLAG(CARRY, false);
}

void ADC_A_r8(System* system, uint8_t S, uint8_t r8) {
    uint16_t result = system->registers[S] + system->registers[r8];
    if (GET_FLAG(CARRY)) result += 1;

    ADD_flags(system, result);
    system->registers[S] = result;
}

void ADC_A_HL(System* system, uint8_t S) {
    uint16_t address = get_GPR16bit(system->registers, HL);
    uint16_t result = system->registers[S] + system->memory[address];

    if (GET_FLAG(CARRY)) result += 1;
    ADD_flags(system, result);
    system->registers[S] = result;
}

void ADC_A_n8(System* system, uint8_t S, uint8_t n8) {
    uint16_t result = system->registers[S] + n8;
    if (GET_FLAG(CARRY)) result += 1;

    ADD_flags(system, result);
    system->registers[S] = result;
}

void ADD_A_r8(System* system, uint8_t S, uint8_t r8) {
    uint16_t result = system->registers[S] + system->registers[r8];
    ADD_flags(system, result);
    system->registers[S] = result;
}

void ADD_A_HL(System* system, uint8_t S) {
    uint16_t address = get_GPR16bit(system->registers, HL);
    uint16_t result = system->registers[S] + system->memory[address];

    ADD_flags(system, result);
    system->registers[S] = result;
}

void ADD_A_n8(System* system, uint8_t S, uint8_t n8) {
    uint16_t result = system->registers[S] + n8;

    ADD_flags(system, result);
    system->registers[S] = result;
}