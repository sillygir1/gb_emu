#include "system.h"
#include "graphics.h"
#include "instructions.h"
#include "registers.h"

void allocate_system(System *system) {
	system->settings = malloc(sizeof(*system->settings));
	system->graphics = malloc(sizeof(*system->graphics));
	memset(system->memory, 0xFF, sizeof(system->memory));
	memset(system->registers, 0, sizeof(system->registers));
	SET_16BIT_REGISTER(PC, 0x0100);
	system->interrupt_counter = 0;
	system->interrupt_pending = false;
	system->IME = false;
}

void free_system(System *system) {
	free(system->settings);
	free(system->graphics);
}

void close_(System *system, uint8_t code) {
	free_system(system);
	free(system);
	exit(code);
}

void load_memory_dump(System *system, char path[]) {
	system->rom = fopen(path, "r");
	if (!system->rom) {
		printf("No file or something\n");
		close_(system, FILE_NOT_FOUND);
	}
	if (system->rom)
		fseek(system->rom, 0L, SEEK_END);
	long int length = ftell(system->rom);
	if (length != 0xFFFF) {
		printf("Weird size\n");
		close_(system, FILE_SIZE_WEIRD);
	}
	system->rom_size = length;
	fseek(system->rom, 0L, 0);
	for (int i = 0; i < length; i++) {
		fread(system->memory + i, 1, 1, system->rom);
	}
	system->rom_size = 32768;
}

void load_rom(System *system, char path[]) {

	system->rom = fopen(path, "r");
	if (!system->rom) {
		printf("No file or something\n");
		close_(system, FILE_NOT_FOUND);
	}
	if (system->rom)
		fseek(system->rom, 0L, SEEK_END);
	long int length = ftell(system->rom);
	if (length != 32768) {
		printf("I don't know what to do yet\n");
		close_(system, FILE_SIZE_WEIRD);
	}
	system->rom_size = length;
	fseek(system->rom, 0L, 0);
	for (int i = 0; i < length; i++) {
		fread(system->memory + i, 1, 1, system->rom);
	}
}

void execute_instruction(System *system) {
	if (system->interrupt_pending) {
		if (system->interrupt_counter > 0) {
			system->IME = true;
			system->interrupt_pending = false;
			system->interrupt_counter = 0;
		} else
			system->interrupt_counter += 1;
	}

	uint16_t program_counter = GET_16BIT_REGISTER(PC);
	system->current_instruction = system->memory[program_counter];
	if (system->current_instruction == 0xCB) {
		system->current_instruction =
		    0xCB00 + system->memory[program_counter + 1];
	} else {
		system->n8 = system->memory[program_counter + 1];
		system->n16 =
		    system->n8 + (system->memory[program_counter + 2] << 8);
	}

	// printf("0x%04X: ", program_counter);
	// printf("0x%02X, 0x%02X, 0x%02X\n", system->current_instruction,
	//        system->memory[program_counter + 1],
	//        system->memory[program_counter + 2]);

	get_instruction_length(system);

	get_instruction_duration(system);

	SET_16BIT_REGISTER(PC, program_counter +
				   system->current_instruction_length);

	if (system->current_instruction <= 0xFF)
		execute_regular(system);
	else if (system->current_instruction && 0xFF00 == 0xCB00)
		execute_extended(system);
	else {
		// Throw an error
	}
}

int worker(System *system) {
	if (!system->rom) {
		printf("No file or something\n");
		return FILE_NOT_FOUND;
	}
	if (system->rom_size != 32768) { // Temporary, have to deal with later
		printf("Rom size is %d\n", system->rom_size);
		return FILE_SIZE_WEIRD;
	}

	bool running = true;

	while (running) {

		if (render(system)) {
			break;
		}
	}
	return 0;
}

void serial(System *system) {
	char data = system->memory[0xFF01];
	printf("%c", data);
	system->memory[0xFF02] = 0x01;
}
