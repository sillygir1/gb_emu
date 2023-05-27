#pragma once

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define SET_FLAG(flag, value) set_flag(system->registers, flag, value)
#define GET_FLAG(flag) get_flag(system->registers, flag)
#define GET_ALL_FLAGS() get_all_flags(system->registers)
#define GET_16BIT_REGISTER(REGISTER) get_GPR16bit(system->registers, REGISTER)
#define SET_16BIT_REGISTER(REGISTER, VALUE) put_GPR16bit(system->registers, REGISTER, VALUE)


// 16-bit registers
typedef enum {
    BC,
    DE,
    HL,
    SP,
    PC,
}DoubleRegisters;

// Flags
typedef enum {
    NONE1,
    NONE2,
    NONE3,
    NONE4,
    CARRY,
    HALFCARRY,
    SUB, // Also known as N
    ZERO,
}Flags;

// Registers
typedef enum {
    A,
    F,
    B,
    C,
    D,
    E,
    H,
    L,
}Registers;

// Get 16-bit registers or something idk
// @param registers Registers array
// @param reg Registers to get
// @return Register value
uint16_t get_GPR16bit(uint8_t registers[], uint8_t reg);

// Put 16-bit value in 16-bit register
// @param registers Registers array
// @param reg Register to set
// @param value Register value
void put_GPR16bit(uint8_t registers[], uint8_t reg, uint16_t value);

// Get flag value
// @param registers Registers array
// @param flag Flag name
// @return Flag value
bool get_flag(uint8_t registers[], uint8_t flag);

// Set flag value
// @param registers Registers array
// @param flag Flag name
// @param value Flag value
void set_flag(uint8_t registers[], uint8_t flag, bool value);

// Print all flags to cli
// @param registers Registers array
void get_all_flags(uint8_t registers[]);