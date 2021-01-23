#ifndef AES_H
#define AES_H

#include <stdint.h>
#include "constants.h"
#include "keyExpansion.h"
#include "cipher.h"
#include "invCipher.h"

void encrypt (uint8_t * plaintext, uint8_t * cipherKey,
              uint32_t keySize, uint8_t * ciphertext);
              
void decrypt (uint8_t * ciphertext, uint8_t * cipherKey,
              uint32_t keySize, uint8_t * plaintext);
#endif