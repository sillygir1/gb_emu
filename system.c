#include "system.h"

bool worker(System* system) {
    if (!system->rom) {
        printf("No file or something\n");
        return FILE_NOT_FOUND;
    }
    if (system->rom_size != 32768) {
        printf("Dunno what to do\n");
        return FILE_SIZE_WEIRD;
    }


}
