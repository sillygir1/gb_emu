#include "tests.h"

static uint8_t test_value = 0b1100;

bool test_all(System* system, bool print_all) {
    uint16_t sum = 0;
    for (uint32_t i = 0; i < 256; i++) {
        test_value = i;
        if (print_all) printf("test_value: %hhu\n", test_value);
        sum += test_ADC_A_r8(system, print_all);
        sum += test_ADC_A_HL(system, print_all);
        sum += test_ADC_A_n8(system, print_all);
        sum += test_ADD_A_r8(system, print_all);
        sum += test_ADD_A_HL(system, print_all);
        sum += test_ADD_A_n8(system, print_all);
        sum += test_AND_A_r8(system, print_all);
        sum += test_AND_A_HL(system, print_all);
        sum += test_AND_A_n8(system, print_all);
        sum += test_CP_A_r8(system, print_all);
        sum += test_CP_A_HL(system, print_all);
        sum += test_CP_A_n8(system, print_all);
        sum += test_DEC_r8(system, print_all);
        sum += test_DEC_HL(system, print_all);
        sum += test_INC_r8(system, print_all);
        sum += test_INC_HL(system, print_all);
        sum += test_OR_A_r8(system, print_all);
        sum += test_OR_A_HL(system, print_all);
        sum += test_OR_A_n8(system, print_all);
        sum += test_SBC_A_r8(system, print_all);
        sum += test_SBC_A_HL(system, print_all);
        sum += test_SBC_A_n8(system, print_all);
        sum += test_SUB_A_r8(system, print_all);
        sum += test_SUB_A_HL(system, print_all);
        sum += test_SUB_A_n8(system, print_all);
        sum += test_XOR_A_r8(system, print_all);
        sum += test_XOR_A_HL(system, print_all);
        sum += test_XOR_A_n8(system, print_all);
    }
    if (sum) { printf("\nTotal of %hu failed runs.\n", sum); } else { printf("\nNo failures!\n"); }
}

