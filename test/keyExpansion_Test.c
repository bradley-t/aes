#include "../src/keyExpansion.c"
#include <stdio.h>

int test_applySbox();
int test_subWord();
int test_rotWord();


int main(int argc, char *argv[]) {
  printf("\nTesting keyExpansion.c\n");
  int testsPassed = 0;
  testsPassed += test_applySbox();
  testsPassed += test_subWord();
  testsPassed += test_rotWord();
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