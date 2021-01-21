#include <stdint.h>
#include <stdio.h>
#include "sBox.c"

#define NB 4
#define NR_128 10
#define NR_192 12
#define NR_256 14
#define NK_128 4
#define NK_192 6
#define NK_256 8

#define LS_BYTE 0x000000ff

uint32_t Rcon[52] = { 0x00000000, 
           0x01000000, 0x02000000, 0x04000000, 0x08000000, 
           0x10000000, 0x20000000, 0x40000000, 0x80000000, 
           0x1B000000, 0x36000000, 0x6C000000, 0xD8000000, 
           0xAB000000, 0x4D000000, 0x9A000000, 0x2F000000, 
           0x5E000000, 0xBC000000, 0x63000000, 0xC6000000, 
           0x97000000, 0x35000000, 0x6A000000, 0xD4000000, 
           0xB3000000, 0x7D000000, 0xFA000000, 0xEF000000, 
           0xC5000000, 0x91000000, 0x39000000, 0x72000000, 
           0xE4000000, 0xD3000000, 0xBD000000, 0x61000000, 
           0xC2000000, 0x9F000000, 0x25000000, 0x4A000000, 
           0x94000000, 0x33000000, 0x66000000, 0xCC000000, 
           0x83000000, 0x1D000000, 0x3A000000, 0x74000000, 
           0xE8000000, 0xCB000000, 0x8D000000};


uint32_t subWord(uint32_t word){
  uint32_t result = 0;
  result = result | (applySbox( word >> 24 ) << 24 );
  result = result | (applySbox( ( word >> 16 ) & LS_BYTE ) << 16 );
  result = result | (applySbox( ( word >> 8 ) & LS_BYTE ) << 8 );
  result = result | (applySbox( word & LS_BYTE ));
  return result;
}

uint32_t rotWord(uint32_t word){
  return ( ( word << 8 ) | word >> 24 );
}

void keyExpansion(uint8_t key[], uint32_t w[], uint8_t Nk, uint8_t w_size){
  uint32_t temp;

  for ( uint8_t i = 0; i < Nk; i++ ) {
    w[i] = ((key[4 * i] << 24) | (key[4 * i + 1] << 16) | (key[4 * i + 2] << 8) | key[4 * i + 3]);
  }

  for ( uint8_t i = Nk; i < w_size; i++ ) {
    temp = w[i - 1];
    if ((i % Nk) == 0) {
      temp = subWord(rotWord(temp)) ^ Rcon[ i / Nk ];
    }
    else if (Nk > 6 && i % Nk == 4) {
      temp = subWord(temp);
    }
    w[i] = w[i - Nk] ^ temp;
  }
}