#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	NO_ERROR,
	FILE_NOT_FOUND,
	FILE_SIZE_WEIRD,
} Errors;

typedef struct {
	uint8_t registers[12];
	uint8_t memory[65536];
	uint16_t current_instruction;
	uint8_t current_instruction_length;
	uint8_t current_instruction_duration;
	bool IME;
	bool interrupt_pending;
	FILE *rom;
	uint32_t rom_size;
} System;

bool worker(System *system);

void close(System *system, uint8_t code);

void load_rom(System *system, char path[]);

void execute_instruction(System *system);
