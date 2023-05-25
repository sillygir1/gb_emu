#include <stdint.h>
#include <stdbool.h>

#include "registers.h"
#include "system.h"
#include "instructions.h"

bool test_all(System* system, bool print_all);

bool test_ADC_A_r8(System* system, bool print_all);

bool test_ADC_A_HL(System* system, bool print_all);

bool test_ADC_A_n8(System* system, bool print_all);

bool test_ADD_A_r8(System* system, bool print_all);

bool test_ADD_A_HL(System* system, bool print_all);

bool test_ADD_A_n8(System* system, bool print_all);

bool test_AND_A_r8(System* system, bool print_all);

bool test_AND_A_HL(System* system, bool print_all);

bool test_AND_A_n8(System* system, bool print_all);

bool test_CP_A_r8(System* system, bool print_all);

bool test_CP_A_HL(System* system, bool print_all);

bool test_CP_A_n8(System* system, bool print_all);

bool test_DEC_r8(System* system, bool print_all);

bool test_DEC_HL(System* system, bool print_all);

bool test_INC_r8(System* system, bool print_all);

bool test_INC_HL(System* system, bool print_all);

bool test_OR_A_r8(System* system, bool print_all);

bool test_OR_A_HL(System* system, bool print_all);

bool test_OR_A_n8(System* system, bool print_all);

bool test_SBC_A_r8(System* system, bool print_all);

bool test_SBC_A_HL(System* system, bool print_all);

bool test_SBC_A_n8(System* system, bool print_all);

bool test_SUB_A_r8(System* system, bool print_all);

bool test_SUB_A_HL(System* system, bool print_all);

bool test_SUB_A_n8(System* system, bool print_all);

bool test_XOR_A_r8(System* system, bool print_all);

bool test_XOR_A_HL(System* system, bool print_all);

bool test_XOR_A_n8(System* system, bool print_all);
