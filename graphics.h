#pragma once
#include "gb-bytes-to-image/tile.h"
#include "system.h"

#define width 160  // px
#define height 144 // px

bool window_init(System *system);

int render(System *system);
