#!/bin/bash
x86_64-w64-mingw32-gcc main.c instructions.c registers.c tests.c -o out/binary -O3;