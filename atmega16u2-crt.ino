#include "HID-Project.h"
#include "fonts/processed/pet.h"

#include "drawing.h"
#include <string.h>
#include <stdint.h>


#define LINE_SPACING 1
#define CHARACTER_SPACING 0
#define MAX_LINES (255/(CHAR_HEIGHT + LINE_SPACING))

#define RAW_HID_BUFFER_SIZE 16
uint8_t rawhidData[RAW_HID_BUFFER_SIZE];


#define SCREEN_BUFFER_SIZE 128
uint8_t screen_buffer[SCREEN_BUFFER_SIZE];
uint8_t screen_write_head = 0;

// reads oldest to newest
#define read_from_screen_buffer(v)  screen_buffer[(screen_write_head + v)%SCREEN_BUFFER_SIZE]

uint8_t num_newlines = 0;
void write_to_screen_buffer(char val){
    num_newlines += (val == '\n') - (screen_buffer[screen_write_head] == '\n');
    screen_buffer[screen_write_head] = val; 
    screen_write_head += 1; 
    screen_write_head %= SCREEN_BUFFER_SIZE;
}

void setup(){
    RawHID.begin(rawhidData, sizeof(rawhidData));
    setup_drawing();
}


void write_to_screen(){
    noInterrupts();
    uint16_t x = 0;
    uint16_t y = 0;
    uint8_t line = 0; 
    for(int i = 0; i < SCREEN_BUFFER_SIZE; i++){
        //char c = read_from_screen_buffer(i);
        char c = read_from_screen_buffer(i);

        // ignore lines off screen
        if(num_newlines - line > MAX_LINES-1){
            if(c == '\n'){
                line+=1;
            }
            continue;
        }
        if(c == '\n'){
            x = 0;
            y += CHAR_HEIGHT + LINE_SPACING;
            continue;
        }

        if(x + MAX_CHAR_WIDTH > 255){
            continue;
        }

        x += write_char(x, y, c) + CHARACTER_SPACING;

    }
    write_char(x, y, '_');
    interrupts();
}

void loop(){
    int bytesAvailable = RawHID.available();
    while(bytesAvailable){
        write_to_screen_buffer(RawHID.read());
        bytesAvailable--;
    }
    write_to_screen();

    return;
}
