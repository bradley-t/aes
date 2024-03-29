#include "aes.h"

void encrypt (uint8_t * plaintext, uint8_t * cipherKey,
              uint32_t keySize, uint8_t * ciphertext){

  uint8_t Nk = (keySize == 256) ? NK_256 : (keySize == 192) ? NK_192 : NK_128;
  uint8_t Nr = (keySize == 256) ? NR_256 : (keySize == 192) ? NR_192 : NR_128;
  uint8_t expanded_key_size = (NB * ( Nr + 1 ));
  uint32_t expandedKey[expanded_key_size];

  keyExpansion(cipherKey, expandedKey, Nk, expanded_key_size);
  cipher(plaintext, ciphertext, expandedKey, Nr);
}
              
void decrypt (uint8_t * ciphertext, uint8_t * cipherKey,
              uint32_t keySize, uint8_t * plaintext){

  uint8_t Nk = (keySize == 256) ? NK_256 : (keySize == 192) ? NK_192 : NK_128;
  uint8_t Nr = (keySize == 256) ? NR_256 : (keySize == 192) ? NR_192 : NR_128;
  uint8_t expanded_key_size = (NB * ( Nr + 1 ));
  uint32_t expandedKey[expanded_key_size];
  
  keyExpansion((uint8_t *)cipherKey, expandedKey, Nk, expanded_key_size);
  invCipher((uint8_t *)ciphertext, (uint8_t *)plaintext, expandedKey, Nr);
}