bool test_ADC_A_r8(System* system, bool print_all) {
    if (print_all) printf("ADC A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->registers[C] = test_value;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        ADC_A_r8(system, B, C);
        uint16_t res = (uint8_t)test_value + i;
        zero = !res;
        sub = 0;
        if (res > 0xFFU) { carry = true; } else { carry = false; }
        if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("ADC A,r8: %hhu %hhu (no carry) passed\n", i);
        } else {
            printf("ADC A,r8: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->registers[C] = test_value;
        SET_FLAG(HALFCARRY, false);
        SET_FLAG(CARRY, true);
        ADC_A_r8(system, B, C);
        uint16_t res = (uint8_t)test_value + i + 1;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        zero = !res;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("ADC A,r8: %hhu %hhu (no carry) passed\n", i);
        } else {
            printf("ADC A,r8: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_ADC_A_HL(System* system, bool print_all) {
    if (print_all) printf("ADC A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->memory[0xFF] = test_value;
        system->registers[H] = 0x00;
        system->registers[L] = 0xFF;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        ADC_A_HL(system, B);
        uint16_t res = (uint8_t)test_value + i;
        zero = !res;
        sub = 0;
        // Calcuating flags
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }

        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("ADC A,[HL]: %hhu %hhu (no carry) passed\n", i);
        } else {
            printf("ADC A,[HL]: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->memory[0xFF] = test_value;
        system->registers[H] = 0x00;
        system->registers[L] = 0xFF;
        SET_FLAG(CARRY, true);
        SET_FLAG(HALFCARRY, false);
        ADC_A_HL(system, B);
        uint16_t res = (uint8_t)test_value + i + 1;
        zero = !res;
        sub = 0;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("ADC A,[HL]: %hhu %hhu (carry) passed\n", i);
        } else {
            printf("ADC A,[HL]: %hhu %hhu (carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_ADC_A_n8(System* system, bool print_all) {
    if (print_all) printf("ADC A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        ADC_A_n8(system, B, test_value);
        uint16_t res = (uint8_t)test_value + i;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        zero = !res;
        sub = 0;
        if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("ADC A,n8: %hhu %hhu (no carry) passed\n", i);
        } else {
            printf("ADC A,n8: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(CARRY, true);
        SET_FLAG(HALFCARRY, false);
        ADC_A_n8(system, B, test_value);
        uint16_t res = (uint8_t)test_value + i + 1;
        zero = !res;
        sub = 0;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("ADC A,n8: %hhu %hhu (carry) passed\n", i);
        } else {
            printf("ADC A,n8: %hhu %hhu (carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_ADD_A_r8(System* system, bool print_all) {
    if (print_all) printf("ADD A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->registers[C] = test_value;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        ADD_A_r8(system, B, C);
        uint16_t res = (uint8_t)test_value + i;
        zero = !res;
        sub = 0;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("ADD A,r8: %hhu %hhu passed\n", i);
        } else {
            printf("ADD A,r8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_ADD_A_HL(System* system, bool print_all) {
    if (print_all) printf("ADD A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->memory[0xFFF] = test_value;
        system->registers[H] = 0x0F;
        system->registers[L] = 0xFF;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        ADD_A_HL(system, B);
        uint16_t res = (uint8_t)test_value + i;
        zero = !res;
        sub = 0;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("ADD A,[HL]: %hhu %hhu passed\n", i);
        } else {
            printf("ADD A,[HL]: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_ADD_A_n8(System* system, bool print_all) {
    if (print_all) printf("ADD A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        ADD_A_n8(system, B, test_value);
        uint16_t res = (uint8_t)test_value + i;
        zero = !res;
        sub = 0;
        if (res > 0xFF) { carry = true; } else { carry = false; }
        if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("ADD A,n8: %hhu %hhu passed\n", i);
        } else {
            printf("ADD A,n8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_AND_A_r8(System* system, bool print_all) {
    if (print_all) printf("AND A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->registers[C] = test_value;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        AND_A_r8(system, B, C);
        uint16_t res = (uint8_t)test_value & i;
        zero = !res;
        sub = 0;
        carry = false;
        halfcarry = true;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("AND A,r8: %hhu %hhu (no carry) passed\n", i);
        } else {
            printf("AND A,r8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_AND_A_HL(System* system, bool print_all) {
    if (print_all) printf("AND A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->memory[0xFF] = test_value;
        system->registers[H] = 0x00;
        system->registers[L] = 0xFF;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        AND_A_HL(system, B);
        uint16_t res = (uint8_t)test_value & i;
        zero = !res;
        sub = 0;
        carry = false;
        halfcarry = true;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("ADC A,[HL]: %hhu %hhu passed\n", i);
        } else {
            printf("AND A,[HL]: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_AND_A_n8(System* system, bool print_all) {
    if (print_all) printf("AND A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        AND_A_n8(system, B, test_value);
        uint16_t res = (uint8_t)test_value & i;
        zero = !res;
        sub = 0;
        carry = false;
        halfcarry = true;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("ADC A,n8: %hhu %hhu passed\n", i);
        } else {
            printf("AND A,n8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_CP_A_r8(System* system, bool print_all) {
    if (print_all) printf("CP A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->registers[C] = test_value;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        CP_A_r8(system, B, C);
        uint16_t res = (uint8_t)i - test_value;
        zero = !res;
        sub = 1;
        if (i < test_value) { carry = true; } else { carry = false; }
        halfcarry = (i & 0xF) < (test_value & 0xF);
        if (carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("CP A,r8: %hhu %hhu passed\n", i);
        } else {
            printf("CP A,r8: %hhu %hhu failed\nExpected: z: %u n: %u hc: %u c: %u, got: z: %u n: %u hc: %u c: %u\n", i, test_value, zero, sub, halfcarry, carry, GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_CP_A_HL(System* system, bool print_all) {
    if (print_all) printf("CP A,HL test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->memory[0xFF] = test_value;
        system->registers[H] = 0x00;
        system->registers[L] = 0xFF;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        CP_A_HL(system, B);
        uint16_t res = (uint8_t)i - test_value;
        zero = !res;
        sub = 1;
        if (i < test_value) { carry = true; } else { carry = false; }
        halfcarry = (i & 0xF) < (test_value & 0xF);

        if (carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("CP A,[HL]: %hhu %hhu passed\n", i);
        } else {
            printf("CP A,[HL]: %hhu %hhu failed\nExpected: z: %u n: %u hc: %u c: %u, got: z: %u n: %u hc: %u c: %u\n", i, test_value, zero, sub, halfcarry, carry, GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_CP_A_n8(System* system, bool print_all) {
    if (print_all) printf("CP A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        CP_A_n8(system, B, test_value);
        uint16_t res = (uint8_t)i - test_value;
        zero = !res;
        sub = 1;
        if (i < test_value) { carry = true; } else { carry = false; }
        halfcarry = (i & 0xF) < (test_value & 0xF);

        if (carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("CP A,r8: %hhu %hhu passed\n", i);
        } else {
            printf("CP A,n8: %hhu %hhu failed\nExpected: z: %u n: %u hc: %u c: %u, got: z: %u n: %u hc: %u c: %u\n", i, test_value, zero, sub, halfcarry, carry, GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_DEC_r8(System* system, bool print_all) {
    if (print_all) printf("DEC r8 test:\n");
    bool failed = false;
    bool sub = false;
    bool zero = false;
    bool halfcarry = false;
    bool carry = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(SUB, false);
        SET_FLAG(HALFCARRY, false);
        SET_FLAG(ZERO, false);
        carry = GET_FLAG(CARRY);
        DEC_r8(system, B);
        uint8_t res = i - 1;
        zero = res == 0;
        halfcarry = ((res) & 0xF == 0b1111);
        sub = true;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("DEC r8: %hhu %hhu passed\n", i);
        } else {
            printf("DEC r8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_DEC_HL(System* system, bool print_all) {
    if (print_all) printf("DEC r8 test:\n");
    bool failed = false;
    bool sub = false;
    bool zero = false;
    bool halfcarry = false;
    bool carry = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->memory[0xFF] = i;
        system->registers[H] = 0x00;
        system->registers[L] = 0xFF;
        SET_FLAG(SUB, false);
        SET_FLAG(HALFCARRY, false);
        SET_FLAG(ZERO, false);
        carry = GET_FLAG(CARRY);
        DEC_HL(system);
        uint8_t res = i - 1;
        zero = res == 0;
        halfcarry = ((res) & 0xF == 0b1111);
        sub = true;
        if ((uint8_t)system->memory[0xFF] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("DEC [HL]: %hhu %hhu passed\n", i);
        } else {
            printf("DEC [HL]: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->memory[0xFF], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_INC_r8(System* system, bool print_all) {
    if (print_all) printf("INC r8 test:\n");
    bool failed = false;
    bool sub = false;
    bool zero = false;
    bool halfcarry = false;
    bool carry = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(SUB, false);
        SET_FLAG(HALFCARRY, false);
        SET_FLAG(ZERO, false);
        carry = GET_FLAG(CARRY);
        INC_r8(system, B);
        uint8_t res = i + 1;
        zero = res == 0;
        halfcarry = ((res - 1) & 0xF == 0b1111);
        sub = false;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("INC r8: %hhu %hhu passed\n", i);
        } else {
            printf("INC r8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_INC_HL(System* system, bool print_all) {
    if (print_all) printf("INC [HL] test:\n");
    bool failed = false;
    bool sub = false;
    bool zero = false;
    bool halfcarry = false;
    bool carry = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        /* Default values */
        system->memory[0xFF] = i;
        system->registers[H] = 0x00;
        system->registers[L] = 0xFF;
        system->registers[F] = 0x00;
        carry = GET_FLAG(CARRY);
        /* Function to test */
        INC_HL(system);
        uint8_t res = i + 1;
        /* Expected flags */
        zero = res == 0;
        halfcarry = ((res - 1) & 0xF == 0b1111);
        sub = false;
        /* Test */
        if ((uint8_t)system->memory[0xFF] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("INC [HL]: %hhu %hhu passed\n", i);
        } else {
            printf("INC [HL]: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->memory[0xFF], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_OR_A_r8(System* system, bool print_all) {
    if (print_all) printf("OR A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->registers[C] = test_value;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        bool carry = GET_FLAG(CARRY);
        OR_A_r8(system, B, C);
        uint8_t res = (uint8_t)i | test_value;
        carry = false;
        halfcarry = false;
        zero = res == 0 ? true : false;
        sub = false;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("OR A,r8: %hhu %hhu passed\n", i);
        } else {
            printf("OR A,r8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_OR_A_HL(System* system, bool print_all) {
    if (print_all) printf("OR A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->memory[0xFF] = test_value;
        system->registers[H] = 0x00;
        system->registers[L] = 0xFF;
        system->registers[F] = 0x00;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        OR_A_HL(system, B);
        uint8_t res = (uint8_t)i | test_value;
        carry = false;
        halfcarry = false;
        zero = res == 0 ? true : false;
        sub = false;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO)) {
            //printf("OR A,[HL]: %hhu %hhu passed\n", i);
        } else {
            printf("OR A,[HL]: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_OR_A_n8(System* system, bool print_all) {
    if (print_all) printf("OR A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        OR_A_n8(system, B, test_value);
        uint8_t res = (uint8_t)i | test_value;
        carry = false;
        halfcarry = false;
        zero = res == 0 ? true : false;
        sub = false;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("OR A,n8: %hhu %hhu passed\n", i);
        } else {
            printf("OR A,n8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SBC_A_r8(System* system, bool print_all) {
    if (print_all) printf("SBC A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->registers[C] = test_value;
        SET_FLAG(CARRY, 0);
        SET_FLAG(HALFCARRY, false);
        SBC_A_r8(system, B, C);
        uint8_t res = (uint8_t)i - test_value;
        zero = !res;
        sub = 1;
        if (i < test_value) { carry = true; } else { carry = false; }
        // if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        halfcarry = (i & 0xF) < (test_value & 0xF);
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("SBC A,r8: %hhu %hhu (no carry) passed\n", i);
        } else {
            printf("SBC A,r8: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->registers[C] = test_value;
        SET_FLAG(HALFCARRY, false);
        SET_FLAG(CARRY, true);
        SBC_A_r8(system, B, C);
        uint8_t res = (uint8_t)i - (uint8_t)test_value - 1;
        sub = 1;
        zero = !res;
        carry = (uint8_t)i < ((uint8_t)test_value + 1);
        halfcarry = ((uint8_t)i & 0xF) < ((uint8_t)(test_value & 0xF) + 1);

        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("SBC A,r8: %hhu %hhu (carry) passed\n", i);
        } else {
            printf("SBC A,r8: %hhu %hhu (carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SBC_A_HL(System* system, bool print_all) {
    if (print_all) printf("SBC A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->memory[0xFF] = test_value;
        system->registers[H] = 0x00;
        system->registers[L] = 0xFF;
        SET_FLAG(CARRY, 0);
        SET_FLAG(HALFCARRY, false);
        SBC_A_HL(system, B);
        uint8_t res = (uint8_t)i - test_value;
        zero = !res;
        sub = 1;
        if (i < test_value) { carry = true; } else { carry = false; }
        // if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        halfcarry = (i & 0xF) < (test_value & 0xF);
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("SBC A,[HL]: %hhu %hhu (no carry) passed\n", i);
        } else {
            printf("SBC A,[HL]: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->memory[0xFF] = test_value;
        system->registers[H] = 0x00;
        system->registers[L] = 0xFF;
        SET_FLAG(CARRY, 1);
        SET_FLAG(HALFCARRY, false);
        SBC_A_HL(system, B);
        uint8_t res = (uint8_t)i - (uint8_t)test_value - 1;
        sub = 1;
        zero = !res;
        carry = (uint8_t)i < ((uint8_t)test_value + 1);
        halfcarry = ((uint8_t)i & 0xF) < ((uint8_t)(test_value & 0xF) + 1);

        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("SBC A,[HL]: %hhu %hhu (carry) passed\n", i);
        } else {
            printf("SBC A,[HL]: %hhu %hhu (carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SBC_A_n8(System* system, bool print_all) {
    if (print_all) printf("SBC A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(CARRY, 0);
        SET_FLAG(HALFCARRY, false);
        SBC_A_n8(system, B, test_value);
        uint8_t res = (uint8_t)i - test_value;
        zero = !res;
        sub = 1;
        if (i < test_value) { carry = true; } else { carry = false; }
        // if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        halfcarry = (i & 0xF) < (test_value & 0xF);
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("SBC A,n8: %hhu %hhu (no carry) passed\n", i);
        } else {
            printf("SBC A,n8: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;

        SET_FLAG(HALFCARRY, false);
        SET_FLAG(CARRY, true);
        SBC_A_n8(system, B, test_value);
        uint8_t res = (uint8_t)i - (uint8_t)test_value - 1;
        sub = 1;
        zero = !res;
        carry = (uint8_t)i < ((uint8_t)test_value + 1);
        halfcarry = ((uint8_t)i & 0xF) < ((uint8_t)(test_value & 0xF) + 1);

        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("SBC A,n8: %hhu %hhu (carry) passed\n", i);
        } else {
            printf("SBC A,n8: %hhu %hhu (carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SUB_A_r8(System* system, bool print_all) {
    if (print_all) printf("SBC A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->registers[C] = test_value;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        SUB_A_r8(system, B, C);
        uint8_t res = (uint8_t)i - test_value;
        zero = !res;
        sub = 1;
        if (i < test_value) { carry = true; } else { carry = false; }
        // if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        halfcarry = (i & 0xF) < (test_value & 0xF);
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("SUB A,r8: %hhu %hhu passed\n", i);
        } else {
            printf("SUB A,r8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SUB_A_HL(System* system, bool print_all) {
    if (print_all) printf("SBC A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->memory[0xFF] = test_value;
        system->registers[H] = 0x00;
        system->registers[L] = 0xFF;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        SUB_A_HL(system, B);
        uint8_t res = (uint8_t)i - test_value;
        zero = !res;
        sub = 1;
        if (i < test_value) { carry = true; } else { carry = false; }
        // if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        halfcarry = (i & 0xF) < (test_value & 0xF);
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("SUB A,[HL]: %hhu %hhu (no carry) passed\n", i);
        } else {
            printf("SUB A,[HL]: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SUB_A_n8(System* system, bool print_all) {
    if (print_all) printf("SBC A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        SUB_A_n8(system, B, test_value);
        uint8_t res = (uint8_t)i - test_value;
        zero = !res;
        sub = 1;
        if (i < test_value) { carry = true; } else { carry = false; }
        // if ((i & 0xF + test_value & 0xF) & 0x10 == 0x10) { halfcarry = true; } else { halfcarry = false; }
        halfcarry = (i & 0xF) < (test_value & 0xF);
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("SUB A,n8: %hhu %hhu passed\n", i);
        } else {
            printf("SUB A,n8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_XOR_A_r8(System* system, bool print_all) {
    if (print_all) printf("XOR A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->registers[C] = test_value;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        bool carry = GET_FLAG(CARRY);
        XOR_A_r8(system, B, C);
        uint8_t res = (uint8_t)i ^ test_value;
        carry = false;
        halfcarry = false;
        zero = res == 0 ? true : false;
        sub = false;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("XOR A,r8: %hhu %hhu passed\n", i);
        } else {
            printf("XOR A,r8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_XOR_A_HL(System* system, bool print_all) {
    if (print_all) printf("XOR A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        system->memory[0xFF] = test_value;
        system->registers[H] = 0x00;
        system->registers[L] = 0xFF;
        system->registers[F] = 0x00;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        XOR_A_HL(system, B);
        uint8_t res = (uint8_t)i ^ test_value;
        carry = false;
        halfcarry = false;
        zero = res == 0 ? true : false;
        sub = false;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO)) {
            //printf("XOR A,[HL]: %hhu %hhu passed\n", i);
        } else {
            printf("XOR A,[HL]: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_XOR_A_n8(System* system, bool print_all) {
    if (print_all) printf("XOR A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i < 0xFF; i++) {
        system->registers[B] = i;
        SET_FLAG(CARRY, false);
        SET_FLAG(HALFCARRY, false);
        XOR_A_n8(system, B, test_value);
        uint8_t res = (uint8_t)i ^ test_value;
        carry = false;
        halfcarry = false;
        zero = res == 0 ? true : false;
        sub = false;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            //printf("XOR A,n8: %hhu %hhu passed\n", i);
        } else {
            printf("XOR A,n8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}
