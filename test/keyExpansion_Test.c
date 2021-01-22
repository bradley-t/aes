#include "../src/keyExpansion.h"
#include <stdio.h>

int test_applySbox();
int test_subWord();
int test_rotWord();
int test_keyExpansion();

uint8_t key[16] =       { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                          0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
uint32_t expanded[44] = { 0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c,
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

int main(int argc, char *argv[]) {
  printf("\nTesting keyExpansion.c\n");
  int testsPassed = 0;
  testsPassed += test_applySbox();
  testsPassed += test_subWord();
  testsPassed += test_rotWord();
  testsPassed += test_keyExpansion();
  printf("Total tests passed: %d\n\n", testsPassed);
}

int test_applySbox() {
  int ret_value = 0;
  int tests_passed = 0;
  printf("-- Testing test_applySbox ... ");

  tests_passed += ( applySbox(0x00) == 0x63 );
  tests_passed += ( applySbox(0x40) == 0x09 );
  tests_passed += ( applySbox(0x80) == 0xcd );
  tests_passed += ( applySbox(0xc0) == 0xba );

  if ( tests_passed == 4 ) {
    printf("success\n");
    ret_value = 1;
  }
  else {
    printf("failure\n");
  }
  return ret_value;
}

int test_subWord() {
  int ret_value = 0;
  int tests_passed = 0;
  printf("-- Testing test_subWord ... ");

  tests_passed += ( subWord(0x00102030) == 0x63cab704 );
  tests_passed += ( subWord(0x40506070) == 0x0953d051 );
  tests_passed += ( subWord(0x8090a0b0) == 0xcd60e0e7 );
  tests_passed += ( subWord(0xc0d0e0f0) == 0xba70e18c );

  if ( tests_passed == 4 ) {
    printf("success\n");
    ret_value = 1;
  }
  else {
    printf("failure\n");
  }
  return ret_value;
}

int test_rotWord() {
  int ret_value = 0;
  int tests_passed = 0;
  printf("-- Testing test_rotWord ... ");

  tests_passed += ( rotWord(0x09cf4f3c) == 0xcf4f3c09 );
  tests_passed += ( rotWord(0x2a6c7605) == 0x6c76052a );

  if ( tests_passed == 2 ) {
    printf("success\n");
    ret_value = 1;
  }
  else {
    printf("failure\n");
  }
  return ret_value;
}

int test_keyExpansion() {
  int ret_value = 1;
  printf("-- Testing test_keyExpansion ... ");
  uint8_t expanded_key_size = (NB * ( NR_128 + 1 ));
  uint32_t expandedKey[expanded_key_size];
  keyExpansion(key, expandedKey, NK_128, expanded_key_size);

  for (int i = 0; i < expanded_key_size; i++){
    if (expandedKey[i] != expanded[i]){
      ret_value = 0;
      printf("failure\n");
      break;
    }
  }

  if ( ret_value != 0 ) {
    printf("success\n");
  }
  return ret_value;
}