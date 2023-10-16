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

void test_render(System *system) {
	SDL_Texture *texture = SDL_CreateTexture(
	    system->graphics->renderer, SDL_PIXELFORMAT_RGBA8888,
	    SDL_TEXTUREACCESS_STREAMING, 8, 8);

	uint8_t bytes[16] = {0x3c, 0x7e, 0x42, 0x42, 0x42, 0x42,
			     0x42, 0x42, 0x7e, 0x5e,

			     0x7e, 0xa,	 0x7c, 0x56, 0x38, 0x7c};
	get_tile(bytes, texture, 0);

	unsigned int a = SDL_GetTicks();
	unsigned int b = SDL_GetTicks();
	double delta = 0;

	// Rectangle to apply texture to
	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	dst.w = system->settings->pixel_scale * 8;
	dst.h = system->settings->pixel_scale * 8;

	// Window display loop
	bool keep_window_open = true;
	while (keep_window_open) {
		SDL_Event e;
		while (SDL_PollEvent(&e) > 0) {
			switch (e.type) {
			case SDL_QUIT:
				keep_window_open = false;
				break;
			}
		}
		a = SDL_GetTicks();
		delta = a - b;
		if (delta > 1000 / 60.0) {
			SDL_SetRenderDrawColor(system->graphics->renderer, 255,
					       255, 255, 255);
			SDL_RenderClear(system->graphics->renderer);
			SDL_RenderCopy(system->graphics->renderer, texture,
				       NULL, &dst);
			SDL_RenderPresent(system->graphics->renderer);
		}
	}
}

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

	test_render(system);
	// render(system);

	free_system(system);
	free(system);
	return (0);
}
