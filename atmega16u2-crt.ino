#include "HID-Project.h"

#include "drawing.h"
#include <string.h>
#include <stdint.h>

#define LINE_SPACING 0
#define CHARACTER_SPACING 0
#define MAX_LINES (255/(CHAR_HEIGHT + LINE_SPACING))
#define MAX_LINE_LEN (255/(MAX_CHAR_WIDTH + CHARACTER_SPACING))

#define RAW_HID_BUFFER_SIZE 32
uint8_t rawhidData[RAW_HID_BUFFER_SIZE];

#define SCREEN_BUFFER_SIZE (128 + 32 + 16)
uint8_t screen_buffer[SCREEN_BUFFER_SIZE];
uint8_t screen_write_head = 0;

// reads oldest to newest
#define read_from_screen_buffer(v)  screen_buffer[(screen_write_head + v)%SCREEN_BUFFER_SIZE]

// iterates in reverse till \n or \0 returns len
uint8_t find_line_len(){
    for(uint8_t i = 1; i < SCREEN_BUFFER_SIZE; i++){
        uint8_t c = read_from_screen_buffer(-i);
        if(c == '\0' || c == '\n'){
            return i;
        }
    }
    return SCREEN_BUFFER_SIZE;
}

// should be large enough to hold the largest escape sequence we care about, all others will just be filtered
#define MAX_ESCAPE_SEQ 3

uint8_t num_newlines = 0;
int escape = -1;
uint8_t escape_buffer[MAX_ESCAPE_SEQ + 1] = {0}; // plus 1 is for nullbyte
static uint8_t line_len = 0;

// check escape_buffer
void process_escape_sequence(){
    // escape sequence was too large, we dont care about it
    if(escape >= sizeof(escape_buffer)){
        return;
    }
    escape_buffer[escape] = '\0';

    // strcmp isnt used to save dynamic memory
    // clear screen
    if(escape_buffer[0] == '[' && escape_buffer[1] == '2' && escape_buffer[2] == 'J' && escape_buffer[3] == '\0'){
        memset(screen_buffer, 0, SCREEN_BUFFER_SIZE);
        screen_write_head = 0;
        line_len = 0;
        num_newlines = 0;
        return;
    }

    // delete char
    if(escape_buffer[0] == '[' && escape_buffer[1] == 'K' && escape_buffer[2] == '\0'){
        if(screen_buffer[screen_write_head] == '\n'){
            num_newlines -= 1;
            line_len = find_line_len();
        }
        else{
            line_len-=1;
        }
        screen_buffer[screen_write_head] = '\0'; 
        return;
    }

    // move write head TODO: fix weird behavior with lines longer than MAX_LINE_LEN
    if(escape_buffer[0] == '[' && escape_buffer[1] == 'C' && escape_buffer[2] == '\0'){
        if(screen_write_head == SCREEN_BUFFER_SIZE - 1){
            screen_write_head = 0;
        }
        else {
            screen_write_head += 1;
        }
        return;
    }
    
}

void write_to_screen_buffer(char val){
    if(val == '\0' || val == '\a'){
        return;
    }
    if(escape >= 0){
        if(escape < MAX_ESCAPE_SEQ){
            escape_buffer[escape]  = val;
        }
        escape++;
        if(
            (val>64 && val<91)    ||  // val is capital letter
            (val>97 && val<123)       // val is lowercase letter
            ){
            process_escape_sequence();
            // end of escape sequence
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

        return;
    }

    if(val != '\n' && line_len >= MAX_LINE_LEN){
        return;
    }

    num_newlines += (val == '\n') - (screen_buffer[screen_write_head] == '\n');
    line_len = (val == '\n') ? 0 : line_len + 1;
    screen_buffer[screen_write_head] = val; 
    screen_write_head += 1; 
    screen_write_head %= SCREEN_BUFFER_SIZE;

    if(line_len > MAX_LINE_LEN){
        write_to_screen_buffer('\n');
    }
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
