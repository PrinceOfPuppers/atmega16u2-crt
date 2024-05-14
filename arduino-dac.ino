#include <avr/pgmspace.h>
#include <Arduino.h>
#include <pins_arduino.h>
#include "fonts/processed/Sigi-5px-Condensed-Regular.h"

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


void draw_char(uint8_t x, uint8_t y, uint8_t *c, size_t len){
    mov(c[0] + x, c[0] + y);
    delayMicroseconds(10);

    size_t points = len/2;

    int i;
    for(int _ = 0; _ < DRAW_REPEATS; _++){

        for(i = 0; i < points; i++){
            mov(c[2*i] + x,c[2*i+1] + y);
            delayMicroseconds(2);
        }

        for(i = points-1; i >=0 ; i--){
            mov(c[2*i] + x,c[2*i+1] + y);
            delayMicroseconds(2);
        }
    }

    for(i = 0; i < points; i++){
        mov(c[2*i] + x,c[2*i+1] + y);
        delayMicroseconds(2);
    }
    delayMicroseconds(2);
}


void write_char(uint8_t x, uint8_t y, char c){
    CharacterData data;
    memcpy_P(&data, &characterDataArray[c], sizeof(CharacterData));

    uint8_t coords[data.length];
    memcpy_P(coords, &characterArray[data.offset], data.length);

    draw_char(x, y, coords, data.length);
}




// #define enable() DDRC &= B01111111
// #define disable() DDRC |= B10000000; PORTC &= B10000000

void setup(){
    DDRB = DDRB | B11111111;
    DDRD = DDRD | B11111100;
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
        delayMicroseconds(1);
        //delay(1);
    }

    for(uint8_t i = 255; i > 0; i--){
        //dac_write(sini(i));
        // dac_write(i);
        PORTD=i;
        PORTB=i;
        delayMicroseconds(1);
        //delay(1);
    }
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
    // sawtooth();
    //draw_char(80, 100, char_h, sizeof(char_h));
    //draw_char(140, 100, char_h, sizeof(char_h));
    //draw_char(200, 100, char_h, sizeof(char_h));
    // test();
    write_char(80, 100, 'H');
    write_char(140, 100, 'H');
    write_char(200, 100, 'H');
    //
}
