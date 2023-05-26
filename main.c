#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "instructions.h"
#include "registers.h"
#include "system.h"
#include "tests.h"



int main(int argc, char* argv[]) {
    System* system = malloc(sizeof(*system));
    memset(system->memory, 0, sizeof(system->memory));
    memset(system->registers, 0, sizeof(system->registers));

    clock_t start, end;
    double cpu_time_used;
    system->registers[B] = 0;
    start = clock();

    test_all(system, false);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("CPU time used: %lf\n", cpu_time_used);

    free(system);
    return(0);
}