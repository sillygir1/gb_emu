#pragma once
#include "gb-bytes-to-image/tile.h"
#include "system.h"

#define width_viewport 160  // px, actual screen dimension
#define height_viewport 144 // px, actual screen dimension
#define height_virtual 256  // px
#define width_virtual 256   // px

#define _8px system->settings->pixel_scale * 8 // tile size
#define _pixel_scale system->settings->pixel_scale

bool window_init(System *system);

int render(System *system);
