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
#include "tests.h"

int main(int argc, char *argv[]) {
	System *system = malloc(sizeof(*system));
	allocate_system(system);

	if (argc > 1) {
		load_rom(system, argv[1]);
	} else {
		printf("No file or something\n");
		close_(system, FILE_NOT_FOUND);
	}

	uint8_t ret = 0;
	if (system->rom)
		ret = worker(system);
	if (ret)
		return (ret);

	system->settings->pixel_scale = 4;

	if (!window_init(system)) {
		printf("Window initialization error\n");
		close_(system, WINDOW_INITIALIZATION_ERROR);
	}

	test_render(system, 0x4357);
	// render(system);

	free_system(system);
	free(system);
	return (0);
}
