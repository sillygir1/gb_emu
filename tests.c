#include "tests.h"

/* Batch tests */

static uint16_t address = 0x00FF;

bool test_all(System* system, bool print_all) {
    uint16_t sum = 0;
    /* 8-bit instructions */
    sum += (int)test_8bit(system, print_all);

    /* 16-bit instructions*/
    sum += (int)test_16bit(system, print_all);

    /* Stack operations instructions */
    sum += (int)test_stack(system, print_all);

    /* Bit operations instructions */
    sum += test_bit(system, print_all);

    /* Bit shift instructions */
    sum += test_bitshift(system, print_all);

    /* Result */
    if (sum) { printf("\nTotal of %hu failed tests.\n", sum); } else { printf("\nNo failures!\n"); }
}

bool test_8bit(System* system, bool print_all) {
    uint16_t sum = 0;
    printf("\n8-bit instructions test.\n");
    /* 8-bit instructions */
    for (uint32_t i = 0; i <= 0xFF; i++) {
        if (print_all) printf("i: %hhu\n", i);
        sum += test_ADC_A_r8(system, i, print_all);
        sum += test_ADC_A_HL(system, i, print_all);
        sum += test_ADC_A_n8(system, i, print_all);
        sum += test_ADD_A_r8(system, i, print_all);
        sum += test_ADD_A_HL(system, i, print_all);
        sum += test_ADD_A_n8(system, i, print_all);
        sum += test_AND_A_r8(system, i, print_all);
        sum += test_AND_A_HL(system, i, print_all);
        sum += test_AND_A_n8(system, i, print_all);
        sum += test_CP_A_r8(system, i, print_all);
        sum += test_CP_A_HL(system, i, print_all);
        sum += test_CP_A_n8(system, i, print_all);
        sum += test_OR_A_r8(system, i, print_all);
        sum += test_OR_A_HL(system, i, print_all);
        sum += test_OR_A_n8(system, i, print_all);
        sum += test_SBC_A_r8(system, i, print_all);
        sum += test_SBC_A_HL(system, i, print_all);
        sum += test_SBC_A_n8(system, i, print_all);
        sum += test_SUB_A_r8(system, i, print_all);
        sum += test_SUB_A_HL(system, i, print_all);
        sum += test_SUB_A_n8(system, i, print_all);
        sum += test_XOR_A_r8(system, i, print_all);
        sum += test_XOR_A_HL(system, i, print_all);
        sum += test_XOR_A_n8(system, i, print_all);
    }
    sum += test_DEC_r8(system, print_all);
    sum += test_DEC_HL(system, print_all);
    sum += test_INC_r8(system, print_all);
    sum += test_INC_HL(system, print_all);
    /* Result */
    if (sum) { printf("\n8-bit instructions:\nTotal of %hu failed runs.\n", sum); } else { printf("\n8-bit instructions:\nNo failures!\n"); }
    return sum;
}

bool test_16bit(System* system, bool print_all) {
    uint16_t sum = 0;
    /* They are very long */
    printf("\n16-bit instructions test.\n");
    for (uint32_t i = 0; i <= 0xFFFF; i++) {
        sum += test_ADD_HL_r16(system, i, print_all);
    }
    sum += test_DEC_r16(system, print_all);
    sum += test_INC_r16(system, print_all);

    /* Result */
    if (sum) { printf("\n16-bit instructions:\nTotal of %hu failed tests.\n", sum); } else { printf("\n16-bit instructions:\nNo failures!\n"); }
    return sum;
}

bool test_bit(System* system, bool print_all) {
    uint16_t sum = 0;
    printf("\nBit instructions test.\n");
    for (uint32_t i = 0; i <= 0xFF; i++) {
        sum += test_BIT_u3_r8(system, i, print_all);
        sum += test_BIT_u3_HL(system, i, print_all);
        sum += test_RES_u3_r8(system, i, print_all);
        sum += test_RES_u3_HL(system, i, print_all);
        sum += test_SET_u3_r8(system, i, print_all);
        sum += test_SET_u3_HL(system, i, print_all);
        sum += test_SWAP_r8(system, i, print_all);
        sum += test_SWAP_HL(system, i, print_all);
    }

    /* Result */
    if (sum) { printf("\nBit instructions:\nTotal of %hu failed tests.\n", sum); } else { printf("\nBit instructions:\nNo failures!\n"); }
    return sum;
}

