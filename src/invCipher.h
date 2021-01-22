#ifndef INV_CIPHER_H
#define INV_CIPHER_H

#include<stdint.h>
#include "constants.h"
#include "ffArithmetic.h"

void invCipher(uint8_t * in, uint8_t * out, uint32_t expandedCipherKey[], uint8_t Nr);
void invSubBytes();
void invShiftRows();
void invMixColumns();
void invAddRoundKey();

void setCurrentState(uint8_t * stateArray);
void copyStates(uint8_t * dstState, uint8_t * srcState);
void setStateCol(uint8_t col, uint32_t value);
uint32_t getStateCol(uint8_t col);

#endif