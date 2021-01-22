#ifndef CIPHER_H
#define CIPHER_H

#include<stdint.h>
#include "constants.h"
#include "ffArithmetic.h"

void cipher(uint8_t * in, uint8_t * out, uint32_t expandedCipherKey[], uint8_t Nr);

void subBytes();
void shiftRows();
void mixColumns();
void addRoundKey(uint32_t roundKey[]);

void setState(uint8_t * stateArray);
void copyState(uint8_t * dstState, uint8_t * srcState);

void setCol(uint8_t col, uint32_t value);
uint32_t getCol(uint8_t col);

#endif