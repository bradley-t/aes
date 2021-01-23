#include "../src/aes.h"
#include <stdio.h>

/*******************************************************************
 * This is an overall project integration test
 * 
 * --Each test was taken from Appendix C of the fips documentation--
 * 
 * *****************************************************************/

int test_encrypt128();
int test_decrypt128();
int test_encrypt192();
int test_decrypt192();
int test_encrypt256();
int test_decrypt256();

uint8_t plaintext[4][4] = { { 0x00, 0x44, 0x88, 0xcc },
                            { 0x11, 0x55, 0x99, 0xdd },
                            { 0x22, 0x66, 0xaa, 0xee }, 
                            { 0x33, 0x77, 0xbb, 0xff } };

uint8_t aes128_key[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                           0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

uint8_t aes192_key[24] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                          0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                          0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 };

uint8_t aes256_key[32] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                          0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                          0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                          0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };

uint8_t aes128_ciphertext[4][4] = { { 0x69, 0x6a, 0xd8, 0x70 },
                                    { 0xc4, 0x7b, 0xcd, 0xb4 },
                                    { 0xe0, 0x04, 0xb7, 0xc5 },
                                    { 0xd8, 0x30, 0x80, 0x5a }};

// uint32_t aes192_ciphertext[4] = { 0xdda97ca4, 0x864cdfe0, 0x6eaf70a0, 0xec0d7191};
uint8_t aes192_ciphertext[4][4] = { { 0xdd, 0x86, 0x6e, 0xec }, 
                                    { 0xa9, 0x4c, 0xaf, 0x0d },
                                    { 0x7c, 0xdf, 0x70, 0x71 },
                                    { 0xa4, 0xe0, 0xa0, 0x91 }};
// uint32_t aes256_ciphertext[4] = { 0x8ea2b7ca, 0x516745bf, 0xeafc4990, 0x4b496089};
uint8_t aes256_ciphertext[4][4] = { {0x8e, 0x51, 0xea, 0x4b},
                                    {0xa2, 0x67, 0xfc, 0x49},
                                    {0xb7, 0x45, 0x49, 0x60},
                                    {0xca, 0xbf, 0x90, 0x89}};


int main(int argc, char *argv[]) {
  printf("\nTesting AES implementation\n");
  printf("**********************************************************\n");
  printf("* This is an overall project integration test\n*\n");
  printf("* Each test was taken from Appendix C of the fips documentation\n*\n");
  printf("**********************************************************\n");
  int testsPassed = 0;
  testsPassed += test_encrypt128();
  testsPassed += test_decrypt128();
  testsPassed += test_encrypt192();
  testsPassed += test_decrypt192();
  testsPassed += test_encrypt256();
  testsPassed += test_decrypt256();
  printf("Total tests passed: %d\n\n", testsPassed);
}

int test_encrypt128(){
  printf("-- Testing test_appendixC_128bit_encrypt ... ");
  uint8_t output[4][4];
  encrypt(&plaintext[0][0], &aes128_key[0], 128, &output[0][0]);
  for ( int i = 0; i < 4; i++ ) {
    for ( int j = 0; j < 4; j++ ) {
      if (output[i][j] != aes128_ciphertext[i][j]){
        printf("failure\n");
        return 0;
      }
    }
  }
  printf("success\n");
  return 1;
}

int test_decrypt128(){
  printf("-- Testing test_appendixC_128bit_decrypt ... ");
  uint8_t output[4][4];
  decrypt(&aes128_ciphertext[0][0], &aes128_key[0], 128, &output[0][0]);
  for ( int i = 0; i < 4; i++ ) {
    for ( int j = 0; j < 4; j++ ) {
      if (output[i][j] != plaintext[i][j]){
        printf("failure\n");
        return 0;
      }
    }
  }
  printf("success\n");
  return 1;
}

int test_encrypt192(){
  printf("-- Testing test_appendixC_192bit_encrypt ... ");
  uint8_t output[4][4];
  encrypt(&plaintext[0][0], &aes192_key[0], 192, &output[0][0]);
  for ( int i = 0; i < 4; i++ ) {
    for ( int j = 0; j < 4; j++ ) {
      if (output[i][j] != aes192_ciphertext[i][j]){
        printf("failure\n");
        return 0;
      }
    }
  }
  printf("success\n");
  return 1;
}

int test_decrypt192(){
  printf("-- Testing test_appendixC_192bit_decrypt ... ");
  uint8_t output[4][4];
  decrypt(&aes192_ciphertext[0][0], &aes192_key[0], 192, &output[0][0]);
  for ( int i = 0; i < 4; i++ ) {
    for ( int j = 0; j < 4; j++ ) {
      if (output[i][j] != plaintext[i][j]){
        printf("failure\n");
        return 0;
      }
    }
  }
  printf("success\n");
  return 1;
}

int test_encrypt256() {
  printf("-- Testing test_appendixC_256bit_encrypt ... ");
  uint8_t output[4][4];
  encrypt(&plaintext[0][0], &aes256_key[0], 256, &output[0][0]);
  for ( int i = 0; i < 4; i++ ) {
    for ( int j = 0; j < 4; j++ ) {
      if (output[i][j] != aes256_ciphertext[i][j]){
        printf("failure\n");
        return 0;
      }
    }
  }
  printf("success\n");
  return 1;
}

int test_decrypt256(){
  printf("-- Testing test_appendixC_256bit_decrypt ... ");
  uint8_t output[4][4];
  decrypt(&aes256_ciphertext[0][0], &aes256_key[0], 256, &output[0][0]);
  for ( int i = 0; i < 4; i++ ) {
    for ( int j = 0; j < 4; j++ ) {
      if (output[i][j] != plaintext[i][j]){
        printf("failure\n");
        return 0;
      }
    }
  }
  printf("success\n");
  return 1;
}