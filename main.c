// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <string.h>
#include <time.h>

#include "instructions.h"
#include "registers.h"
#include "system.h"
#include "tests.h"

void close(System* system, uint8_t code) {
    free(system);
    exit(code);
}

void load_rom(System* system, char path[]) {

    system->rom = fopen(path, "r");
    if (!system->rom) {
        printf("No file or something\n");
        close(system, FILE_NOT_FOUND);
    }
    if (system->rom) fseek(system->rom, 0L, SEEK_END);
    long int length = ftell(system->rom);
    if (length != 32768) {
        printf("I don't know what to do yet\n");
        close(system, FILE_SIZE_WEIRD);
    }

    fseek(system->rom, 0L, 0);
    for (int i = 0; i < length; i++) {
        fread(system->memory + i, 1, 1, system->rom);
    }
}

int main(int argc, char* argv[]) {
    System* system = malloc(sizeof(*system));
    memset(system->memory, 0, sizeof(system->memory));
    memset(system->registers, 0, sizeof(system->registers));
    if (argc > 1) {
        load_rom(system, argv[1]);
    } else {
        printf("No file or something\n");
        close(system, FILE_NOT_FOUND);
    }

    uint8_t ret = 0;
    if (system->rom) ret = worker(system);
    if (ret) return(ret);

    free(system);
    return(0);
}