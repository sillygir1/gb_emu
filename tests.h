#include <stdbool.h>
#include <stdint.h>

#include "instructions.h"
#include "registers.h"
#include "system.h"

/* Batch tests */

bool test_all(System *system, bool print_all);

bool test_8bit(System *system, bool print_all);

bool test_16bit(System *system, bool print_all);

bool test_stack(System *system, bool print_all);

bool test_bit(System *system, bool print_all);

bool test_bitshift(System *system, bool print_all);

bool test_jumps_subtoutines(System *system, bool print_all);

bool test_load(System *system, bool print_all);

bool test_misc(System *system, bool print_all);

/* 8-bit arithmetic and logic instructions */

bool test_ADC_A_r8(System *system, uint8_t test_value, bool print_all);

bool test_ADC_A_HL(System *system, uint8_t test_value, bool print_all);

bool test_ADC_A_n8(System *system, uint8_t test_value, bool print_all);

bool test_ADD_A_r8(System *system, uint8_t test_value, bool print_all);

bool test_ADD_A_HL(System *system, uint8_t test_value, bool print_all);

bool test_ADD_A_n8(System *system, uint8_t test_value, bool print_all);

bool test_AND_A_r8(System *system, uint8_t test_value, bool print_all);

bool test_AND_A_HL(System *system, uint8_t test_value, bool print_all);

bool test_AND_A_n8(System *system, uint8_t test_value, bool print_all);

bool test_CP_A_r8(System *system, uint8_t test_value, bool print_all);

bool test_CP_A_HL(System *system, uint8_t test_value, bool print_all);

bool test_CP_A_n8(System *system, uint8_t test_value, bool print_all);

bool test_DEC_r8(System *system, bool print_all);

bool test_DEC_HL(System *system, bool print_all);

bool test_INC_r8(System *system, bool print_all);

bool test_INC_HL(System *system, bool print_all);

bool test_OR_A_r8(System *system, uint8_t test_value, bool print_all);

bool test_OR_A_HL(System *system, uint8_t test_value, bool print_all);

bool test_OR_A_n8(System *system, uint8_t test_value, bool print_all);

bool test_SBC_A_r8(System *system, uint8_t test_value, bool print_all);

bool test_SBC_A_HL(System *system, uint8_t test_value, bool print_all);

bool test_SBC_A_n8(System *system, uint8_t test_value, bool print_all);

bool test_SUB_A_r8(System *system, uint8_t test_value, bool print_all);

bool test_SUB_A_HL(System *system, uint8_t test_value, bool print_all);

bool test_SUB_A_n8(System *system, uint8_t test_value, bool print_all);

bool test_XOR_A_r8(System *system, uint8_t test_value, bool print_all);

bool test_XOR_A_HL(System *system, uint8_t test_value, bool print_all);

bool test_XOR_A_n8(System *system, uint8_t test_value, bool print_all);

/* 16-bit arithmetic instructions */

bool test_ADD_HL_r16(System *system, uint16_t test_value, bool print_all);

bool test_DEC_r16(System *system, bool print_all);

bool test_INC_r16(System *system, bool print_all);

/* Bit operations instructions */

bool test_BIT_u3_r8(System *system, uint8_t test_value, bool print_all);

bool test_BIT_u3_HL(System *system, uint8_t test_value, bool print_all);

bool test_RES_u3_r8(System *system, uint8_t test_value, bool print_all);

bool test_RES_u3_HL(System *system, uint8_t test_value, bool print_all);

bool test_SET_u3_r8(System *system, uint8_t test_value, bool print_all);

bool test_SET_u3_HL(System *system, uint8_t test_value, bool print_all);

bool test_SWAP_r8(System *system, uint8_t test_value, bool print_all);

bool test_SWAP_HL(System *system, uint8_t test_value, bool print_all);

/* Bit shift instructions */

bool test_RL_r8(System *system, uint8_t test_value, bool print_all);

bool test_RL_HL(System *system, uint8_t test_value, bool print_all);

bool test_RLA(System *system, uint8_t test_value, bool print_all);

bool test_RLC_r8(System *system, uint8_t test_value, bool print_all);

