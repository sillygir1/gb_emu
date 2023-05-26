#!/bin/bash
if gcc main.c instructions.c registers.c tests.c -o out/binary -O3; then 
./out/binary 
fi