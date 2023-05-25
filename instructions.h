#pragma once
#include <stdint.h>

#include "registers.h"
#include "system.h"

/* 8-Bit instructions */

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

// Bitwise AND between the value in r8 and S.
// @param system System struct
// @param S
// @param r8
void AND_A_r8(System* system, uint8_t S, uint8_t r8);

// Bitwise AND between the byte pointed to by HL and S.
// @param system System struct
// @param S
void AND_A_HL(System* system, uint8_t S);

// Bitwise AND between immediate value n8 and S.
// @param system System struct
// @param S
// @param n8 Immediate value
void AND_A_n8(System* system, uint8_t S, uint8_t n8);

// Subtract the value in r8 from S and set flags accordingly.
// @param system System struct
// @param S
// @param r8
void CP_A_r8(System* system, uint8_t S, uint8_t r8);

// Subtract the byte pointed to by HL from S and set flags accordingly.
// @param system System struct
// @param S
void CP_A_HL(System* system, uint8_t S);

// Subtract immediate value n8 from S and set flags accordingly.
// @param S
// @param n8 Immediate value
void CP_A_n8(System* system, uint8_t S, uint8_t n8);

//Decrement value in register r8 by 1.
// @param system System struct
// @param r8
void DEC_r8(System* system, uint8_t r8);

//Decrement the byte pointed to by HL by 1.
// @param system System struct
void DEC_HL(System* system);

// Increment value in register r8 by 1.
// @param system System struct
// @param r8
void INC_r8(System* system, uint8_t r8);

//Increment the byte pointed to by HL by 1.
// @param system System struct
void INC_HL(System* system);

// Bitwise OR between the value in r8 and S.
// @param system System struct
// @param S
// @param r8
void OR_A_r8(System* system, uint8_t S, uint8_t r8);

// Bitwise OR between the byte pointed to by HL and S.
// @param system System struct
// @param S
void OR_A_HL(System* system, uint8_t S);

// Bitwise OR between immediate value n8 and S.
// @param system System struct
// @param S
// @param n8 Immediate value
void OR_A_n8(System* system, uint8_t S, uint8_t n8);

//Subtract the value in r8 and the carry flag from S.
// @param system System struct
// @param S
// @param r8
void SBC_A_r8(System* system, uint8_t S, uint8_t r8);

//Subtract the byte pointed to by HL and the carry flag from S.
// @param system System struct
// @param S
void SBC_A_HL(System* system, uint8_t S);

//Subtract immediate value n8 and the carry flag from S.
// @param system System struct
// @param S
// @param n8 Immediate value
void SBC_A_n8(System* system, uint8_t S, uint8_t n8);

//Subtract the value in r8 from S.
// @param system System struct
// @param S
// @param r8
void SUB_A_r8(System* system, uint8_t S, uint8_t r8);

//Subtract the byte pointed to by HL from S.
// @param system System struct
// @param S
void SUB_A_HL(System* system, uint8_t S);

//Subtract immediate value n8 from S.
// @param system System struct
// @param S
// @param n8 Immediate value
void SUB_A_n8(System* system, uint8_t S, uint8_t n8);

// Bitwise XOR between the value in r8 and S.
// @param system System struct
// @param S 
// @param r8
void XOR_A_r8(System* system, uint8_t S, uint8_t r8);

// Bitwise XOR between the byte pointed to by HL and S.
// @param system System struct
// @param S
void XOR_A_HL(System* system, uint8_t S);

// Bitwise XOR between immediate value n8 and S.
// @param system System struct
// @param S
// @param n8 Immediate value
void XOR_A_n8(System* system, uint8_t S, uint8_t n8);