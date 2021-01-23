#ifndef AES_H
#define AES_H

#include <stdint.h>
#include "constants.h"
#include "keyExpansion.h"
#include "cipher.h"
#include "invCipher.h"

void encrypt (uint32_t * plaintext, uint32_t * cipherKey,
              uint32_t keySize, uint32_t * ciphertext);
              
void decrypt (uint32_t * ciphertext, uint32_t * cipherKey,
              uint32_t keySize, uint32_t * plaintext);
#endif