#pragma once
#include <stdint.h>

#include "registers.h"
#include "system.h"

#define SET_FLAG(flag, value) set_flag(system->registers, flag, value)
#define GET_FLAG(flag) get_flag(system->registers, flag)

// Add the value in r8 plus the carry flag to S.
// @param registers Registers array
// @param S Add to (Can't have letter A because defines)
// @param r8 Value source
void ADC_A_r8(System* system, uint8_t S, uint8_t r8);

// Add the value in [HL] plus the carry flag to S.
// @param registers Registers array
// @param S Add to (Can't have letter A because defines)
void ADC_A_HL(System* sys, uint8_t S);

// Add n8 plus the carry flag to S.
// @param registers Registers array
// @param S Add to (Can't have letter A because defines)
// @param n8 Value
void ADC_A_n8(System* system, uint8_t S, uint8_t n8);