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

int render(System *system) { return 0; }
