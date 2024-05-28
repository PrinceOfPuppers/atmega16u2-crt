#include "drawing.h"

#include <Arduino.h>
#include <avr/pgmspace.h>

// number of there and backs
#define DRAW_REPEATS 2


void setup_drawing(){
    DDRB = DDRB | 0b11111111;
    DDRD = DDRD | 0b11111111;
}

void draw_segment(uint8_t x, uint8_t y, uint8_t *c, size_t len){
    size_t points = len/2;

    int i;
    for(int _ = 0; _ < DRAW_REPEATS; _++){

        for(i = 0; i < points; i++){
            mov(c[2*i] + x,c[2*i+1] + y);
            delay_clock(2);
        }

        for(i = points-1; i >=0 ; i--){
            mov(c[2*i] + x,c[2*i+1] + y);
            delay_clock(2);
        }
    }

    for(i = 0; i < points-1; i++){
        mov(c[2*i] + x,c[2*i+1] + y);
        delay_clock(2);
    }
    mov(c[len - 2] + x,c[len - 1] + y);
}


// returns width
uint16_t write_char(uint8_t x, uint8_t y, char c){
    CharacterData data;
    memcpy_P(&data, &characterDataArray[c], sizeof(CharacterData));
    if(data.length == 0){
        return data.width;
    }

    mov(x + data.first_x, y + data.first_y);

    uint8_t coords[data.length];
    memcpy_P(coords, &characterArray[data.offsets[0]], data.length);

    for(int i = 0; i < data.segments; i++){
        draw_segment(x, y, coords + (data.offsets[i] - data.offsets[0]), data.lengths[i]);
    }
    return data.width;
}

void write(const char *s, int len){
    noInterrupts();
    uint16_t x = 0;
    uint16_t y = 0;
    for(int i = 0; i < len; i++){

        if(s[i] == '\n'){
            x = 0;
            y += CHAR_HEIGHT + 1;
        }
        else {
            x += write_char(x, y, s[i]) + 1;
        }

        if(x + MAX_CHAR_WIDTH >= 255){
            x = 0;
            y += CHAR_HEIGHT + 1;
        }
    }
    interrupts();
}
