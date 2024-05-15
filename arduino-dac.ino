#include <avr/pgmspace.h>
#include <Arduino.h>
#include <pins_arduino.h>
#include "fonts/processed/Sigi-5px-Condensed-Regular.h"

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


/*
#define dac_write(x) \
    PORTD = (B00111111 & (x)) << 2 ; \
    PORTB = (x) >> 6;
*/

#define mov(x, y) PORTD=(x); PORTB=(y)


/*
uint8_t char_h[] = {
    0,6,
    0,5,
    0,4,
    0,3,
    0,2,
    0,1,
    0,0,

    0,1,
    1,2,
    2,3,
    3,2,
    4,1,
    4,0,
};
*/


// number of there and backs
#define DRAW_REPEATS 5

uint8_t char_h[] = {
    0,6,
    0,5,
    0,4,
    0,3,
    0,2,
    0,1,
    0,0,

    0,1,
    0,2,
    1,3,

    2,3,

    3,2,
    3,1,
    3,0,
};


void draw_segment(uint8_t x, uint8_t y, uint8_t *c, size_t len){
    //mov(c[0] + x, c[0] + y);
    //delayMicroseconds(2);

    size_t points = len/2;

    int i;
    for(int _ = 0; _ < DRAW_REPEATS; _++){

        for(i = 0; i < points; i++){
            mov(c[2*i] + x,c[2*i+1] + y);
            delay_clock(10);
        }

        for(i = points-1; i >=0 ; i--){
            mov(c[2*i] + x,c[2*i+1] + y);
            delay_clock(10);
        }
    }

    for(i = 0; i < points; i++){
        mov(c[2*i] + x,c[2*i+1] + y);
        delay_clock(10);
    }
}


// returns width
uint16_t write_char(uint8_t x, uint8_t y, char c){
    CharacterData data;
    memcpy_P(&data, &characterDataArray[c], sizeof(CharacterData));

    uint8_t coords[data.length];
    memcpy_P(coords, &characterArray[data.offsets[0]], data.length);

    for(int i = 0; i < data.segments; i++){
        draw_segment(x, y, coords + (data.offsets[i] - data.offsets[0]), data.lengths[i]);
    }
    return data.width;
}





// #define enable() DDRC &= B01111111
// #define disable() DDRC |= B10000000; PORTC &= B10000000

void setup(){
    noInterrupts();
    DDRB = DDRB | B11111111;
    DDRD = DDRD | B11111111;
}

/*
uint8_t sini(uint8_t x){
    return round(127* (sinf( 2*M_PI*(x/255.) )+1) );
}
uint8_t cosi(uint8_t x){
    return round(127* (cosf( 2*M_PI*(x/255.) )+1) );
}
*/

void sawtooth(){
    for(uint8_t i = 0; i < 255; i++){
        //dac_write(sini(i));
        // dac_write(i);
        PORTD=i;
        PORTB=i;
        //delayMicroseconds(1);
        delay_clock(5);
        //delayClocks(2);
        //delay(1);
    }

    /*
    for(uint8_t i = 255; i > 0; i--){
        //dac_write(sini(i));
        // dac_write(i);
        PORTD=i;
        PORTB=i;
        delayMicroseconds(1);
        //delay(1);
    }
    */
}
void test(){
    mov(110,110);
    delayMicroseconds(5);
    mov(115,120);
    delayMicroseconds(5);
    mov(120,110);
    delayMicroseconds(5);

}

void loop(){
    uint16_t x = 10;
    uint16_t y = 10;
    for(int i = 0; i < 63; i++){
        x += write_char(x, y, i+33) + 1;
        if(x > 240){
            x = 10;
            y += CHAR_HEIGHT + 1;
        }
    }

    //sawtooth();
    //draw_char(80, 100, char_h, sizeof(char_h));
    //draw_char(140, 100, char_h, sizeof(char_h));
    //draw_char(200, 100, char_h, sizeof(char_h));
    // test();
    //write_char(80, 100, 'A');

    //write_char(10, 10, 'B');
    //write_char(200, 100, 'C');
    //
}
