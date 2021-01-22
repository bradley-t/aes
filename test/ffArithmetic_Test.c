
#include "../src/ffArithmetic.h"
#include <stdio.h>

int test_ffAdd();
int test_xtime();
int test_ffMultiply();


int main(int argc, char *argv[]) {
  printf("\nTesting ffArithmetic.c\n");
  int testsPassed = 0;
  testsPassed += test_ffAdd();
  testsPassed += test_xtime();
  testsPassed += test_ffMultiply();
  printf("Total tests passed: %d\n\n", testsPassed);
}

int test_ffAdd() {
  int ret_value = 0;
  printf("-- Testing test_ffAdd ... ");
  if ( ffAdd( 0x57,0x83 ) == 0xd4 ) {
    printf("success\n");
    ret_value = 1;
  }
  else {
    printf("failure\n");
  }
  return ret_value;
}

int test_xtime() {
  int ret_value = 0;
  int tests_passed = 0;
  printf("-- Testing test_xtime ... ");

  tests_passed += ( xtime(0x57) == 0xae );
  tests_passed += ( xtime(0xae) == 0x47 );
  tests_passed += ( xtime(0x47) == 0x8e );
  tests_passed += ( xtime(0x8e) == 0x07 );

  if ( tests_passed == 4 ) {
    printf("success\n");
    ret_value = 1;
  }
  else {
    printf("failure\n");
  }
  return ret_value;
}

int test_ffMultiply() {
  int ret_value = 0;
  printf("-- Testing test_ffMultiply ... ");
  if ( ffMultiply( 0x57,0x13 ) == 0xfe ) {
    printf("success\n");
    ret_value = 1;
  }
  else {
    printf("failure\n");
  }
  return ret_value;
}