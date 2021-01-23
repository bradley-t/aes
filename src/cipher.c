#include "cipher.h"

uint8_t state[STATE_ROWS][STATE_COLS];

void cipher(uint8_t * in, uint8_t * out, uint32_t expandedCipherKey[], uint8_t Nr){
  
  setState(in);

  addRoundKey(&expandedCipherKey[0]);

  for ( uint8_t round = 1; round < Nr; round++) {
    subBytes();
    shiftRows();
    mixColumns();
    addRoundKey(&expandedCipherKey[4 * round]);
  }

  subBytes();
  shiftRows();
  addRoundKey(&expandedCipherKey[4 * Nr]);

  copyState(&state[0][0], out);
}

void subBytes() {
  for ( uint8_t col = 0; col < STATE_COLS; col++ ) {
    for ( uint8_t row = 0; row < STATE_ROWS; row++ ) {
      state[row][col] = applySbox( state[row][col] );
    }
  }
}

void shiftRows(){
  for ( uint8_t row = 1; row < STATE_ROWS; row++ ) {
    for ( uint8_t rotations = row; rotations > 0; rotations-- ) {
      uint8_t temp = state[row][0];
      state[row][0] = state[row][1];
      state[row][1] = state[row][2];
      state[row][2] = state[row][3];
      state[row][3] = temp;
    }
  }
}

void mixColumns(){
  for ( uint8_t col = 0; col < STATE_COLS; col++ ) {
    uint8_t s0_prime = ( ffMultiply(2, state[0][col]) ^ ffMultiply(3, state[1][col]) ^ state[2][col] ^ state[3][col] );
    uint8_t s1_prime = ( state[0][col] ^ ffMultiply(2, state[1][col]) ^ ffMultiply(3, state[2][col]) ^ state[3][col] );
    uint8_t s2_prime = ( state[0][col] ^ state[1][col] ^ ffMultiply(2, state[2][col]) ^ ffMultiply(3, state[3][col]) );
    uint8_t s3_prime = ( ffMultiply(3, state[0][col]) ^ state[1][col] ^ state[2][col] ^ ffMultiply(2, state[3][col]) );
    state[0][col] = s0_prime;
    state[1][col] = s1_prime;
    state[2][col] = s2_prime;
    state[3][col] = s3_prime;
  }
}

void addRoundKey(uint32_t * roundKey){
  // uint32_t * state_p = (uint32_t *)&state[0][0];
  for ( uint8_t col = 0; col < STATE_COLS; col++ ) {
    uint32_t value = getCol(col) ^ *(roundKey + col);
    setCol(col, value);
    // *(state_p + col) = *(state_p + col) ^ *(roundKey + col);
  }
}

uint32_t getCol(uint8_t col){
  return ((state[0][col] << 24) | (state[1][col] << 16) | (state[2][col] << 8) | state[3][col]);
}

void setCol(uint8_t col, uint32_t value){
  state[0][col] = ( value >> 24 );
  state[1][col] = ( ( value >> 16 ) & LS_BYTE );
  state[2][col] = ( ( value >> 8 ) & LS_BYTE );
  state[3][col] = ( value & LS_BYTE );
}

void copyState( uint8_t * srcState, uint8_t * dstState ) {
 for ( uint8_t col = 0; col < STATE_COLS; col++ ) {
    for ( uint8_t row = 0; row < STATE_ROWS; row++ ) {
      *(dstState + (4 * col) + row) = *(srcState + (4 * col) + row);
    }
  }
}
void setState(uint8_t * stateArray) {
  copyState(stateArray, &state[0][0]);
}
