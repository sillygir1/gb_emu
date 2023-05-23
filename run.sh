#!/bin/bash
if gcc main.c instructions.c registers.c -o out/binary; then 
./out/binary 
fi