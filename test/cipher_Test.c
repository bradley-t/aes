#include "../src/cipher.c"
#include <stdio.h>

int test_subBytes();
int test_shiftRows();
int test_mixColumns();
int test_addRoundKey();
int test_cipher();

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

uint8_t inputState[4][4] = {
  { 0x32, 0x88, 0x31, 0xe0 },
  { 0x43, 0x5a, 0x31, 0x37 },
  { 0xf6, 0x30, 0x98, 0x07 },
  { 0xa8, 0x8d, 0xa2, 0x34 }
};
uint8_t outputState[4][4] = {
  { 0x39, 0x02, 0xdc, 0x19 },
  { 0x25, 0xdc, 0x11, 0x6a },
  { 0x84, 0x09, 0x85, 0x0b },
  { 0x1d, 0xfb, 0x97, 0x32 }
};

uint32_t expandedCipherKey[44] = { 0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c,
                          0xa0fafe17, 0x88542cb1, 0x23a33939, 0x2a6c7605,
                          0xf2c295f2, 0x7a96b943, 0x5935807a, 0x7359f67f,
                          0x3d80477d, 0x4716fe3e, 0x1e237e44, 0x6d7a883b,
                          0xef44a541, 0xa8525b7f, 0xb671253b, 0xdb0bad00,
                          0xd4d1c6f8, 0x7c839d87, 0xcaf2b8bc, 0x11f915bc,
                          0x6d88a37a, 0x110b3efd, 0xdbf98641, 0xca0093fd,
                          0x4e54f70e, 0x5f5fc9f3, 0x84a64fb2, 0x4ea6dc4f,
                          0xead27321, 0xb58dbad2, 0x312bf560, 0x7f8d292f,
                          0xac7766f3, 0x19fadc21, 0x28d12941, 0x575c006e,
                          0xd014f9a8, 0xc9ee2589, 0xe13f0cc8, 0xb6630ca6 };


uint32_t roundKey[4] = { 0xa0fafe17, 0x88542cb1, 0x23a33939, 0x2a6c7605};

int main(int argc, char *argv[]) {
  printf("\nTesting cipher.c\n");
  int testsPassed = 0;
  testsPassed += test_subBytes();
  testsPassed += test_shiftRows();
  testsPassed += test_mixColumns();
  testsPassed += test_addRoundKey();
  testsPassed += test_cipher();
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

int test_cipher() {
  printf("-- Testing test_cipher ... ");
  uint8_t output[STATE_COLS][STATE_ROWS];
  cipher(&inputState[0][0], &output[0][0], expandedCipherKey, NR_128);
  for ( uint8_t col = 0; col < STATE_COLS; col++ ) {
    for ( uint8_t row = 0; row < STATE_ROWS; row++ ) {
      if (output[col][row] != outputState[col][row]){
        printf("failure\n");
        return 0;
      }
    }
  }

  printf("success\n");
  return 1;
}