bool test_bitshift(System* system, bool print_all) {
    uint16_t sum = 0;
    printf("\nBit shift instructions test.\n");

    for (uint16_t i = 0; i <= 0xFF; i++) {
        sum += test_RL_r8(system, i, print_all);
        sum += test_RL_HL(system, i, print_all);
        sum += test_RLA(system, i, print_all);
        sum += test_RLC_r8(system, i, print_all);
        sum += test_RLC_HL(system, i, print_all);
        sum += test_RLCA(system, i, print_all);
        sum += test_RR_r8(system, i, print_all);
        sum += test_RR_HL(system, i, print_all);
        sum += test_RRA(system, i, print_all);
        sum += test_RRC_r8(system, i, print_all);
        sum += test_RRC_HL(system, i, print_all);
        sum += test_RRCA(system, i, print_all);
        sum += test_SLA_r8(system, i, print_all);
        sum += test_SLA_HL(system, i, print_all);
        sum += test_SRA_r8(system, i, print_all);
        sum += test_SRA_HL(system, i, print_all);
        sum += test_SRL_r8(system, i, print_all);
        sum += test_SRL_HL(system, i, print_all);
    }

    /* Result */
    if (sum) { printf("\nBit shift instructions:\nTotal of %hu failed tests.\n", sum); } else { printf("\nBit shift instructions:\nNo failures!\n"); }
    return sum;
}

bool test_stack(System* system, bool print_all) {
    uint16_t sum = 0;
    /* They are very long too */
    printf("\nStack operations instructions test.\n");
    for (uint32_t i = 0; i <= 0xFFFF; i++) {
        sum += test_ADD_HL_SP(system, i, print_all);
        // do test_ADD_SP_e8
    }

    /* Result */
    if (sum) { printf("\nStack operations instructions:\nTotal of %hu failed tests.\n", sum); } else { printf("\n16-bit instructions:\nNo failures!\n"); }
    return sum;
}

/* 8-bit arithmetic and logic instructions */

