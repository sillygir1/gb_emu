#pragma once
#include <stdint.h>

#include "registers.h"
#include "system.h"

// Add the value in r8 plus the carry flag to S.
// @param system System struct
// @param S Add to (Can't have letter A because defines)
// @param r8 Value source
void ADC_A_r8(System* system, uint8_t S, uint8_t r8);

// Add the value in [HL] plus the carry flag to S.
// @param system System struct
// @param S Add to (Can't have letter A because defines)
void ADC_A_HL(System* sys, uint8_t S);

// Add immediate value n8 plus the carry flag to S.
// @param system System struct
// @param S Add to (Can't have letter A because defines)
// @param n8 Immediate value
void ADC_A_n8(System* system, uint8_t S, uint8_t n8);

// Add the value in r8 to S.
// @param system System struct
// @param S Add to (Can't have letter A because defines)
// @param r8 Value source
void ADD_A_r8(System* system, uint8_t S, uint8_t r8);

// Add the value in [HL] to S.
// @param system System struct
// @param S Add to (Can't have letter A because defines)
void ADD_A_HL(System* system, uint8_t S);

// Add immediate value n8 to S.
// @param system System struct
// @param S Add to (Can't have letter A because defines)
// @param n8 Immediate value
void ADD_A_n8(System* system, uint8_t S, uint8_t n8);