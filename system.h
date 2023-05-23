#pragma once

#include <stdint.h>

typedef struct {
    uint8_t registers[8];
    uint8_t memory[65536];
}System;