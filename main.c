// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <string.h>
#include <SDL2/SDL.h>
#include <time.h>

#include "instructions.h"
#include "registers.h"
#include "system.h"
#include "tests.h"

int main(int argc, char *argv[]) {
	System *system = malloc(sizeof(*system));
	memset(system->memory, 0, sizeof(system->memory));
	memset(system->registers, 0, sizeof(system->registers));

	if (argc > 1) {
		load_rom(system, argv[1]);
	} else {
		printf("No file or something\n");
		close(system, FILE_NOT_FOUND);
	}

	uint8_t ret = 0;
	if (system->rom)
		ret = worker(system);
	if (ret)
		return (ret);

	free(system);
	return (0);
}
