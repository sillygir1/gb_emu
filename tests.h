#include <stdint.h>
#include <stdbool.h>

#include "registers.h"
#include "system.h"
#include "instructions.h"

/* Batch tests */

bool test_all(System* system, bool print_all);

bool test_8bit(System* system, bool print_all);

bool test_16bit(System* system, bool print_all);

bool test_stack(System* system, bool print_all);

bool test_bit(System* system, bool print_all);

/* 8-bit arithmetic and logic instructions */

bool test_ADC_A_r8(System* system, uint8_t test_value, bool print_all);

bool test_ADC_A_HL(System* system, uint8_t test_value, bool print_all);

bool test_ADC_A_n8(System* system, uint8_t test_value, bool print_all);

bool test_ADD_A_r8(System* system, uint8_t test_value, bool print_all);

bool test_ADD_A_HL(System* system, uint8_t test_value, bool print_all);

bool test_ADD_A_n8(System* system, uint8_t test_value, bool print_all);

bool test_AND_A_r8(System* system, uint8_t test_value, bool print_all);

bool test_AND_A_HL(System* system, uint8_t test_value, bool print_all);

bool test_AND_A_n8(System* system, uint8_t test_value, bool print_all);

bool test_CP_A_r8(System* system, uint8_t test_value, bool print_all);

bool test_CP_A_HL(System* system, uint8_t test_value, bool print_all);

bool test_CP_A_n8(System* system, uint8_t test_value, bool print_all);

bool test_DEC_r8(System* system, bool print_all);

bool test_DEC_HL(System* system, bool print_all);

bool test_INC_r8(System* system, bool print_all);

bool test_INC_HL(System* system, bool print_all);

bool test_OR_A_r8(System* system, uint8_t test_value, bool print_all);

bool test_OR_A_HL(System* system, uint8_t test_value, bool print_all);

bool test_OR_A_n8(System* system, uint8_t test_value, bool print_all);

bool test_SBC_A_r8(System* system, uint8_t test_value, bool print_all);

bool test_SBC_A_HL(System* system, uint8_t test_value, bool print_all);

bool test_SBC_A_n8(System* system, uint8_t test_value, bool print_all);

bool test_SUB_A_r8(System* system, uint8_t test_value, bool print_all);

bool test_SUB_A_HL(System* system, uint8_t test_value, bool print_all);

bool test_SUB_A_n8(System* system, uint8_t test_value, bool print_all);

bool test_XOR_A_r8(System* system, uint8_t test_value, bool print_all);

bool test_XOR_A_HL(System* system, uint8_t test_value, bool print_all);

bool test_XOR_A_n8(System* system, uint8_t test_value, bool print_all);

/* 16-bit arithmetic instructions */

bool test_ADD_HL_r16(System* system, uint16_t test_value, bool print_all);

bool test_DEC_r16(System* system, bool print_all);

bool test_INC_r16(System* system, bool print_all);

/* Bit operations instructions */

bool test_BIT_u3_r8(System* system, uint8_t test_value, bool print_all);

bool test_BIT_u3_HL(System* system, uint8_t test_value, bool print_all);

bool test_RES_u3_r8(System* system, uint8_t test_value, bool print_all);

bool test_RES_u3_HL(System* system, uint8_t test_value, bool print_all);

bool test_SET_u3_r8(System* system, uint8_t test_value, bool print_all);

bool test_SET_u3_HL(System* system, uint8_t test_value, bool print_all);

bool test_SWAP_r8(System* system, uint8_t test_value, bool print_all);

bool test_SWAP_HL(System* system, uint8_t test_value, bool print_all);

/* Stack operations instructions */

bool test_ADD_HL_SP(System* system, uint16_t test_value, bool print_all);

bool test_ADD_SP_e8(System* system, uint16_t test_value, bool print_all);
