#ifndef KEY_EXPANSION_H
#define KEY_EXPANSION_H

#include <stdint.h>
#include <stdio.h>
#include "constants.h"

uint32_t rotWord(uint32_t word);
uint32_t subWord(uint32_t word);
void keyExpansion(uint8_t key[], uint32_t w[], uint8_t Nk, uint8_t w_size);

#endif