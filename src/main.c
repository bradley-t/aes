#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aes.h"

uint8_t getByte(FILE * file){
  char char_pair[3];
  char_pair[0] = fgetc(file);
  char_pair[1] = fgetc(file);
  char_pair[2] = '\0';
  return (uint8_t)strtol(char_pair, NULL, 16);
}

int main(int argc, char * argv[]){
  // printf("%d", argc);
  if(argc != 4 && argc != 5){
    fprintf(stderr, "Usage: %s key_length key_file input_file [-d | --decrypt]\n\n", argv[0]);
    return 1;
  }
  int key_length = atoi(argv[1]);
  if (key_length != 256 && key_length != 192 && key_length != 128){
    fprintf(stderr, "Key length must be 128, 192 or 256\n");
    fprintf(stderr, "Usage: %s key_length key_file input_file [-d | --decrypt]\n\n", argv[0]);
    return 1;
  }
  FILE * cipher_key_file = fopen( argv[2], "r" );
  FILE * plaintext_file = fopen( argv[3], "r" );
  if (cipher_key_file == NULL || plaintext_file == NULL){
    perror("Unable to open file: ");
    fprintf(stderr, "Usage: %s key_length key_file input_file [-d | --decrypt]\n\n", argv[0]);
    return 1;
  }

  uint8_t aes_key[key_length / 8];
  for (int i = 0; i < (key_length / 8); i++){
    aes_key[i] = getByte(cipher_key_file);
  }

  uint8_t input[4][4];
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      input[j][i] = getByte(plaintext_file);
    }
  }
  fclose(cipher_key_file);
  fclose(plaintext_file);
  uint8_t output[4][4];
  if(argc == 5){
    decrypt(&input[0][0], &aes_key[0], key_length, &output[0][0]);
  }
  else {
    encrypt(&input[0][0], &aes_key[0], key_length, &output[0][0]);
  }
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      printf("%02x", output[j][i]);
    }
  }
  
}