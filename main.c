#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "instructions.h"
#include "registers.h"
#include "system.h"

void test_registers(System* system) {
    system->registers[B] = 0xC0;
    system->registers[C] = 0xDE;
    printf("%x\n", get_GPR16bit(system->registers, BC));
    system->registers[F] = 0b11111111;
    // SET_FLAG(CARRY, false);
    SET_FLAG(ZERO, false);
    SET_FLAG(SIGN, false);
    printf("Carry: %u\nZero: %u\nSign: %u\n",
        GET_FLAG(CARRY),
        GET_FLAG(ZERO),
        GET_FLAG(SIGN));
}

void test_adc(System* system) {
    system->registers[B] = 0b11110000;
    system->memory[0xF0] = 0b11111;
    system->registers[H] = 0x00;
    system->registers[L] = 0xFF;
    SET_FLAG(CARRY, false);
    ADC_A_HL(system, B);
    printf("B: 0x%x\nCarry: 0x%x\n", system->registers[B], GET_FLAG(CARRY));
}


int main(int argc, char* argv[]) {
    System* sys = malloc(sizeof(*sys));
    memset(sys->memory, 0, sizeof(sys->memory));
    memset(sys->registers, 0, sizeof(sys->registers));

    // test_registers(sys->registers);
    test_adc(sys);

    free(sys);
    return(0);
}

