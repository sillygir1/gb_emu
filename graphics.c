#include "graphics.h"
#include "system.h"

bool window_init(System *system) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// throw some error idk
		return false;
	}
	system->graphics->window = SDL_CreateWindow(
	    "gb_emu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	    width * system->settings->pixel_scale,
	    height * system->settings->pixel_scale,
	    SDL_WINDOW_SHOWN | SDL_WINDOW_UTILITY);

	system->graphics->renderer = SDL_CreateRenderer(
	    system->graphics->window, -1, SDL_RENDERER_ACCELERATED);
	return true;
}

void draw_pixel(System *system, uint8_t x, uint8_t y) {
	SDL_Rect r;
	r.x = x * system->settings->pixel_scale;
	r.y = y * system->settings->pixel_scale;
	r.w = system->settings->pixel_scale;
	r.h = system->settings->pixel_scale;

	SDL_SetRenderDrawColor(system->graphics->renderer, 0, 0, 0, 255);

	SDL_RenderFillRect(system->graphics->renderer, &r);
}

void draw_tiles(System *system, uint16_t start) {
	if (start) { // for testing purposes
		     //
	} else {
		//
	}
}

int render(System *system) {
	uint8_t w = 256 / 8;
	uint8_t h = 256 / 8;

	SDL_Texture *texture = SDL_CreateTexture(
	    system->graphics->renderer, SDL_PIXELFORMAT_RGBA8888,
	    SDL_TEXTUREACCESS_STREAMING, 8, 8);

	for (uint8_t i = 0; i < h; i++) {
		for (uint8_t j = 0; j < w; j++) {
			system->graphics->tile_rect[i][j].x =
			    8 * j * system->settings->pixel_scale;
			system->graphics->tile_rect[i][j].y =
			    8 * i * system->settings->pixel_scale;
			system->graphics->tile_rect[i][j].w = _8px;
			system->graphics->tile_rect[i][j].h = _8px;
		}
	}

	unsigned int a = SDL_GetTicks();
	unsigned int b = SDL_GetTicks();
	double delta = 0;

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
			SDL_SetRenderDrawColor(system->graphics->renderer, 0, 0,
					       0, 255);
			SDL_RenderClear(system->graphics->renderer);
			for (uint8_t i = 0; i < h; i++) {
				for (uint8_t j = 0; j < w; j++) {
					uint16_t addr =
					    0x8000 +
					    system->memory[0x9800 + i * w + j] *
						16;
					get_tile(system->memory, texture, addr);
					SDL_RenderCopy(
					    system->graphics->renderer, texture,
					    NULL,
					    &system->graphics->tile_rect[i][j]);
				}
			}

			SDL_RenderPresent(system->graphics->renderer);
		}
	}
	return 0;
}
