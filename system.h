#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	NO_ERROR,
	FILE_NOT_FOUND,
	FILE_SIZE_WEIRD,

	WINDOW_INITIALIZATION_ERROR,
} Errors;

typedef struct {
	uint8_t pixel_scale;
} Settings;

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *tile_texture;
	SDL_Rect tile_rect;
} Graphics;

typedef struct {
	uint8_t registers[12];
	uint8_t memory[65536];
	uint16_t current_instruction;
	uint8_t current_instruction_length;
	uint8_t current_instruction_duration;
	uint8_t n8;
	uint16_t n16;
	bool IME;
	bool interrupt_pending;
	uint8_t interrupt_counter;
	FILE *rom;
	uint32_t rom_size;
	Graphics *graphics;
	Settings *settings;
} System;

int worker(System *system);

void allocate_system(System *system);

void free_system(System *system);

void close_(System *system, uint8_t code);

void load_memory_dump(System *system, char path[]);

void load_rom(System *system, char path[]);

void execute_instruction(System *system);

void serial(System *system);
