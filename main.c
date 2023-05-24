#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "instructions.h"
#include "registers.h"
#include "system.h"
#include "tests.h"

int main(int argc, char* argv[]) {
    System* system = malloc(sizeof(*system));
    memset(system->memory, 0, sizeof(system->memory));
    memset(system->registers, 0, sizeof(system->registers));

    test_all(system);

    // GET_ALL_FLAGS();
    free(system);
    return(0);
}