bool test_ADC_A_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("ADC A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("ADC A,r8: %hhu (no carry) passed\n", i);
        } else {
            printf("ADC A,r8: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("ADC A,r8: %hhu (carry) passed\n", i);
        } else {
            printf("ADC A,r8: %hhu %hhu (carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_ADC_A_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("ADC A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
        system->registers[B] = i;
        system->memory[address] = test_value;
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
            if (print_all)printf("ADC A,[HL]: %hhu (no carry) passed\n", i);
        } else {
            printf("ADC A,[HL]: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    for (uint16_t i = 0; i <= 0xFF; i++) {
        system->registers[B] = i;
        system->memory[address] = test_value;
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
            if (print_all)printf("ADC A,[HL]: %hhu (carry) passed\n", i);
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

bool test_ADC_A_n8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("ADC A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("ADC A,n8: %hhu (no carry) passed\n", i);
        } else {
            printf("ADC A,n8: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("ADC A,n8: %hhu (carry) passed\n", i);
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

bool test_ADD_A_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("ADD A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("ADD A,r8: %hhu passed\n", i);
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

bool test_ADD_A_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("ADD A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("ADD A,[HL]: %hhu passed\n", i);
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

bool test_ADD_A_n8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("ADD A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("ADD A,n8: %hhu passed\n", i);
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

bool test_AND_A_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("AND A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("AND A,r8: %hhu (no carry) passed\n", i);
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

bool test_AND_A_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("AND A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
        system->registers[B] = i;
        system->memory[address] = test_value;
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
            if (print_all)printf("ADC A,[HL]: %hhu passed\n", i);
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

bool test_AND_A_n8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("AND A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("ADC A,n8: %hhu passed\n", i);
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

bool test_CP_A_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("CP A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("CP A,r8: %hhu passed\n", i);
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

bool test_CP_A_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("CP A,HL test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
        system->registers[B] = i;
        system->memory[address] = test_value;
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
            if (print_all)printf("CP A,[HL]: %hhu passed\n", i);
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

bool test_CP_A_n8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("CP A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("CP A,r8: %hhu passed\n", i);
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

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("DEC r8: %hhu passed\n", i);
        } else {
            printf("DEC r8: %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
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

    for (uint16_t i = 0; i <= 0xFF; i++) {
        system->memory[address] = i;
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
        if ((uint8_t)system->memory[address] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            if (print_all)printf("DEC [HL]: %hhu passed\n", i);
        } else {
            printf("DEC [HL]: %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, res, zero, sub, halfcarry, carry, system->memory[address], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
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

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("INC r8: %hhu passed\n", i);
        } else {
            printf("INC r8: %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
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

    for (uint16_t i = 0; i <= 0xFF; i++) {
        /* Default values */
        system->memory[address] = i;
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
        if ((uint8_t)system->memory[address] == (uint8_t)res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            if (print_all)printf("INC [HL]: %hhu passed\n", i);
        } else {
            printf("INC [HL]: %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, res, zero, sub, halfcarry, carry, system->memory[address], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_OR_A_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("OR A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("OR A,r8: %hhu passed\n", i);
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

bool test_OR_A_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("OR A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
        system->registers[B] = i;
        system->memory[address] = test_value;
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
            if (print_all)printf("OR A,[HL]: %hhu passed\n", i);
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

bool test_OR_A_n8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("OR A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("OR A,n8: %hhu passed\n", i);
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

bool test_SBC_A_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SBC A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("SBC A,r8: %hhu (no carry) passed\n", i);
        } else {
            printf("SBC A,r8: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("SBC A,r8: %hhu (carry) passed\n", i);
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

bool test_SBC_A_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SBC A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
        system->registers[B] = i;
        system->memory[address] = test_value;
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
            if (print_all)printf("SBC A,[HL]: %hhu (no carry) passed\n", i);
        } else {
            printf("SBC A,[HL]: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }

    for (uint16_t i = 0; i <= 0xFF; i++) {
        system->registers[B] = i;
        system->memory[address] = test_value;
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
            if (print_all)printf("SBC A,[HL]: %hhu (carry) passed\n", i);
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

bool test_SBC_A_n8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SBC A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("SBC A,n8: %hhu (no carry) passed\n", i);
        } else {
            printf("SBC A,n8: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("SBC A,n8: %hhu (carry) passed\n", i);
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

bool test_SUB_A_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SBC A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("SUB A,r8: %hhu passed\n", i);
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

bool test_SUB_A_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SBC A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
        system->registers[B] = i;
        system->memory[address] = test_value;
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
            if (print_all)printf("SUB A,[HL]: %hhu (no carry) passed\n", i);
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

bool test_SUB_A_n8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SBC A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("SUB A,n8: %hhu passed\n", i);
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

bool test_XOR_A_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("XOR A,r8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("XOR A,r8: %hhu passed\n", i);
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

bool test_XOR_A_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("XOR A,[HL] test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
        system->registers[B] = i;
        system->memory[address] = test_value;
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
            if (print_all)printf("XOR A,[HL]: %hhu passed\n", i);
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

bool test_XOR_A_n8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("XOR A,n8 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint16_t i = 0; i <= 0xFF; i++) {
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
            if (print_all)printf("XOR A,n8: %hhu passed\n", i);
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

/* 16-bit arithmetic instructions */

bool test_ADD_HL_r16(System* system, uint16_t test_value, bool print_all) {
    if (print_all) printf("ADD [HL],r16 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint32_t i = 0; i <= 0xFFFF; i++) {
        zero = GET_FLAG(ZERO);
        SET_FLAG(SUB, true);
        SET_FLAG(HALFCARRY, false);
        SET_FLAG(CARRY, false);
        SET_16BIT_REGISTER(HL, i);
        SET_16BIT_REGISTER(BC, test_value);
        ADD_HL_r16(system, BC);
        sub = false;
        uint16_t res = i + test_value;
        carry = (i + test_value) > 0xFFFF;
        halfcarry = ((i & 0xFFF) + (test_value & 0xFFF)) > 0xFFF;

        if (GET_16BIT_REGISTER(HL) == res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            if (print_all)printf("ADD [HL],r16: %hhu passed\n", i);
        } else {
            printf("ADD [HL],r16: %hu %hu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, GET_16BIT_REGISTER(HL), GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }

    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_DEC_r16(System* system, bool print_all) {
    if (print_all) printf("DEC r16 test:\n");
    bool failed = false;

    for (uint32_t i = 0; i <= 0xFFFF; i++) {
        SET_16BIT_REGISTER(BC, i);
        DEC_r16(system, BC);
        uint16_t res = i - 1;

        if (GET_16BIT_REGISTER(BC) == res) {
            if (print_all)printf("DEC r16: %hhu passed\n", i);
        } else {
            printf("DEC r16: %hu failed\nExpected: %u got: %u\n", i, res, GET_16BIT_REGISTER(BC));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_INC_r16(System* system, bool print_all) {
    if (print_all) printf("INC r16 test:\n");
    bool failed = false;

    for (uint32_t i = 0; i <= 0xFFFF; i++) {
        SET_16BIT_REGISTER(BC, i);
        INC_r16(system, BC);
        uint16_t res = i + 1;

        if (GET_16BIT_REGISTER(BC) == res) {
            if (print_all)printf("INC r16: %hhu passed\n", i);
        } else {
            printf("INC r16: %hu failed\nExpected: %u got: %u\n", i, res, GET_16BIT_REGISTER(BC));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

/* Bit operations instructions */

bool test_BIT_u3_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("BIT u3,r8 test:\n");
    bool failed = false;
    bool zero = false;

    for (int i = 0; i < 8; i++) {
        system->registers[B] = test_value;
        BIT_u3_r8(system, i, B);
        zero = !(test_value & (1 << i));
        if (GET_FLAG(ZERO) == zero) {
            if (print_all)printf("BIT u3,r8: %hhu %hhu passed\n", i, test_value);
        } else {
            printf("BIT u3,r8: %hhu %hhu failed\nExpected: z: %u got: z: %u\n", i, test_value, zero, GET_FLAG(ZERO));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_BIT_u3_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("BIT u3,[HL] test:\n");
    bool failed = false;
    bool zero = false;

    for (int i = 0; i < 8; i++) {
        system->memory[address] = test_value;
        SET_16BIT_REGISTER(HL, address);
        BIT_u3_HL(system, i);
        zero = !(test_value & (1 << i));
        if (GET_FLAG(ZERO) == zero) {
            if (print_all)printf("BIT u3,[HL]: %hhu %hhu passed\n", i, test_value);
        } else {
            printf("BIT u3,[HL]: %hhu %hhu failed\nExpected: z: %u got: z: %u\n", i, test_value, zero, GET_FLAG(ZERO));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_RES_u3_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("RES u3,r8 test:\n");
    bool failed = false;

    for (int i = 0; i < 8; i++) {
        system->registers[B] = test_value;
        RES_u3_r8(system, i, B);
        uint8_t res = test_value & ~(1 << i);
        if (res == system->registers[B]) {
            if (print_all)printf("RES u3,r8: %hhu %hhu passed\n", i, test_value);
        } else {
            printf("RES u3,r8: %hhu %hhu failed\nExpected: %u got: %u\n", i, test_value, res, system->registers[B]);
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_RES_u3_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("RES u3,[HL] test:\n");
    bool failed = false;

    for (int i = 0; i < 8; i++) {
        system->memory[address] = test_value;
        SET_16BIT_REGISTER(HL, address);
        RES_u3_HL(system, i);
        uint8_t res = test_value & ~(1 << i);
        if (res == system->memory[address]) {
            if (print_all)printf("RES u3,[HL]: %hhu %hhu passed\n", i, test_value);
        } else {
            printf("RES u3,[HL]: %hhu %hhu failed\nExpected: %u got: %u\n", i, test_value, res, system->registers[B]);
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SET_u3_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SET u3,r8 test:\n");
    bool failed = false;

    for (int i = 0; i < 8; i++) {
        system->registers[B] = test_value;
        SET_u3_r8(system, i, B);
        uint8_t res = test_value | (1 << i);
        if (res == system->registers[B]) {
            if (print_all)printf("SET u3,r8: %hhu %hhu passed\n", i, test_value);
        } else {
            printf("SET u3,r8: %hhu %hhu failed\nExpected: %u got: %u\n", i, test_value, res, system->registers[B]);
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SET_u3_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SET u3,[HL] test:\n");
    bool failed = false;

    for (int i = 0; i < 8; i++) {
        system->memory[address] = test_value;
        SET_16BIT_REGISTER(HL, address);
        SET_u3_HL(system, i);
        uint8_t res = test_value | (1 << i);
        if (res == system->memory[address]) {
            if (print_all)printf("SET u3,[HL]: %hhu %hhu passed\n", i, test_value);
        } else {
            printf("SET u3,[HL]: %hhu %hhu failed\nExpected: %u got: %u\n", i, test_value, res, system->memory[address]);
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SWAP_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SWAP r8 test:\n");
    bool failed = false;
    bool zero = false;

    system->registers[B] = test_value;
    SWAP_r8(system, B);

    uint8_t temp = test_value & 0xF;
    uint8_t res = (test_value >> 4) + (test_value << 4);
    zero = !res;
    if ((uint8_t)system->registers[B] == (uint8_t)res && 0 == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
        if (print_all)printf("SWAP r8: %hhu (no carry) passed\n", test_value);
    } else {
        printf("SWAP r8: %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", test_value, res, zero, 0, 0, 0, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
        failed = true;
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SWAP_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SWAP [HL] test:\n");
    bool failed = false;
    bool zero = false;

    system->memory[address] = test_value;
    SET_16BIT_REGISTER(HL, address);
    SWAP_HL(system);
    uint8_t temp = test_value & 0xF;
    uint8_t res = (test_value >> 4) + (test_value << 4);
    zero = !res;
    if ((uint8_t)system->memory[address] == (uint8_t)res && 0 == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
        if (print_all)printf("SWAP [HL]: %hhu (no carry) passed\n", test_value);
    } else {
        printf("SWAP [HL]: %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", test_value, res, zero, 0, 0, 0, system->memory[address], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
        failed = true;
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

/* Bit shift instructions */

bool test_RL_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("RL r8 test:\n");
    bool failed = false;
    bool zero = false;
    bool carry = false;

    system->registers[B] = test_value;
    for (uint8_t i = 1; i < 9; i++) {
        carry = system->registers[B] & (1 << 7);
        SET_FLAG(CARRY, false);
        uint8_t res = (system->registers[B] << 1) + 0;
        RL_r8(system, B);
        zero = !res;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RL r8: %hhu (no carry) passed\n", test_value);
        } else {
            printf("RL r8: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    system->registers[B] = test_value;
    for (uint8_t i = 1; i < 9; i++) {
        SET_FLAG(CARRY, true);
        carry = system->registers[B] & (1 << 7);
        uint8_t res = (system->registers[B] << 1) + 1;
        RL_r8(system, B);
        zero = !res;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RL r8: %hhu (no carry) passed\n", test_value);
        } else {
            printf("RL r8: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_RL_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("RL [HL] test:\n");
    bool failed = false;
    bool zero = false;
    bool carry = false;

    system->memory[address] = test_value;
    SET_16BIT_REGISTER(HL, address);
    for (uint8_t i = 1; i < 9; i++) {
        SET_FLAG(CARRY, false);
        carry = system->memory[address] & (1 << 7);
        uint8_t res = (system->memory[address] << 1) + 0;
        RL_HL(system);
        zero = !res;
        if ((uint8_t)system->memory[address] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RL [HL]: %hhu (no carry) passed\n", test_value);
        } else {
            printf("RL [HL]: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->memory[address], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    system->memory[address] = test_value;
    for (uint8_t i = 1; i < 9; i++) {
        SET_FLAG(CARRY, true);
        carry = system->memory[address] & (1 << 7);
        uint8_t res = (system->memory[address] << 1) + 1;
        RL_HL(system);
        zero = !res;
        if ((uint8_t)system->memory[address] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RL [HL]: %hhu (carry) passed\n", test_value);
        } else {
            printf("RL [HL]: %hhu %hhu (carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->memory[address], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_RLA(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("RLA test:\n");
    bool failed = false;
    bool carry = false;
    system->registers[A] = test_value;
    for (uint8_t i = 1; i < 9; i++) {
        SET_FLAG(CARRY, false);
        carry = system->registers[A] & (1 << 7);
        uint8_t res = (system->registers[A] << 1) + 0;
        RLA(system);
        if ((uint8_t)system->registers[A] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && 0 == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RLA: %hhu (no carry) passed\n", test_value);
        } else {
            printf("RLA: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, 0, 0, 0, carry, system->registers[A], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    system->registers[A] = test_value;
    for (uint8_t i = 1; i < 9; i++) {
        SET_FLAG(CARRY, true);
        carry = system->registers[A] & (1 << 7);
        uint8_t res = (system->registers[A] << 1) + 1;
        RLA(system);
        if ((uint8_t)system->registers[A] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && 0 == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RLA: %hhu (carry) passed\n", test_value);
        } else {
            printf("RLA: %hhu %hhu (carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, 0, 0, 0, carry, system->registers[A], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_RLC_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("RLC r8 test:\n");
    bool failed = false;
    bool zero = false;
    bool carry = false;
    system->registers[B] = test_value;

    for (uint8_t i = 1; i < 9; i++) {
        carry = system->registers[B] & (1 << 7);
        uint8_t res = (system->registers[B] << 1) + carry;
        RLC_r8(system, B);
        zero = !res;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RLC r8: %hhu passed\n", test_value);
        } else {
            printf("RLC r8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_RLC_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("RLC [HL] test:\n");
    bool failed = false;
    bool zero = false;
    bool carry = false;

    system->memory[address] = test_value;
    SET_16BIT_REGISTER(HL, address);

    for (uint8_t i = 1; i < 9; i++) {
        carry = system->memory[address] & (1 << 7);
        uint8_t res = (system->memory[address] << 1) + carry;
        RLC_HL(system);
        zero = !res;
        if ((uint8_t)system->memory[address] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RLC [HL]: %hhu passed\n", test_value);
        } else {
            printf("RLC [HL]: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->memory[address], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_RLCA(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("RLCA test:\n");
    bool failed = false;
    bool carry = false;
    system->registers[A] = test_value;

    for (uint8_t i = 1; i < 9; i++) {
        carry = system->registers[A] & (1 << 7);
        uint8_t res = (system->registers[A] << 1) + carry;
        RLCA(system);
        if ((uint8_t)system->registers[A] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && 0 == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RLCA: %hhu passed\n", test_value);
        } else {
            printf("RLCA: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, 0, 0, 0, carry, system->registers[A], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_RR_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("RR r8 test:\n");
    bool failed = false;
    bool zero = false;
    bool carry = false;

    system->registers[B] = test_value;
    for (uint8_t i = 1; i < 9; i++) {
        carry = system->registers[B] & 1;
        SET_FLAG(CARRY, false);
        uint8_t res = (system->registers[B] >> 1);
        RR_r8(system, B);
        zero = !res;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RR r8: %hhu (no carry) passed\n", test_value);
        } else {
            printf("RR r8: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    system->registers[B] = test_value;
    for (uint8_t i = 1; i < 9; i++) {
        SET_FLAG(CARRY, true);
        carry = system->registers[B] & 1;
        uint8_t res = (system->registers[B] >> 1) + (1 << 7);
        RR_r8(system, B);
        zero = !res;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RR r8: %hhu (carry) passed\n", test_value);
        } else {
            printf("RR r8: %hhu %hhu (carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_RR_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("RR [HL] test:\n");
    bool failed = false;
    bool zero = false;
    bool carry = false;

    system->memory[address] = test_value;
    SET_16BIT_REGISTER(HL, address);
    for (uint8_t i = 1; i < 9; i++) {
        SET_FLAG(CARRY, false);
        carry = system->memory[address] & 1;
        uint8_t res = (system->memory[address] >> 1);
        RR_HL(system);
        zero = !res;
        if ((uint8_t)system->memory[address] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RR [HL]: %hhu (no carry) passed\n", test_value);
        } else {
            printf("RR [HL]: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->memory[address], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    system->memory[address] = test_value;
    for (uint8_t i = 1; i < 9; i++) {
        SET_FLAG(CARRY, true);
        carry = system->memory[address] & 1;
        uint8_t res = (system->memory[address] >> 1) + (1 << 7);
        RR_HL(system);
        zero = !res;
        if ((uint8_t)system->memory[address] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RR [HL]: %hhu (carry) passed\n", test_value);
        } else {
            printf("RR [HL]: %hhu %hhu (carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->memory[address], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_RRA(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("RRA test:\n");
    bool failed = false;
    bool carry = false;
    system->registers[A] = test_value;
    for (uint8_t i = 1; i < 9; i++) {
        SET_FLAG(CARRY, false);
        carry = system->registers[A] & 1;
        uint8_t res = (system->registers[A] >> 1);
        RRA(system);
        if ((uint8_t)system->registers[A] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && 0 == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RRA: %hhu (no carry) passed\n", test_value);
        } else {
            printf("RRA: %hhu %hhu (no carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, 0, 0, 0, carry, system->registers[A], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    system->registers[A] = test_value;
    for (uint8_t i = 1; i < 9; i++) {
        SET_FLAG(CARRY, true);
        carry = system->registers[A] & 1;
        uint8_t res = (system->registers[A] >> 1) + (1 << 7);
        RRA(system);
        if ((uint8_t)system->registers[A] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && 0 == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RRA: %hhu (carry) passed\n", test_value);
        } else {
            printf("RRA: %hhu %hhu (carry) failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, 0, 0, 0, carry, system->registers[A], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_RRC_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("RRC r8 test:\n");
    bool failed = false;
    bool zero = false;
    bool carry = false;
    system->registers[B] = test_value;

    for (uint8_t i = 1; i < 9; i++) {
        carry = system->registers[B] & 1;
        uint8_t res = (system->registers[B] >> 1) + (carry << 7);
        RRC_r8(system, B);
        zero = !res;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RRC r8: %hhu passed\n", test_value);
        } else {
            printf("RRC r8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_RRC_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("RRC [HL] test:\n");
    bool failed = false;
    bool zero = false;
    bool carry = false;

    system->memory[address] = test_value;
    SET_16BIT_REGISTER(HL, address);

    for (uint8_t i = 1; i < 9; i++) {
        carry = system->memory[address] & 1;
        uint8_t res = (system->memory[address] >> 1) + (carry << 7);
        RRC_HL(system);
        zero = !res;
        if ((uint8_t)system->memory[address] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RRC [HL]: %hhu passed\n", test_value);
        } else {
            printf("RRC [HL]: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->memory[address], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_RRCA(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("RRCA test:\n");
    bool failed = false;
    bool carry = false;
    system->registers[A] = test_value;

    for (uint8_t i = 1; i < 9; i++) {
        carry = system->registers[A] & 1;
        uint8_t res = (system->registers[A] >> 1) + (carry << 7);
        RRCA(system);
        if ((uint8_t)system->registers[A] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && 0 == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("RRCA: %hhu passed\n", test_value);
        } else {
            printf("RRCA: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, 0, 0, 0, carry, system->registers[A], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SLA_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SLA r8 test:\n");
    bool failed = false;
    bool zero = false;
    bool carry = false;
    system->registers[B] = test_value;

    for (uint8_t i = 1; i < 9; i++) {
        carry = system->registers[B] & (1 << 7);
        uint8_t res = (system->registers[B] << 1);
        SLA_r8(system, B);
        zero = !res;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("SLA r8: %hhu passed\n", test_value);
        } else {
            printf("SLA r8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SLA_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SLA [HL] test:\n");
    bool failed = false;
    bool zero = false;
    bool carry = false;

    system->memory[address] = test_value;
    SET_16BIT_REGISTER(HL, address);
    for (uint8_t i = 1; i < 9; i++) {
        carry = system->memory[address] & (1 << 7);
        uint8_t res = (system->memory[address] << 1);
        SLA_HL(system);
        zero = !res;
        if ((uint8_t)system->memory[address] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("SLA [HL]: %hhu passed\n", test_value);
        } else {
            printf("SLA [HL]: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->memory[address], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SRA_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SRA r8 test:\n");
    bool failed = false;
    bool zero = false;
    bool carry = false;
    system->registers[B] = test_value;

    for (uint8_t i = 1; i < 9; i++) {
        carry = system->registers[B] & 1;
        uint8_t res = (system->registers[B] >> 1) + (system->registers[B] & (1 << 7));
        SRA_r8(system, B);
        zero = !res;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("SRA r8: %hhu passed\n", test_value);
        } else {
            printf("SRA r8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SRA_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SRA [HL] test:\n");
    bool failed = false;
    bool zero = false;
    bool carry = false;

    system->memory[address] = test_value;
    SET_16BIT_REGISTER(HL, address);

    for (uint8_t i = 1; i < 9; i++) {
        carry = system->memory[address] & 1;
        uint8_t res = (system->memory[address] >> 1) + (system->memory[address] & (1 << 7));
        SRA_HL(system);
        zero = !res;
        if ((uint8_t)system->memory[address] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("SRA [HL]: %hhu passed\n", test_value);
        } else {
            printf("SRA [HL]: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->memory[address], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SRL_r8(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SRL r8 test:\n");
    bool failed = false;
    bool zero = false;
    bool carry = false;
    system->registers[B] = test_value;

    for (uint8_t i = 1; i < 9; i++) {
        carry = system->registers[B] & 1;
        uint8_t res = (system->registers[B] >> 1);
        SRL_r8(system, B);
        zero = !res;
        if ((uint8_t)system->registers[B] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("SRL r8: %hhu passed\n", test_value);
        } else {
            printf("SRL r8: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->registers[B], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_SRL_HL(System* system, uint8_t test_value, bool print_all) {
    if (print_all) printf("SRL [HL] test:\n");
    bool failed = false;
    bool zero = false;
    bool carry = false;
    system->memory[address] = test_value;
    SET_16BIT_REGISTER(HL, address);

    for (uint8_t i = 1; i < 9; i++) {
        carry = system->memory[address] & 1;
        uint8_t res = (system->memory[address] >> 1);
        SRL_HL(system);
        zero = !res;
        if ((uint8_t)system->memory[address] == (uint8_t)res && carry == GET_FLAG(CARRY) && 0 == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && 0 == GET_FLAG(SUB)) {
            if (print_all)printf("SRL [HL]: %hhu passed\n", test_value);
        } else {
            printf("SRL [HL]: %hhu %hhu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, 0, 0, carry, system->memory[address], GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }
    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

/* Stack operations instructions */

bool test_ADD_HL_SP(System* system, uint16_t test_value, bool print_all) {
    if (print_all) printf("ADD [HL],r16 test:\n");
    bool failed = false;
    bool carry = false;
    bool halfcarry = false;
    bool zero = false;
    bool sub = false;

    for (uint32_t i = 0; i <= 0xFFFF; i++) {
        zero = GET_FLAG(ZERO);
        SET_FLAG(SUB, true);
        SET_FLAG(HALFCARRY, false);
        SET_FLAG(CARRY, false);
        SET_16BIT_REGISTER(HL, i);
        SET_16BIT_REGISTER(SP, test_value);
        ADD_HL_SP(system);
        sub = false;
        uint16_t res = i + test_value;
        carry = (i + test_value) > 0xFFFF;
        halfcarry = ((i & 0xFFF) + (test_value & 0xFFF)) > 0xFFF;

        if (GET_16BIT_REGISTER(HL) == res && carry == GET_FLAG(CARRY) && halfcarry == GET_FLAG(HALFCARRY) && zero == GET_FLAG(ZERO) && sub == GET_FLAG(SUB)) {
            if (print_all)printf("ADD [HL],r16: %hhu passed\n", i);
        } else {
            printf("ADD [HL],r16: %hu %hu failed\nExpected: %u z: %u n: %u hc: %u c: %u, got: %u z: %u n: %u hc: %u c: %u\n", i, test_value, res, zero, sub, halfcarry, carry, GET_16BIT_REGISTER(HL), GET_FLAG(ZERO), GET_FLAG(SUB), GET_FLAG(HALFCARRY), GET_FLAG(CARRY));
            failed = true;
        }
    }

    if (!failed) {
        if (print_all) printf("Success!\n");
        return 0;
    } else
        return 1;
}

bool test_ADD_SP_e8(System* system, uint16_t test_value, bool print_all); // TODO
