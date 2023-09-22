#include "system.h"

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

static uint8_t instruction_length(uint8_t instruction) {
	// I'm really not proud of this part,
	// but it'll be like this until i come up
	// with someting actually good
	switch (instruction) {
	case 0x01:
	case 0x08:
	case 0x11:
	case 0x21:
	case 0x31:
	case 0xC2:
	case 0xC3:
	case 0xC4:
	case 0xCA:
	case 0xCC:
	case 0xCD:
	case 0xD2:
	case 0xD4:
	case 0xDA:
	case 0xDC:
	case 0xEA:
	case 0xFA:
		return (3);
		break;
	case 0x06:
	case 0x0E:
	case 0x10:
	case 0x16:
	case 0x18:
	case 0x1E:
	case 0x20:
	case 0x26:
	case 0x28:
	case 0x2E:
	case 0x30:
	case 0x36:
	case 0x38:
	case 0x3E:
	case 0xC6:
	case 0xCE:
	case 0xD6:
	case 0xDE:
	case 0xE0:
	case 0xE2:
	case 0xE6:
	case 0xE8:
	case 0xEE:
	case 0xF0:
	case 0xF2:
	case 0xF6:
	case 0xF8:
	case 0xFE:
		return (2);
		break;
	case 0xD3:
	case 0xDB:
	case 0xDD:
	case 0xE3:
	case 0xE4:
	case 0xEB:
	case 0xEC:
	case 0xED:
	case 0xF4:
	case 0xFC:
	case 0xFD:
		// no such instructions
		return (0);
		break;
	case 0xCB:
		// prefix, figure out later
		break;
	default:
		return (1);
		break;
	}
}

static uint8_t instruction_cycles() {}

void execute_instruction(System *system) {}
