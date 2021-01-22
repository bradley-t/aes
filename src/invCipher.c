#include "invCipher.h"

uint8_t state[STATE_ROWS][STATE_COLS];


void invCipher(uint8_t * in, uint8_t * out, uint32_t expandedCipherKey[], uint8_t Nr){
  
  setCurrentState(in);

  invAddRoundKey(&expandedCipherKey[4 * Nr]);

  for ( uint8_t round = Nr - 1; round > 0; round--) {
    invShiftRows();
    invSubBytes();
    invAddRoundKey(&expandedCipherKey[4 * round]);
    invMixColumns();
  }

  invShiftRows();
  invSubBytes();
  invAddRoundKey(&expandedCipherKey[0]);

  copyStates(&state[0][0], out);
}

void invSubBytes(){
  for ( uint8_t col = 0; col < STATE_COLS; col++ ) {
    for ( uint8_t row = 0; row < STATE_ROWS; row++ ) {
      state[row][col] = applyInvSbox( state[row][col] );
    }
  }
}

void invShiftRows(){
  for ( uint8_t row = 1; row < STATE_ROWS; row++ ) {
    for ( uint8_t rotations = row; rotations > 0; rotations-- ) {
      uint8_t temp = state[row][3];
      state[row][3] = state[row][2];
      state[row][2] = state[row][1];
      state[row][1] = state[row][0];
      state[row][0] = temp;
    }
  }
}

void invMixColumns(){
  for ( uint8_t col = 0; col < STATE_COLS; col++ ) {
    uint8_t s0_prime = ( ffMultiply(0x0e, state[0][col]) ^ ffMultiply(0x0b, state[1][col]) ^  ffMultiply(0x0d, state[2][col]) ^  ffMultiply(0x09, state[3][col]) );
    uint8_t s1_prime = ( ffMultiply(0x09, state[0][col]) ^ ffMultiply(0x0e, state[1][col]) ^  ffMultiply(0x0b, state[2][col]) ^  ffMultiply(0x0d, state[3][col]) );
    uint8_t s2_prime = ( ffMultiply(0x0d, state[0][col]) ^ ffMultiply(0x09, state[1][col]) ^  ffMultiply(0x0e, state[2][col]) ^  ffMultiply(0x0b, state[3][col]) );
    uint8_t s3_prime = ( ffMultiply(0x0b, state[0][col]) ^ ffMultiply(0x0d, state[1][col]) ^  ffMultiply(0x09, state[2][col]) ^  ffMultiply(0x0e, state[3][col]) );
    state[0][col] = s0_prime;
    state[1][col] = s1_prime;
    state[2][col] = s2_prime;
    state[3][col] = s3_prime;
  }
}

void invAddRoundKey(uint32_t * roundKey){
  for ( uint8_t col = 0; col < STATE_COLS; col++ ) {
    uint32_t value = getStateCol(col) ^ *(roundKey + col);
    setStateCol(col, value);
  }
}

uint32_t getStateCol(uint8_t col){
  return ((state[0][col] << 24) | (state[1][col] << 16) | (state[2][col] << 8) | state[3][col]);
}

void setStateCol(uint8_t col, uint32_t value){
  state[0][col] = ( value >> 24 );
  state[1][col] = ( ( value >> 16 ) & LS_BYTE );
  state[2][col] = ( ( value >> 8 ) & LS_BYTE );
  state[3][col] = ( value & LS_BYTE );
}

void copyStates( uint8_t * srcState, uint8_t * dstState ) {
 for ( uint8_t col = 0; col < STATE_COLS; col++ ) {
    for ( uint8_t row = 0; row < STATE_ROWS; row++ ) {
      *(dstState + (4 * col) + row) = *(srcState + (4 * col) + row);
    }
  }
}
void setCurrentState(uint8_t * stateArray) {
  copyStates(stateArray, &state[0][0]);
}