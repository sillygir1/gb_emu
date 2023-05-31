#pragma once
#include <stdint.h>

#include "registers.h"
#include "system.h"

/* 8-bit arithmetic and logic instructions */


/// @brief Add the value in r8 plus the carry flag to A.
/// @param system System struct
/// @param r8 Value source
void ADC_A_r8(System* system, uint8_t r8);

/// @brief Add the value in [HL] plus the carry flag to A.
/// @param system System struct
void ADC_A_HL(System* sys);

/// @brief Add immediate value n8 plus the carry flag to A.
/// @param system System struct
/// @param n8 Immediate value
void ADC_A_n8(System* system, uint8_t n8);

/// @brief Add the value in r8 to A.
/// @param system System struct
/// @param r8 Value source
void ADD_A_r8(System* system, uint8_t r8);

/// @brief Add the value in [HL] to A.
/// @param system System struct
void ADD_A_HL(System* system);

/// @brief Add immediate value n8 to A.
/// @param system System struct
/// @param n8 Immediate value
void ADD_A_n8(System* system, uint8_t n8);

/// @brief Bitwise AND between the value in r8 and A.
/// @param system System struct
/// @param r8
void AND_A_r8(System* system, uint8_t r8);

/// @brief Bitwise AND between the byte pointed to by HL and A.
/// @param system System struct
void AND_A_HL(System* system);

/// @brief Bitwise AND between immediate value n8 and A.
/// @param system System struct
/// @param n8 Immediate value
void AND_A_n8(System* system, uint8_t n8);

/// @brief Subtract the value in r8 from A and set flags accordingly.
/// @param system System struct
/// @param r8
void CP_A_r8(System* system, uint8_t r8);

/// @brief Subtract the byte pointed to by HL from A and set flags accordingly.
/// @param system System struct
void CP_A_HL(System* system);

/// @brief Subtract immediate value n8 from A and set flags accordingly.
/// @param n8 Immediate value
void CP_A_n8(System* system, uint8_t n8);

/// @brief Decrement value in register r8 by 1.
/// @param system System struct
/// @param r8
void DEC_r8(System* system, uint8_t r8);

/// @brief Decrement the byte pointed to by HL by 1.
/// @param system System struct
void DEC_HL(System* system);

/// @brief Increment value in register r8 by 1.
/// @param system System struct
/// @param r8
void INC_r8(System* system, uint8_t r8);

/// @brief Increment the byte pointed to by HL by 1.
/// @param system System struct
void INC_HL(System* system);

/// @brief Bitwise OR between the value in r8 and A.
/// @param system System struct
/// @param r8
void OR_A_r8(System* system, uint8_t r8);

/// @brief Bitwise OR between the byte pointed to by HL and A.
/// @param system System struct
void OR_A_HL(System* system);

/// @brief Bitwise OR between immediate value n8 and A.
/// @param system System struct
/// @param n8 Immediate value
void OR_A_n8(System* system, uint8_t n8);

/// @brief Subtract the value in r8 and the carry flag from A.
/// @param system System struct
/// @param r8
void SBC_A_r8(System* system, uint8_t r8);

/// @brief Subtract the byte pointed to by HL and the carry flag from A.
/// @param system System struct
void SBC_A_HL(System* system);

/// @brief Subtract immediate value n8 and the carry flag from A.
/// @param system System struct
/// @param n8 Immediate value
void SBC_A_n8(System* system, uint8_t n8);

/// @brief Subtract the value in r8 from A.
/// @param system System struct
/// @param r8
void SUB_A_r8(System* system, uint8_t r8);

/// @brief Subtract the byte pointed to by HL from A.
/// @param system System struct
void SUB_A_HL(System* system);

/// @brief Subtract immediate value n8 from A.
/// @param system System struct
/// @param n8 Immediate value
void SUB_A_n8(System* system, uint8_t n8);

/// @brief Bitwise XOR between the value in r8 and A.
/// @param system System struct
/// @param r8
void XOR_A_r8(System* system, uint8_t r8);

/// @brief Bitwise XOR between the byte pointed to by HL and A.
/// @param system System struct
void XOR_A_HL(System* system);

/// @brief Bitwise XOR between immediate value n8 and A.
/// @param system System struct
/// @param n8 Immediate value
void XOR_A_n8(System* system, uint8_t n8);

/* 16-bit arithmetic instructions */

/// @brief Add the value in r16 to HL.
/// @param system System struct
/// @param r16
void ADD_HL_r16(System* system, uint8_t r16);

/// @brief Decrement value in register r16 by 1.
/// @param system System struct
/// @param r16
void DEC_r16(System* system, uint8_t r16);

/// @brief Increment value in register r16 by 1.
/// @param system System struct
/// @param r16
void INC_r16(System* system, uint8_t r16);

