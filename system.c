#include "system.h"
#include "instructions.h"
#include "registers.h"

void close(System *system, uint8_t code) {
	free(system);
	exit(code);
}

void load_rom(System *system, char path[]) {

	system->rom = fopen(path, "r");
	if (!system->rom) {
		printf("No file or something\n");
		close(system, FILE_NOT_FOUND);
	}
	if (system->rom)
		fseek(system->rom, 0L, SEEK_END);
	long int length = ftell(system->rom);
	if (length != 32768) {
		printf("I don't know what to do yet\n");
		close(system, FILE_SIZE_WEIRD);
	}
	system->rom_size = length;
	fseek(system->rom, 0L, 0);
	for (int i = 0; i < length; i++) {
		fread(system->memory + i, 1, 1, system->rom);
	}
}

void execute_instruction(System *system) {
	uint16_t program_counter = GET_16BIT_REGISTER(PC);
	system->current_instruction = system->memory[program_counter];
	if (system->current_instruction == 0xCB) {
		system->current_instruction =
		    0xCB00 + system->memory[program_counter + 1];
	}
	get_instruction_length(system);

	// DEAL WITH THE 0xCB ONES

	SET_16BIT_REGISTER(PC, program_counter +
				   system->current_instruction_length);

	// execute the instruction

	SET_16BIT_REGISTER(PC, program_counter +
				   system->current_instruction_length);
}

bool worker(System *system) {
	if (!system->rom) {
		printf("No file or something\n");
		return FILE_NOT_FOUND;
	}
	if (system->rom_size != 32768) {
		printf("Rom size is %d\n", system->rom_size);
		return FILE_SIZE_WEIRD;
	}
}
