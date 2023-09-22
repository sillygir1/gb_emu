#include "registers.h"

uint16_t get_GPR16bit(uint8_t registers[], uint8_t reg) {
  uint16_t ret = 0;
  switch (reg) {
  case AF:
    ret = (registers[A] << 8) + registers[F];
    break;
  case BC:
    ret = (registers[B] << 8) + registers[C];
    break;
  case DE:
    ret = (registers[D] << 8) + registers[E];
    break;
  case HL:
    ret = (registers[H] << 8) + registers[L];
    break;
  case SP:
    ret = (registers[8] << 8) + registers[9];
    break;
  case PC:
    ret = (registers[10] << 8) + registers[11];
    break;
  default:
    printf("You want WHAT register??\n");
    ret = 0;
    break;
  }
  return ret;
}

void put_GPR16bit(uint8_t registers[], uint8_t reg, uint16_t value) {
  switch (reg) {
  case AF:
    registers[A] = (value & 0xFF00) >> 8;
    registers[F] = value & 0x00FF;
  case BC:
    registers[B] = (value & 0xFF00) >> 8;
    registers[C] = value & 0x00FF;
    break;
  case DE:
    registers[D] = (value & 0xFF00) >> 8;
    registers[E] = value & 0x00FF;
    break;
  case HL:
    registers[H] = (value & 0xFF00) >> 8;
    registers[L] = value & 0x00FF;
    break;
  case SP:
    registers[8] = (value & 0xFF00) >> 8;
    registers[9] = value & 0x00FF;
    break;
  case PC:
    registers[10] = (value & 0xFF00) >> 8;
    registers[11] = value & 0x00FF;
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

void set_flag(uint8_t registers[], uint8_t flag, bool value) {
  if (value) {
    registers[F] |= (1 << flag);
  } else {
    registers[F] &= ~(1 << flag);
  }
}

void get_all_flags(uint8_t registers[]) {
  printf("Flags:\nz: %hhu\nc: %hhu\nhc: %hhu\nn: %hhu\n",
         get_flag(registers, ZERO), get_flag(registers, CARRY),
         get_flag(registers, HALFCARRY), get_flag(registers, SUB));
}