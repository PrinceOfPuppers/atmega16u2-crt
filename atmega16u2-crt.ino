#include "drawing.h"
#include "string.h"

//uint8_t rawhidData[CHUNK_BYTE_SIZE];

void setup(){
    setup_drawing();
}


void loop(){
    const char *s = " !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    write(s, strlen(s));
    return;
}
