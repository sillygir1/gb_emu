#pragma once
#include <stdint.h>

#include "registers.h"
#include "system.h"

/* 8-bit arithmetic and logic instructions */


// Add the value in r8 plus the carry flag to S.
/// @param system System struct
/// @param S Add to (Can't have letter A because defines)
/// @param r8 Value source
void ADC_A_r8(System* system, uint8_t S, uint8_t r8);

// Add the value in [HL] plus the carry flag to S.
/// @param system System struct
/// @param S Add to (Can't have letter A because defines)
void ADC_A_HL(System* sys, uint8_t S);

// Add immediate value n8 plus the carry flag to S.
/// @param system System struct
/// @param S Add to (Can't have letter A because defines)
/// @param n8 Immediate value
void ADC_A_n8(System* system, uint8_t S, uint8_t n8);

// Add the value in r8 to S.
/// @param system System struct
/// @param S Add to (Can't have letter A because defines)
/// @param r8 Value source
void ADD_A_r8(System* system, uint8_t S, uint8_t r8);

// Add the value in [HL] to S.
/// @param system System struct
/// @param S Add to (Can't have letter A because defines)
void ADD_A_HL(System* system, uint8_t S);

// Add immediate value n8 to S.
/// @param system System struct
/// @param S Add to (Can't have letter A because defines)
/// @param n8 Immediate value
void ADD_A_n8(System* system, uint8_t S, uint8_t n8);

// Bitwise AND between the value in r8 and S.
/// @param system System struct
/// @param S
/// @param r8
void AND_A_r8(System* system, uint8_t S, uint8_t r8);

// Bitwise AND between the byte pointed to by HL and S.
/// @param system System struct
/// @param S
void AND_A_HL(System* system, uint8_t S);

// Bitwise AND between immediate value n8 and S.
/// @param system System struct
/// @param S
/// @param n8 Immediate value
void AND_A_n8(System* system, uint8_t S, uint8_t n8);

// Subtract the value in r8 from S and set flags accordingly.
/// @param system System struct
/// @param S
/// @param r8
void CP_A_r8(System* system, uint8_t S, uint8_t r8);

// Subtract the byte pointed to by HL from S and set flags accordingly.
/// @param system System struct
/// @param S
void CP_A_HL(System* system, uint8_t S);

// Subtract immediate value n8 from S and set flags accordingly.
/// @param S
/// @param n8 Immediate value
void CP_A_n8(System* system, uint8_t S, uint8_t n8);

//Decrement value in register r8 by 1.
/// @param system System struct
/// @param r8
void DEC_r8(System* system, uint8_t r8);

//Decrement the byte pointed to by HL by 1.
/// @param system System struct
void DEC_HL(System* system);

// Increment value in register r8 by 1.
/// @param system System struct
/// @param r8
void INC_r8(System* system, uint8_t r8);

//Increment the byte pointed to by HL by 1.
/// @param system System struct
void INC_HL(System* system);

// Bitwise OR between the value in r8 and S.
/// @param system System struct
/// @param S
/// @param r8
void OR_A_r8(System* system, uint8_t S, uint8_t r8);

// Bitwise OR between the byte pointed to by HL and S.
/// @param system System struct
/// @param S
void OR_A_HL(System* system, uint8_t S);

// Bitwise OR between immediate value n8 and S.
/// @param system System struct
/// @param S
/// @param n8 Immediate value
void OR_A_n8(System* system, uint8_t S, uint8_t n8);

//Subtract the value in r8 and the carry flag from S.
/// @param system System struct
/// @param S
/// @param r8
void SBC_A_r8(System* system, uint8_t S, uint8_t r8);

//Subtract the byte pointed to by HL and the carry flag from S.
/// @param system System struct
/// @param S
void SBC_A_HL(System* system, uint8_t S);

//Subtract immediate value n8 and the carry flag from S.
/// @param system System struct
/// @param S
/// @param n8 Immediate value
void SBC_A_n8(System* system, uint8_t S, uint8_t n8);

//Subtract the value in r8 from S.
/// @param system System struct
/// @param S
/// @param r8
void SUB_A_r8(System* system, uint8_t S, uint8_t r8);

//Subtract the byte pointed to by HL from S.
/// @param system System struct
/// @param S
void SUB_A_HL(System* system, uint8_t S);

//Subtract immediate value n8 from S.
/// @param system System struct
/// @param S
/// @param n8 Immediate value
void SUB_A_n8(System* system, uint8_t S, uint8_t n8);

// Bitwise XOR between the value in r8 and S.
/// @param system System struct
/// @param S 
/// @param r8
void XOR_A_r8(System* system, uint8_t S, uint8_t r8);

