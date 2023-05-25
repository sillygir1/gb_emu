#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "instructions.h"
#include "registers.h"
#include "system.h"
#include "tests.h"


// #include <time.h> // УБРАТЬ ПОТОМ

int main(int argc, char* argv[]) {
    System* system = malloc(sizeof(*system));
    memset(system->memory, 0, sizeof(system->memory));
    memset(system->registers, 0, sizeof(system->registers));

    test_all(system);


    // clock_t start, end;
    // double cpu_time_used;
    // system->registers[B] = 0;
    // start = clock();
    // for (int i = 0; i < 10000000; i++) {
    //     ADD_A_n8(system, B, (uint8_t)i);
    // }
    // end = clock();
    // cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("CPU time used: %lf\n", cpu_time_used);

    // GET_ALL_FLAGS();
    free(system);
    return(0);
}