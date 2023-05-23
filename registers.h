#pragma once

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// 16-bit registers
typedef enum {
    BC,
    DE,
    HL,
}DoubleRegisters;

// Flags
typedef enum {
    CARRY,
    ADDSUB,
    PV,
    NONE1,
    HALFCARRY,
    NONE2,
    ZERO,
    SIGN,
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