// Bitwise XOR between the byte pointed to by HL and S.
/// @param system System struct
/// @param S
void XOR_A_HL(System* system, uint8_t S);

// Bitwise XOR between immediate value n8 and S.
/// @param system System struct
/// @param S
/// @param n8 Immediate value
void XOR_A_n8(System* system, uint8_t S, uint8_t n8);

/* 16-bit arithmetic instructions */

//Add the value in r16 to HL.
/// @param system System struct
/// @param r16
void ADD_HL_r16(System* system, uint8_t r16);

// Decrement value in register r16 by 1.
/// @param system System struct
/// @param r16
void DEC_r16(System* system, uint8_t r16);

// Increment value in register r16 by 1.
/// @param system System struct
/// @param r16
void INC_r16(System* system, uint8_t r16);

/* Bit operations instructions */

// Test bit u3 in register r8, set the zero flag if bit not set.
/// @param system System struct
/// @param u3
/// @param r8
void BIT_u3_r8(System* system, uint8_t u3, uint8_t r8);

// Test bit u3 in the byte pointed by HL, set the zero flag if bit not set.
/// @param system System struct
/// @param u3
void BIT_u3_HL(System* system, uint8_t u3);

// Set bit u3 in register r8 to 0. Bit 0 is the rightmost one, bit 7 the leftmost one.
/// @param system System struct
/// @param u3
/// @param r8
void RES_u3_r8(System* system, uint8_t u3, uint8_t r8);

// Set bit u3 in the byte pointed by HL to 0. Bit 0 is the rightmost one, bit 7 the leftmost one.
/// @param system System struct
/// @param u3
void RES_u3_HL(System* system, uint8_t u3);

// Set bit u3 in register r8 to 1. Bit 0 is the rightmost one, bit 7 the leftmost one.
/// @param system System struct
/// @param u3
/// @param r8
void SET_u3_r8(System* system, uint8_t u3, uint8_t r8);

// Set bit u3 in the byte pointed by HL to 1. Bit 0 is the rightmost one, bit 7 the leftmost one.
/// @param system System struct
/// @param u3
void SET_u3_HL(System* system, uint8_t u3);

// Swap the upper 4 bits in register r8 and the lower 4 ones.
/// @param system System struct
/// @param r8
void SWAP_r8(System* system, uint8_t r8);

//Swap the upper 4 bits in the byte pointed by HL and the lower 4 ones.
/// @param system System struct
void SWAP_HL(System* system);

/* Bit shift instructions */

// Rotate bits in register r8 left through carry.
/// @param system System struct
/// @param r8
void RL_r8(System* system, uint8_t r8);

// Rotate the byte pointed to by HL left through carry.
/// @param system System struct
void RL_HL(System* system);

// Rotate register A left through carry.
/// @param system System struct
void RLA(System* system);

// Rotate register r8 left.
/// @param system System struct
/// @param r8
void RLC_r8(System* system, uint8_t r8);

// Rotate the byte pointed to by HL left.
/// @param system System struct
void RLC_HL(System* system);

// Rotate register A left.
/// @param system System struct
void RLCA(System* system);

// Rotate register r8 right through carry.
/// @param system System struct
/// @param r8
void RR_r8(System* system, uint8_t r8);

// Rotate the byte pointed to by HL right through carry.
/// @param system System struct
void RR_HL(System* system);

// Rotate register A right through carry.
/// @param system System struct
void RRA(System* system);

// Rotate register r8 right.
/// @param system System struct
/// @param r8
void RRC_r8(System* system, uint8_t r8);

// Rotate the byte pointed to by HL right.
/// @param system System struct
void RRC_HL(System* system);

// Rotate register A right.
/// @param system System struct
void RRCA(System* system);

// Shift Left Arithmetically register r8.
/// @param system System struct
/// @param r8
void SLA_r8(System* system, uint8_t r8);

// Shift Left Arithmetically the byte pointed to by HL.
/// @param system System struct
void SLA_HL(System* system);

// Shift Right Arithmetically register r8.
/// @param system System struct
/// @param r8
void SRA_r8(System* system, uint8_t r8);

// Shift Right Arithmetically the byte pointed to by HL.
/// @param system System struct
void SRA_HL(System* system);

// Shift Right Logically register r8.
/// @param system System struct
/// @param r8
void SRL_r8(System* system, uint8_t r8);

// Shift Right Logically the byte pointed to by HL.
/// @param system System struct
void SRL_HL(System* system);

/* Stack operations instructions */

// Add the value in SP to HL.
/// @param system System struct
void ADD_HL_SP(System* system);

// Add the signed value e8 to SP.
/// @param system System struct
/// @param e8 Signed value
void ADD_SP_e8(System* system, uint8_t e8);