bool test_RLC_HL(System *system, uint8_t test_value, bool print_all);

bool test_RLCA(System *system, uint8_t test_value, bool print_all);

bool test_RR_r8(System *system, uint8_t test_value, bool print_all);

bool test_RR_HL(System *system, uint8_t test_value, bool print_all);

bool test_RRA(System *system, uint8_t test_value, bool print_all);

bool test_RRC_r8(System *system, uint8_t test_value, bool print_all);

bool test_RRC_HL(System *system, uint8_t test_value, bool print_all);

bool test_RRCA(System *system, uint8_t test_value, bool print_all);

bool test_SLA_r8(System *system, uint8_t test_value, bool print_all);

bool test_SLA_HL(System *system, uint8_t test_value, bool print_all);

bool test_SRA_r8(System *system, uint8_t test_value, bool print_all);

bool test_SRA_HL(System *system, uint8_t test_value, bool print_all);

bool test_SRL_r8(System *system, uint8_t test_value, bool print_all);

bool test_SRL_HL(System *system, uint8_t test_value, bool print_all);

/* Load instructions */

bool test_LD_r8_r8(System *system, uint8_t test_value, bool print_all);

bool test_LD_r8_n8(System *system, uint8_t test_value, bool print_all);

bool test_LD_r16_n16(System *system, uint16_t test_value, bool print_all);

bool test_LD_HL_r8(System *system, uint8_t test_value, bool print_all);

bool test_LD_HL_n8(System *system, uint8_t test_value, bool print_all);

bool test_LD_r8_HL(System *system, uint8_t test_value, bool print_all);

bool test_LD_r16_A(System *system, uint8_t test_value, bool print_all);

bool test_LD_n16_A(System *system, uint8_t test_value, bool print_all);

bool test_LDH_n8_A(System *system, uint8_t test_value, bool print_all);

bool test_LDH_C_A(System *system, uint8_t test_value, bool print_all);

bool test_LD_A_r16(System *system, uint8_t test_value, bool print_all);

bool test_LD_A_n16(System *system, uint8_t test_value, bool print_all);

bool test_LDH_A_n8(System *system, uint8_t test_value, bool print_all);

bool test_LDH_A_C(System *system, uint8_t test_value, bool print_all);

bool test_LD_HLI_A(System *system, uint8_t test_value, bool print_all);

bool test_LD_HLD_A(System *system, uint8_t test_value, bool print_all);

bool test_LD_A_HLI(System *system, uint8_t test_value, bool print_all);

bool test_LD_A_HLD(System *system, uint8_t test_value, bool print_all);

/* Jumps and Subroutines */

bool test_JP_HL(System *system, uint16_t test_value, bool print_all);

bool test_JP_n16(System *system, uint16_t test_value, bool print_all);

bool test_JP_cc_n16(System *system, uint16_t test_value, bool print_all);

bool test_JR_n16(System *system, uint16_t test_value, bool print_all);

bool test_JR_cc_n16(System *system, uint16_t test_value, bool print_all);

bool test_RET(System *system, uint16_t test_value, bool print_all);

bool test_RET_cc(System *system, uint16_t test_value, bool print_all);

/* Stack operations instructions */

bool test_ADD_HL_SP(System *system, uint16_t test_value, bool print_all);

bool test_ADD_SP_e8(System *system, uint16_t test_value, bool print_all);

bool test_DEC_SP(System *system, uint16_t test_value, bool print_all);

bool test_INC_SP(System *system, uint16_t test_value, bool print_all);

bool test_LD_SP_n16(System *system, uint16_t test_value, bool print_all);

bool test_LD_n16_SP(System *system, uint16_t test_value, bool print_all);

bool test_LD_HL_SP_e8(System *system, uint16_t test_value, bool print_all);

bool test_LD_SP_HL(System *system, uint16_t test_value, bool print_all);

bool test_POP_r16(System *system, uint16_t test_value, bool print_all);

bool test_PUSH_r16(System *system, uint16_t test_value, bool print_all);

/* Miscellaneous Instructions */

bool test_CCF(System *system, bool print_all);

bool test_CPL(System *system, uint8_t test_value, bool print_all);
