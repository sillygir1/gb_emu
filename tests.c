#include "tests.h"

#define add_value 0b11111

void test_all(System* system) {
    test_ADC_A_r8(system);
    test_ADC_A_HL(system);
    test_ADC_A_n8(system);
    test_ADD_A_r8(system);
    test_ADD_A_HL(system);
    test_ADD_A_n8(system);

}

void test_ADC_A_r8(System* system) {
    printf("ADC A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->registers[C] = add_value;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        ADC_A_r8(system, B, C);
        uint16_t res = (uint8_t)add_value + i;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if (res > 0xFU) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("ADC A,r8: %hhu (no carry) passed\n", i);
        } else {
            printf("ADC A,r8: %hhu (no carry) failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->registers[C] = add_value;
        SET_FLAG(CARRY, true);
        SET_FLAG(HALFCARRY, false);
        ADC_A_r8(system, B, C);
        uint16_t res = (uint8_t)add_value + i + 1;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if (res > 0xFU) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("ADC A,r8: %hhu (carry) passed\n", i);
        } else {
            printf("ADC A,r8: %hhu (no carry) failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    if (!failed) printf("Success!\n");
}

void test_ADC_A_HL(System* system) {
    printf("ADC A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->memory[0xFF] = add_value;
        system->registers[H] = 0x00;
        system->registers[L] = 0xFF;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        ADC_A_HL(system, B);
        uint16_t res = (uint8_t)add_value + i;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if (res > 0xFU) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("ADC A,[HL]: %hhu (no carry) passed\n", i);
        } else {
            printf("ADC A,[HL]: %hhu (no carry) failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->memory[0xFF] = add_value;
        system->registers[H] = 0x00;
        system->registers[L] = 0xFF;
        SET_FLAG(CARRY, true);
        SET_FLAG(HALFCARRY, false);
        ADC_A_HL(system, B);
        uint16_t res = (uint8_t)add_value + i + 1;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if (res > 0xFU) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("ADC A,[HL]: %hhu (carry) passed\n", i);
        } else {
            printf("ADC A,[HL]: %hhu (carry) failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    if (!failed) printf("Success!\n");
}

void test_ADC_A_n8(System* system) {
    printf("ADC A,n8 test:\n");
    bool failed = false;
    bool carry = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        ADC_A_n8(system, B, add_value);
        uint16_t res = (uint8_t)add_value + i;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY)) {
            //printf("ADC A,n8: %hhu (no carry) passed\n", i);
        } else {
            printf("ADC A,n8: %hhu (no carry) failed\nExpected: %hhu c:%d, got: %u c:%d\n", i, res, carry, system->registers[B], GET_FLAG(CARRY));
            failed = true;
        }
    }
    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(CARRY, true);
        SET_FLAG(HALFCARRY, false);
        ADC_A_n8(system, B, add_value);
        uint16_t res = (uint8_t)add_value + i + 1;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY)) {
            //printf("ADC A,n8: %hhu (carry) passed\n", i);
        } else {
            printf("ADC A,n8: %hhu (carry) failed\nExpected: %hhu c:%d, got: %u c:%d\n", i, res, carry, system->registers[B], GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) printf("Success!\n");
}

void test_ADD_A_r8(System* system) {
    printf("ADD A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->registers[C] = add_value;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        ADD_A_r8(system, B, C);
        uint16_t res = (uint8_t)add_value + i;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if (res > 0xFU) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("ADD A,r8: %hhu (no carry) passed\n", i);
        } else {
            printf("ADD A,r8: %hhu (no carry) failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    if (!failed) printf("Success!\n");
}

void test_ADD_A_HL(System* system) {
    printf("ADD A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->memory[0xFFF] = add_value;
        system->registers[H] = 0x0F;
        system->registers[L] = 0xFF;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        ADD_A_HL(system, B);
        uint16_t res = (uint8_t)add_value + i;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if (res > 0xFU) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("ADD A,[HL]: %hhu (no carry) passed\n", i);
        } else {
            printf("ADD A,[HL]: %hhu (no carry) failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    if (!failed) printf("Success!\n");
}

void test_ADD_A_n8(System* system) {
    printf("ADD A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        ADD_A_n8(system, B, add_value);
        SET_FLAG(HALFCARRY, false);
        uint16_t res = (uint8_t)add_value + i;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if (res > 0xFU) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("ADD A,n8: %hhu (no carry) passed\n", i);
        } else {
            printf("ADD A,[HL]: %hhu (no carry) failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    if (!failed) printf("Success!\n");
}