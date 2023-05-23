#include "registers.h"

uint16_t get_GPR16bit(uint8_t registers[], uint8_t reg) {
    uint16_t ret = 0;
    switch (reg) {
    case BC:
        ret = (registers[B] << 8) + registers[C];
        return(ret);
        break;
    case DE:
        ret = (registers[D] << 8) + registers[E];
        return(ret);
        break;
    case HL:
        ret = (registers[H] << 8) + registers[L];
        return(ret);
        break;
    default:
        printf("You want WHAT register??\n");
        break;
    }
}

bool get_flag(uint8_t registers[], uint8_t flag) {
    bool ret = registers[F] & (1 << flag);
    return ret;
}

void set_flag(uint8_t registers[F], uint8_t flag, bool value) {
    if (value) {
        registers[F] |= (1 << flag);
    } else {
        registers[F] &= ~(1 << flag);
    }
}