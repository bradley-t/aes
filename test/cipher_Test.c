#include "../src/cipher.c"
#include <stdio.h>

int test_subBytes();
int test_shiftRows();
int test_mixColumns();
int test_addRoundKey();

uint8_t initialState[4][4] = {
    { 0x19, 0xa0, 0x9a, 0xe9 },
    { 0x3d, 0xf4, 0xc6, 0xf8 },
    { 0xe3, 0xe2, 0x8d, 0x48 },
    { 0xbe, 0x2b, 0x2a, 0x08 }
  };

uint8_t afterSubBytesState[4][4] = {
  { 0xd4, 0xe0, 0xb8, 0x1e },
  { 0x27, 0xbf, 0xb4, 0x41 },
  { 0x11, 0x98, 0x5d, 0x52 },
  { 0xae, 0xf1, 0xe5, 0x30 }
};

uint8_t afterShiftRowsState[4][4] = {
  { 0xd4, 0xe0, 0xb8, 0x1e },
  { 0xbf, 0xb4, 0x41, 0x27 },
  { 0x5d, 0x52, 0x11, 0x98 },
  { 0x30, 0xae, 0xf1, 0xe5 }
};

uint8_t afterMixColumnsState[4][4] = {
  { 0x04, 0xe0, 0x48, 0x28 },
  { 0x66, 0xcb, 0xf8, 0x06 },
  { 0x81, 0x19, 0xd3, 0x26 },
  { 0xe5, 0x9a, 0x7a, 0x4c }
};

uint8_t afterAddRoundKeyState[4][4] = {
  { 0xa4, 0x68, 0x6b, 0x02 },
  { 0x9c, 0x9f, 0x5b, 0x6a },
  { 0x7f, 0x35, 0xea, 0x50 },
  { 0xf2, 0x2b, 0x43, 0x49 }
};

uint32_t roundKey[4] = { 0xa0fafe17, 0x88542cb1, 0x23a33939, 0x2a6c7605};

int main(int argc, char *argv[]) {
  printf("\nTesting cipher.c\n");
  int testsPassed = 0;
  testsPassed += test_subBytes();
  testsPassed += test_shiftRows();
  testsPassed += test_mixColumns();
  testsPassed += test_addRoundKey();
  printf("Total tests passed: %d\n\n", testsPassed);
}

int test_subBytes() {
  printf("-- Testing test_subBytes ... ");
  setState(&initialState[0][0]);
  subBytes();
  for ( uint8_t col = 0; col < STATE_COLS; col++ ) {
    for ( uint8_t row = 0; row < STATE_ROWS; row++ ) {
      if (state[col][row] != afterSubBytesState[col][row]){
        printf("failure\n");
        return 0;
      }
    }
  }

  printf("success\n");
  return 1;
}

int test_shiftRows() {
  printf("-- Testing test_shiftRows ... ");
  setState(&afterSubBytesState[0][0]);
  shiftRows();
  for ( uint8_t col = 0; col < STATE_COLS; col++ ) {
    for ( uint8_t row = 0; row < STATE_ROWS; row++ ) {
      if (state[col][row] != afterShiftRowsState[col][row]){
        printf("failure\n");
        return 0;
      }
    }
  }

  printf("success\n");
  return 1;
}

int test_mixColumns() {
  printf("-- Testing test_mixColumns ... ");
  setState(&afterShiftRowsState[0][0]);
  mixColumns();
  for ( uint8_t col = 0; col < STATE_COLS; col++ ) {
    for ( uint8_t row = 0; row < STATE_ROWS; row++ ) {
      if (state[col][row] != afterMixColumnsState[col][row]){
        printf("failure\n");
        return 0;
      }
    }
  }

  printf("success\n");
  return 1;
}

int test_addRoundKey() {
  printf("-- Testing test_addRoundKey ... ");
  setState(&afterMixColumnsState[0][0]);
  addRoundKey(roundKey);
  for ( uint8_t col = 0; col < STATE_COLS; col++ ) {
    for ( uint8_t row = 0; row < STATE_ROWS; row++ ) {
      if (state[col][row] != afterAddRoundKeyState[col][row]){
        printf("failure\n");
        return 0;
      }
    }
  }

  printf("success\n");
  return 1;
}