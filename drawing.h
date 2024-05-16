#ifndef DRAWING_H_
#define DRAWING_H_
#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

#define mov(x, y) PORTD=(x); PORTB=(y)

// for testing dac linearity
#define sawtooth() for(uint8_t i = 0; i < 255; i++){ mov(i,i); delay_clock(5);}

#define DELAY_CLOCK_1 __asm( "nop" )
#define DELAY_CLOCK_2 DELAY_CLOCK_1; DELAY_CLOCK_1
#define DELAY_CLOCK_3 DELAY_CLOCK_2; DELAY_CLOCK_1
#define DELAY_CLOCK_4 DELAY_CLOCK_3; DELAY_CLOCK_1
#define DELAY_CLOCK_5 DELAY_CLOCK_4; DELAY_CLOCK_1
#define DELAY_CLOCK_6 DELAY_CLOCK_5; DELAY_CLOCK_1
#define DELAY_CLOCK_7 DELAY_CLOCK_6; DELAY_CLOCK_1
#define DELAY_CLOCK_8 DELAY_CLOCK_7; DELAY_CLOCK_1
#define DELAY_CLOCK_9 DELAY_CLOCK_8; DELAY_CLOCK_1
#define DELAY_CLOCK_10 DELAY_CLOCK_9; DELAY_CLOCK_1
#define delay_clock(x) DELAY_CLOCK_##x


void setup_drawing();

// returns width
uint16_t write_char(uint8_t x, uint8_t y, char c);

void write(const char *s, int len);

#ifdef __cplusplus
}
#endif

#endif
