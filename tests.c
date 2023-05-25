#include "tests.h"

#define add_value 0b1100

void test_all(System* system) {
    test_ADC_A_r8(system);
    test_ADC_A_HL(system);
    test_ADC_A_n8(system);
    test_ADD_A_r8(system);
    test_ADD_A_HL(system);
    test_ADD_A_n8(system);
    test_AND_A_r8(system);
    test_AND_A_HL(system);
    test_AND_A_n8(system);
    test_CP_A_r8(system);
    test_CP_A_HL(system);
    test_CP_A_n8(system);
    test_DEC_r8(system);
    test_DEC_HL(system);

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
        if (res > 0xFFU) { carry = true; } else { carry = false; }
        if ((i & 0xF + add_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
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
        SET_FLAG(HALFCARRY, false);
        SET_FLAG(CARRY, true);
        ADC_A_r8(system, B, C);
        uint16_t res = (uint8_t)add_value + i + 1;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if ((i & 0xF + add_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("ADC A,r8: %hhu (carry) passed\n", i);
        } else {
            printf("ADC A,r8: %hhu (carry) failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
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
        // Calcuating flags
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if ((i & 0xF + add_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }

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
        if ((i & 0xF + add_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
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
    bool halfcarry = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        ADC_A_n8(system, B, add_value);
        uint16_t res = (uint8_t)add_value + i;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if ((i & 0xF + add_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("ADC A,n8: %hhu (no carry) passed\n", i);
        } else {
            printf("ADC A,n8: %hhu (no carry) failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
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
        if ((i & 0xF + add_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("ADC A,n8: %hhu (carry) passed\n", i);
        } else {
            printf("ADC A,n8: %hhu (carry) failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
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
        if ((i & 0xF + add_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("ADD A,r8: %hhu passed\n", i);
        } else {
            printf("ADD A,r8: %hhu failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
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
        if ((i & 0xF + add_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("ADD A,[HL]: %hhu passed\n", i);
        } else {
            printf("ADD A,[HL]: %hhu failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
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
        uint16_t res = (uint8_t)add_value + i;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if ((i & 0xF + add_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("ADD A,n8: %hhu passed\n", i);
        } else {
            printf("ADD A,[HL]: %hhu failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    if (!failed) printf("Success!\n");
}

void test_AND_A_r8(System* system) {
    printf("AND A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->registers[C] = add_value;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        AND_A_r8(system, B, C);
        uint16_t res = (uint8_t)add_value & i;
        carry = false;
        halfcarry = true;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("AND A,r8: %hhu passed\n", i);
        } else {
            printf("AND A,r8: %hhu failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    if (!failed) printf("Success!\n");
}

void test_AND_A_HL(System* system) {
    printf("AND A,[HL] test:\n");
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
        AND_A_HL(system, B);
        uint16_t res = (uint8_t)add_value & i;
        carry = false;
        halfcarry = true;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("AND A,[HL]: %hhu passed\n", i);
        } else {
            printf("AND A,[HL]: %hhu failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    if (!failed) printf("Success!\n");
}

void test_AND_A_n8(System* system) {
    printf("AND A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        AND_A_n8(system, B, add_value);
        uint16_t res = (uint8_t)add_value & i;
        carry = false;
        halfcarry = true;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("AND A,n8: %hhu passed\n", i);
        } else {
            printf("AND A,[HL]: %hhu failed\nExpected: %hhu c:%u hc: %u, got: %u c:%u hc: %u\n", i, res, carry, halfcarry, system->registers[B], GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    if (!failed) printf("Success!\n");
}

void test_CP_A_r8(System* system) {
    printf("CP A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->registers[C] = add_value;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        CP_A_r8(system, B, C);
        uint16_t res = (uint8_t)add_value - i;
        if (i < add_value) { carry = true; } else { carry = false; }
        if (i & 0xF < add_value & 0xF) { halfcarry = true; } else { halfcarry = false; }

        if (GET_FLAG(ZERO) == (res == 0) && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("CP A,r8: %hhu passed\n", i);
        } else {
            printf("CP A,r8: %hhu failed\nExpected: z: %u c:%u hc: %u, got: z: %u c: %u hc: %u\n", i, zero, carry, halfcarry, GET_FLAG(ZERO), GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    if (!failed) printf("Success!\n");
}

void test_CP_A_HL(System* system) {
    printf("CP A,HL test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->memory[0xFF] = add_value;
        system->registers[H] = 0x00;
        system->registers[L] = 0xFF;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        CP_A_HL(system, B);
        uint16_t res = (uint8_t)add_value - i;
        if (i < add_value) { carry = true; } else { carry = false; }
        if (i & 0xF < add_value & 0xF) { halfcarry = true; } else { halfcarry = false; }

        if (GET_FLAG(ZERO) == (res == 0) && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("CP A,HL: %hhu passed\n", i);
        } else {
            printf("CP A,HL: %hhu failed\nExpected: z: %u c:%u hc: %u, got: z: %u c: %u hc: %u\n", i, zero, carry, halfcarry, GET_FLAG(ZERO), GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    if (!failed) printf("Success!\n");
}

void test_CP_A_n8(System* system) {
    printf("CP A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        CP_A_n8(system, B, add_value);
        uint16_t res = (uint8_t)add_value - i;
        if (i < add_value) { carry = true; } else { carry = false; }
        if (i & 0xF < add_value & 0xF) { halfcarry = true; } else { halfcarry = false; }

        if (GET_FLAG(ZERO) == (res == 0) && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("CP A,n8: %hhu passed\n", i);
        } else {
            printf("CP A,n8: %hhu failed\nExpected: z: %u c:%u hc: %u, got: z: %u c: %u hc: %u\n", i, zero, carry, halfcarry, GET_FLAG(ZERO), GET_FLAG(CARRY), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    if (!failed) printf("Success!\n");
}

void test_DEC_r8(System* system) {
    printf("DEC r8 test:\n");
    bool failed = false;
    bool sub = false;
    bool zero = false;
    bool halfcarry = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(SUB, false);
        SET_FLAG(HALFCARRY, false);
        SET_FLAG(ZERO, false);
        DEC_r8(system, B);
        zero = i - 1 == 0;
        halfcarry = ((i - 1) & 0xF == 0b1111);
        sub = true;
        if (zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("DEC r8: %hhu passed\n", i);
        } else {
            printf("DEC r8: %hhu failed\nExpected: %u z: %u n:%u hc: %u, got: %u z: %u n: %u hc: %u\n", i, i - 1, zero, sub, halfcarry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    if (!failed) printf("Success!\n");
}

void test_DEC_HL(System* system) {
    printf("DEC r8 test:\n");
    bool failed = false;
    bool sub = false;
    bool zero = false;
    bool halfcarry = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->memory[0xFF] = i;
        system->registers[H] = 0x00;
        system->registers[L] = 0xFF;
        SET_FLAG(SUB, false);
        SET_FLAG(HALFCARRY, false);
        SET_FLAG(ZERO, false);
        DEC_HL(system);
        zero = i - 1 == 0;
        halfcarry = ((i - 1) & 0xF == 0b1111);
        sub = true;
        if (zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB) && halfcarry == GET_FLAG(HALFCARRY)) {
            //printf("DEC HL: %hhu passed\n", i);
        } else {
            printf("DEC HL: %hhu failed\nExpected: %u z: %u n:%u hc: %u, got: %u z: %u n: %u hc: %u\n", i, i - 1, zero, sub, halfcarry, system->memory[0xFF], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY));
            failed = true;
        }
    }
    if (!failed) printf("Success!\n");
}