/* Bit operations instructions */

/// @brief Test bit u3 in register r8, set the zero flag if bit not set.
/// @param system System struct
/// @param u3
/// @param r8
void BIT_u3_r8(System* system, uint8_t u3, uint8_t r8);

/// @brief Test bit u3 in the byte pointed by HL, set the zero flag if bit not set.
/// @param system System struct
/// @param u3
void BIT_u3_HL(System* system, uint8_t u3);

/// @brief Set bit u3 in register r8 to 0. Bit 0 is the rightmost one, bit 7 the leftmost one.
/// @param system System struct
/// @param u3
/// @param r8
void RES_u3_r8(System* system, uint8_t u3, uint8_t r8);

/// @brief Set bit u3 in the byte pointed by HL to 0. Bit 0 is the rightmost one, bit 7 the leftmost one.
/// @param system System struct
/// @param u3
void RES_u3_HL(System* system, uint8_t u3);

/// @brief Set bit u3 in register r8 to 1. Bit 0 is the rightmost one, bit 7 the leftmost one.
/// @param system System struct
/// @param u3
/// @param r8
void SET_u3_r8(System* system, uint8_t u3, uint8_t r8);

/// @brief Set bit u3 in the byte pointed by HL to 1. Bit 0 is the rightmost one, bit 7 the leftmost one.
/// @param system System struct
/// @param u3
void SET_u3_HL(System* system, uint8_t u3);

/// @brief Swap the upper 4 bits in register r8 and the lower 4 ones.
/// @param system System struct
/// @param r8
void SWAP_r8(System* system, uint8_t r8);

//Swap the upper 4 bits in the byte pointed by HL and the lower 4 ones.
/// @param system System struct
void SWAP_HL(System* system);

/* Bit shift instructions */

/// @brief Rotate bits in register r8 left through carry.
/// @param system System struct
/// @param r8
void RL_r8(System* system, uint8_t r8);

/// @brief Rotate the byte pointed to by HL left through carry.
/// @param system System struct
void RL_HL(System* system);

/// @brief Rotate register A left through carry.
/// @param system System struct
void RLA(System* system);

/// @brief Rotate register r8 left.
/// @param system System struct
/// @param r8
void RLC_r8(System* system, uint8_t r8);

/// @brief Rotate the byte pointed to by HL left.
/// @param system System struct
void RLC_HL(System* system);

/// @brief Rotate register A left.
/// @param system System struct
void RLCA(System* system);

/// @brief Rotate register r8 right through carry.
/// @param system System struct
/// @param r8
void RR_r8(System* system, uint8_t r8);

/// @brief Rotate the byte pointed to by HL right through carry.
/// @param system System struct
void RR_HL(System* system);

/// @brief Rotate register A right through carry.
/// @param system System struct
void RRA(System* system);

/// @brief Rotate register r8 right.
/// @param system System struct
/// @param r8
void RRC_r8(System* system, uint8_t r8);

/// @brief Rotate the byte pointed to by HL right.
/// @param system System struct
void RRC_HL(System* system);

/// @brief Rotate register A right.
/// @param system System struct
void RRCA(System* system);

/// @brief Shift Left Arithmetically register r8.
/// @param system System struct
/// @param r8
void SLA_r8(System* system, uint8_t r8);

/// @brief Shift Left Arithmetically the byte pointed to by HL.
/// @param system System struct
void SLA_HL(System* system);

/// @brief Shift Right Arithmetically register r8.
/// @param system System struct
/// @param r8
void SRA_r8(System* system, uint8_t r8);

/// @brief Shift Right Arithmetically the byte pointed to by HL.
/// @param system System struct
void SRA_HL(System* system);

/// @brief Shift Right Logically register r8.
/// @param system System struct
/// @param r8
void SRL_r8(System* system, uint8_t r8);

/// @brief Shift Right Logically the byte pointed to by HL.
/// @param system System struct
void SRL_HL(System* system);

/* Load instructions */

/// @brief Load (copy) value in r8_2 into r8_1.
/// @param system 
/// @param r8_1 
/// @param r8_2 
void LD_r8_r8(System* system, uint8_t r8_1, uint8_t r8_2);

/// @brief Load value n8 into register r8.
/// @param system 
/// @param r8 
/// @param n8 
void LD_r8_n8(System* system, uint8_t r8, uint8_t n8);

/// @brief Load value n16 into register r16.
/// @param system 
/// @param r16 
/// @param n16 
void LD_r16_n16(System* system, uint8_t r16, uint16_t n16);

/// @brief Store value in register r8 into the byte pointed to by register HL.
/// @param system 
/// @param r8 
void LD_HL_r8(System* system, uint8_t r8);

