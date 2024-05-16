#include <avr/pgmspace.h>
#include <Arduino.h>
#include <pins_arduino.h>
// #include "fonts/processed/Sigi-7px-Regular.h"
#include "fonts/processed/pet.h"

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


#define mov(x, y) PORTD=(x); PORTB=(y)



// number of there and backs
#define DRAW_REPEATS 3



void draw_segment(uint8_t x, uint8_t y, uint8_t *c, size_t len){
    //mov(c[0] + x, c[0] + y);
    //delayMicroseconds(2);

    size_t points = len/2;

    int i;
    for(int _ = 0; _ < DRAW_REPEATS; _++){

        for(i = 0; i < points; i++){
            mov(c[2*i] + x,c[2*i+1] + y);
            delay_clock(5);
        }

        for(i = points-1; i >=0 ; i--){
            mov(c[2*i] + x,c[2*i+1] + y);
            delay_clock(5);
        }
    }

    for(i = 0; i < points-1; i++){
        mov(c[2*i] + x,c[2*i+1] + y);
        delay_clock(5);
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

void setup(){
    noInterrupts();
    DDRB = DDRB | B11111111;
    DDRD = DDRD | B11111111;
}

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

}
void test(){
    mov(110,110);
    delayMicroseconds(5);
    mov(115,120);
    delayMicroseconds(5);
    mov(120,110);
    delayMicroseconds(5);

}

void write(char *s, int len){
    uint16_t x = 0;
    uint16_t y = 0;
    for(int i = 0; i < len; i++){

        /*
        if(s[i] == ' '){
            x+= MAX_CHAR_WIDTH-1;
        }else 
        */
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
}

void loop(){
    // char *s = "MR COCONUT\nWAS HERE";
    char *s = " !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    write(s, strlen(s));
    return;
    uint16_t x = 0;
    uint16_t y = 0;
    uint16_t i = 0;
    while(y+CHAR_HEIGHT < 230){
        x += write_char(x, y, i+33) + 1;

        if(x + MAX_CHAR_WIDTH >= 255){
            x = 0;
            y += CHAR_HEIGHT + 1;
        }

        i++;
        i %= 63;
    }

}
