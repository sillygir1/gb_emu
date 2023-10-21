// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <string.h>
#include <SDL2/SDL.h>
#include <time.h>

#include "graphics.h"
#include "instructions.h"
#include "registers.h"
#include "system.h"
// #include "tests.h"

static void parse_args(System *system, int argc, char *argv[]) {
	if (argc > 1) {
		if (strcmp(argv[1], "-m") == 0) { // load memory dump
			load_memory_dump(system, argv[2]);
		} else {
			load_rom(system, argv[1]);
		}
	} else {
		printf("No file or something\n");
		close_(system, FILE_NOT_FOUND);
	}
}

int main(int argc, char *argv[]) {
	System *system = malloc(sizeof(*system));
	allocate_system(system);
	system->settings->pixel_scale = 4;

	parse_args(system, argc, argv);

	if (!window_init(system)) {
		printf("Window initialization error\n");
		close_(system, WINDOW_INITIALIZATION_ERROR);
	}

	// render(system);

	uint8_t ret = 0;
	if (system->rom)
		ret = worker(system);

	free_system(system);
	free(system);
	return (ret);
}
