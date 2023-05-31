#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t registers[12];
    uint8_t memory[65536];
}System;