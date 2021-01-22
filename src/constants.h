#ifndef CONSTANTS_H
#define CONSTANTS_H

#include<stdint.h>

#define LS_BYTE 0x000000ff
#define STATE_SIZE 16
#define STATE_COLS 4
#define STATE_ROWS 4

extern const uint8_t NB;
extern const uint8_t NR_128;
extern const uint8_t NR_192;
extern const uint8_t NR_256;
extern const uint8_t NK_128;
extern const uint8_t NK_192;
extern const uint8_t NK_256;

extern const uint32_t Rcon[52];
extern const uint8_t Sbox[16][16];
extern const uint8_t InvSbox[16][16];

uint8_t applySbox(uint8_t byte);
uint8_t applyInvSbox(uint8_t byte);

#endif