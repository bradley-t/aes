#include <stdint.h>
#include <stdbool.h>

uint8_t ffAdd( uint8_t a, uint8_t b ) {
  return a ^ b;
}

uint8_t xtime( uint8_t a ) {
  bool modNeeded = ( ( a & 0x80 ) != 0 );
  a = a << 1;
  if ( modNeeded ) {
    a = a ^ 0x1b;
  }
  return a;
}

uint8_t ffMultiply( uint8_t a, uint8_t b ) {
  uint8_t result = 0;
  uint8_t intermediate_result = b;

  // for each bit in uint8_t from smallest to largest
  for ( uint8_t i = 1; i != 0 && i <= a; i = i << 1 ) { 
    
    if ( ( a & i ) != 0 ) {
      result = result ^ intermediate_result;
    }
  
  intermediate_result = xtime(intermediate_result);
  }
  
  return result;
}
