#!/bin/bash
if gcc main.c instructions.c registers.c tests.c -o out/binary -O3; then 
./out/binary
else
exit 1 
fi