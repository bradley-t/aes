#include "keyExpansion.h"

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