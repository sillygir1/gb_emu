#include <stdint.h>
#include <stdbool.h>

#include "registers.h"
#include "system.h"
#include "instructions.h"

void test_all(System *system);

void test_ADC_A_r8(System* system);

void test_ADC_A_HL(System* system);

void test_ADC_A_n8(System* system);

void test_ADD_A_r8(System* system);

void test_ADD_A_HL(System* system);

void test_ADD_A_n8(System* system);

void test_AND_A_r8(System* system);

void test_AND_A_HL(System* system);

void test_AND_A_n8(System* system);

void test_CP_A_r8(System* system);

void test_CP_A_HL(System* system);

void test_CP_A_n8(System* system);

void test_DEC_r8(System *system);

void test_DEC_HL(System *system);
