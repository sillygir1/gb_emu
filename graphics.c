#include "graphics.h"
#include "registers.h"
#include "system.h"

uint8_t color_palette[4][3] = {{0x00, 0x00, 0x00},
			       {0x67, 0x67, 0x67},
			       {0xb6, 0xb6, 0xb6},
			       {0xff, 0xff, 0xff}};

uint8_t color_palette_inverted[4][3] = {{0xff, 0xff, 0xff},
					{0xb6, 0xb6, 0xb6},
					{0x67, 0x67, 0x67},
					{0x00, 0x00, 0x00}};

bool window_init(System *system) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// throw some error idk
		return false;
	}
	system->graphics->window = SDL_CreateWindow(
	    "gb_emu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	    width_viewport * _pixel_scale, height_viewport * _pixel_scale,
	    SDL_WINDOW_SHOWN | SDL_WINDOW_UTILITY);

	system->graphics->renderer = SDL_CreateRenderer(
	    system->graphics->window, -1, SDL_RENDERER_ACCELERATED);

	system->graphics->tile_texture = SDL_CreateTexture(
	    system->graphics->renderer, SDL_PIXELFORMAT_RGBA8888,
	    SDL_TEXTUREACCESS_STREAMING, 8, 8);
	return true;
}

void draw_pixel(System *system, uint8_t x, uint8_t y) {
	SDL_Rect r;
	r.x = x * _pixel_scale;
	r.y = y * _pixel_scale;
	r.w = _pixel_scale;
	r.h = _pixel_scale;

	SDL_SetRenderDrawColor(system->graphics->renderer, 0, 0, 0, 255);

	SDL_RenderFillRect(system->graphics->renderer, &r);
}

void set_pos(System *system, int i, int j) {
	uint8_t SCX = system->memory[0xFF43];
	uint8_t SCY = system->memory[0xFF42];
	uint16_t x_pos = SCX * _pixel_scale;
	uint16_t y_pos = SCY * _pixel_scale;

	int x = 8 * j * _pixel_scale + x_pos;
	if (x > 255 * _pixel_scale)
		x -= (int)(256 * _pixel_scale);
	int y = 8 * i * _pixel_scale + y_pos;
	if (y > 255 * _pixel_scale)
		y -= 256 * _pixel_scale;
	system->graphics->tile_rect.x = x;
	system->graphics->tile_rect.y = y;
	system->graphics->tile_rect.w = _8px;
	system->graphics->tile_rect.h = _8px;
}

uint16_t get_bg_address(System *system, int i, int j, uint8_t w) {
	int index;
	if (GET_FLAG(0xFF40, 4)) {
		index = i * w + j;
		return 0x8000 + system->memory[0x9800 + index] * 16;
	} else { // THING TO TEST ON PROPER ROM
		index = i * w + j - 128;
		return 0x9000 + system->memory[0x9800 + index] * 16;
	}
}

int render(System *system) {
	uint8_t w = width_virtual / 8;
	uint8_t h = height_virtual / 8;

	uint64_t a = SDL_GetTicks64();
	uint64_t b = SDL_GetTicks64();
	double delta = 0;

	// Window display loop
	bool keep_window_open = true;
	while (keep_window_open) {
		SDL_Event e;
		while (SDL_PollEvent(&e) > 0) {
			switch (e.type) {
				case SDL_QUIT:
					keep_window_open = false;
					return 1;
					break;
			}
		}

		a = SDL_GetTicks64();
		delta = a - b;
		if (delta > 1000 / 60.0) {
			SDL_SetRenderDrawColor(system->graphics->renderer, 255,
					       255, 255, 255);
			// TODO
			// if ( /*get LCDC lcd off flag */ ) continue;
			SDL_RenderClear(system->graphics->renderer);
			for (uint8_t i = 0; i < h; i++) {
				for (uint8_t j = 0; j < w; j++) {
					set_pos(system, i, j);
					uint16_t addr =
					    get_bg_address(system, i, j, w);
					get_tile(system->memory,
						 system->graphics->tile_texture,
						 addr, color_palette_inverted);
					SDL_RenderCopy(
					    system->graphics->renderer,
					    system->graphics->tile_texture,
					    NULL, &system->graphics->tile_rect);
				}
			}

			SDL_RenderPresent(system->graphics->renderer);

			b = SDL_GetTicks64();
		}
	}
	return 0;
}
