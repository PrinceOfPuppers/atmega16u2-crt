#include "HID-Project.h"

#include "drawing.h"
#include <string.h>
#include <stdint.h>


#define LINE_SPACING 0
#define CHARACTER_SPACING 0
#define MAX_LINES (255/(CHAR_HEIGHT + LINE_SPACING))

#define RAW_HID_BUFFER_SIZE 32
uint8_t rawhidData[RAW_HID_BUFFER_SIZE];


#define SCREEN_BUFFER_SIZE (128 + 32 + 16)
uint8_t screen_buffer[SCREEN_BUFFER_SIZE];
uint8_t screen_write_head = 0;

// reads oldest to newest
#define read_from_screen_buffer(v)  screen_buffer[(screen_write_head + v)%SCREEN_BUFFER_SIZE]

uint8_t num_newlines = 0;
#define ESCAPE_MAX_LEN 20
int escape = -1;
void write_to_screen_buffer(char val){
    if(val == '\0'){
        return;
    }
    if(escape >= 0){
        escape++;
        if(
            escape>ESCAPE_MAX_LEN ||  // error recovery
            (val>64 && val<91)    ||  // val is capital letter
            (val>97 && val<123)       // val is lowercase letter
            ){
            escape = -1;
        }

        return;
    }
    if(val == 0x1B){
        escape = 0;
        return;
    }

    if(val == '\b'){
        if(screen_write_head == 0){
            screen_write_head = SCREEN_BUFFER_SIZE -1;
        }
        else {
            screen_write_head -= 1;
        }

        //screen_write_head = screen_write_head == 0 ? SCREEN_BUFFER_SIZE - 1 : screen_write_head - 1;
        //screen_write_head -= 1;
        num_newlines -= screen_buffer[screen_write_head] == '\n';
        screen_buffer[screen_write_head] = '\0'; 
        return;
    }

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
    for(uint8_t i = 0; i < SCREEN_BUFFER_SIZE; i++){
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