/// @brief Store value n8 into the byte pointed to by register HL.
/// @param system 
/// @param n8 
void LD_HL_n8(System* system, uint8_t n8);

/// @brief Load value into register r8 from the byte pointed to by register HL.
/// @param system 
/// @param r8 
void LD_r8_HL(System* system, uint8_t r8);

/// @brief Store value in register A into the byte pointed to by register r16.
/// @param system 
/// @param r16 
void LD_r16_A(System* system, uint8_t r16);

/// @brief Store value in register A into the byte at address n16.
/// @param system 
/// @param n16 
void LD_n16_A(System* system, uint16_t n16);

/// @brief Store value in register A into the byte at address $FF00+n8
/// @param system 
/// @param n8 
void LDH_n8_A(System* system, uint8_t n8);

/// @brief Store value in register A into the byte at address $FF00+C.
/// @param system 
void LDH_C_A(System* system);

/// @brief Load value in register A from the byte pointed to by register r16.
/// @param system 
/// @param r16 
void LD_A_r16(System* system, uint8_t r16);

/// @brief Load value in register A from the byte at address n16.
/// @param system 
/// @param n16 
void LD_A_n16(System* system, uint16_t n16);

/// @brief Load value in register A from the byte at address $FF00+n8.
/// @param system 
/// @param n8 
void LDH_A_n8(System* system, uint8_t n8);

/// @brief Load value in register A from the byte at address $FF00+c.
/// @param system 
void LDH_A_C(System* system);

/// @brief Store value in register A into the byte pointed by HL and increment HL afterwards.
/// @param system 
void LD_HLI_A(System* system);

/// @brief Store value in register A into the byte pointed by HL and decrement HL afterwards.
/// @param system 
void LD_HLD_A(System* system);

/// @brief Load value into register A from the byte pointed by HL and increment HL afterwards.
/// @param system 
void LD_A_HLI(System* system);

/// @brief Load value into register A from the byte pointed by HL and decrement HL afterwards.
/// @param system 
void LD_A_HLD(System* system);

/* Jumps and Subroutines */

/// @brief Call address n16.
/// @param system 
/// @param n16 
void CALL_n16(System* system, uint16_t n16);

/// @brief Call address n16 if condition cc is met.
/// @param system 
/// @param condition 
/// @param n16 
void CALL_cc_n16(System* system, uint8_t condition, uint16_t n16);

/// @brief Jump to address in HL.
/// @param system 
void JP_HL(System* system);

/// @brief Jump to address n16.
/// @param system 
/// @param n16 
void JP_n16(System* system, uint16_t n16);

/// @brief Jump to address n16 if condition cc is met.
/// @param system 
/// @param condition 
/// @param n16 
void JP_cc_n16(System* system, uint8_t condition, uint16_t n16);

/// @brief Relative Jump to address n16.
/// @param system 
/// @param e8 
void JR_n16(System* system, char e8);

/// @brief Relative Jump to address n16 if condition cc is met.
/// @param system 
/// @param condition 
/// @param e8 
void JR_cc_n16(System* system, uint8_t condition, char e8);

/// @brief Return from subroutine.
/// @param system 
void RET(System* system);

/// @brief Return from subroutine if condition cc is met.
/// @param system 
/// @param condition
void RET_cc(System* system, uint8_t condition);

/// @brief Return from subroutine and enable interrupts.
/// @param system 
void RETI(System* system);

/// @brief Call address vec.
/// @param system 
void RST_vec(System* system);

/* Stack operations instructions */

/// @brief Add the value in SP to HL.
/// @param system System struct
void ADD_HL_SP(System* system);

/// @brief Add the signed value e8 to SP.
/// @param system System struct
/// @param e8 Signed value
void ADD_SP_e8(System* system, char e8);

/// @brief Decrement value in register SP by 1.
/// @param system 
void DEC_SP(System* system);

/// @brief Increment value in register SP by 1.
/// @param system 
void INC_SP(System* system);

/// @brief Load value n16 into register SP.
/// @param system 
/// @param n16 
void LD_SP_n16(System* system, uint16_t n16);

/// @brief Store SP & $FF at address n16 and SP >> 8 at address n16 + 1.
/// @param system 
/// @param n16 
void LD_n16_SP(System* system, uint16_t n16);

/// @brief Add the signed value e8 to SP and store the result in HL.
/// @param system 
/// @param e8 
void LD_HL_SP_e8(System* system, char e8);

/// @brief Load register HL into register SP.
/// @param system 
void LD_SP_HL(System* system);

/// @brief Pop register r16 from the stack.
/// @param system 
/// @param r16 
void POP_r16(System* system, uint8_t r16);

/// @brief Push register r16 into the stack.
/// @param system 
/// @param r16 
void PUSH_r16(System* system, uint8_t r16);
