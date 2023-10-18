#pragma once
#include "gb-bytes-to-image/tile.h"
#include "system.h"

#define width 160  // px
#define height 144 // px

#define _8px system->settings->pixel_scale * 8 // tile size

bool window_init(System *system);

int render(System *system);
