#define CHAR_HEIGHT 18
#define MAX_CHAR_WIDTH 16
#define MAX_SEGMENTS 3

typedef struct CharacterData{
    uint8_t first_x;                  // first x value in offset list (allows for less beam oversaturation on prev char)
    uint8_t first_y;                  // first y ''
    uint8_t width;                  // full width of the character
    uint8_t length;                 // number of bytes for full char
    uint8_t segments;               // number of segments
    uint16_t offsets[MAX_SEGMENTS]; // offsets into characterArray for the start of each segment
    uint16_t lengths[MAX_SEGMENTS]; // number of bytes for segment
} CharacterData;

const CharacterData characterDataArray[] PROGMEM = {
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0} },
    { 0, 0, 16, 0, 0, {0, 0, 0}, {0, 0, 0} }, //  
    { 8, 12, 16, 10, 2, {0, 2, 10}, {2, 8, 0} }, // !
    { 4, 0, 16, 12, 2, {10, 16, 22}, {6, 6, 0} }, // "
    { 2, 4, 16, 74, 1, {22, 96, 96}, {74, 0, 0} }, // #
    { 4, 10, 16, 62, 1, {96, 158, 158}, {62, 0, 0} }, // $
    { 2, 12, 16, 32, 3, {158, 170, 180}, {12, 10, 10} }, // %
    { 12, 8, 16, 52, 1, {190, 242, 242}, {52, 0, 0} }, // &
    { 6, 4, 16, 6, 1, {242, 248, 248}, {6, 0, 0} }, // '
    { 10, 0, 16, 14, 1, {248, 262, 262}, {14, 0, 0} }, // (
    { 4, 0, 16, 14, 1, {262, 276, 276}, {14, 0, 0} }, // )
    { 4, 2, 16, 82, 1, {276, 358, 358}, {82, 0, 0} }, // *
    { 4, 6, 16, 26, 1, {358, 384, 384}, {26, 0, 0} }, // +
    { 6, 14, 16, 6, 1, {384, 390, 390}, {6, 0, 0} }, // ,
    { 2, 6, 16, 12, 1, {390, 402, 402}, {12, 0, 0} }, // -
    { 6, 10, 16, 10, 1, {402, 412, 412}, {10, 0, 0} }, // .
    { 2, 12, 16, 12, 1, {412, 424, 424}, {12, 0, 0} }, // /
    { 2, 2, 16, 78, 1, {424, 502, 502}, {78, 0, 0} }, // 0
    { 4, 4, 16, 46, 1, {502, 548, 548}, {46, 0, 0} }, // 1
    { 2, 2, 16, 36, 1, {548, 584, 584}, {36, 0, 0} }, // 2
    { 2, 2, 16, 38, 1, {584, 622, 622}, {38, 0, 0} }, // 3
    { 2, 8, 16, 52, 1, {622, 674, 674}, {52, 0, 0} }, // 4
    { 2, 10, 16, 36, 1, {674, 710, 710}, {36, 0, 0} }, // 5
    { 10, 0, 16, 38, 1, {710, 748, 748}, {38, 0, 0} }, // 6
    { 2, 2, 16, 26, 1, {748, 774, 774}, {26, 0, 0} }, // 7
    { 2, 2, 16, 58, 1, {774, 832, 832}, {58, 0, 0} }, // 8
    { 4, 12, 16, 38, 1, {832, 870, 870}, {38, 0, 0} }, // 9
    { 8, 4, 16, 4, 2, {870, 872, 874}, {2, 2, 0} }, // :
    { 8, 4, 16, 8, 2, {874, 876, 882}, {2, 6, 0} }, // ;
    { 2, 6, 16, 46, 1, {882, 928, 928}, {46, 0, 0} }, // <
    { 2, 4, 16, 24, 2, {928, 940, 952}, {12, 12, 0} }, // =
    { 2, 0, 16, 34, 1, {952, 986, 986}, {34, 0, 0} }, // >
    { 6, 12, 16, 22, 2, {986, 988, 1008}, {2, 20, 0} }, // ?
    { 12, 12, 16, 42, 1, {1008, 1050, 1050}, {42, 0, 0} }, // @
    { 2, 12, 16, 48, 1, {1050, 1098, 1098}, {48, 0, 0} }, // A
    { 2, 0, 16, 56, 1, {1098, 1154, 1154}, {56, 0, 0} }, // B
    { 12, 2, 16, 26, 1, {1154, 1180, 1180}, {26, 0, 0} }, // C
    { 2, 0, 16, 50, 1, {1180, 1230, 1230}, {50, 0, 0} }, // D
    { 8, 6, 16, 56, 1, {1230, 1286, 1286}, {56, 0, 0} }, // E
    { 2, 12, 16, 46, 1, {1286, 1332, 1332}, {46, 0, 0} }, // F
    { 8, 6, 16, 34, 1, {1332, 1366, 1366}, {34, 0, 0} }, // G
    { 2, 0, 16, 58, 1, {1366, 1424, 1424}, {58, 0, 0} }, // H
    { 6, 0, 16, 26, 1, {1424, 1450, 1450}, {26, 0, 0} }, // I
    { 2, 10, 16, 26, 1, {1450, 1476, 1476}, {26, 0, 0} }, // J
    { 2, 0, 16, 46, 1, {1476, 1522, 1522}, {46, 0, 0} }, // K
    { 2, 0, 16, 24, 1, {1522, 1546, 1546}, {24, 0, 0} }, // L
    { 2, 0, 16, 74, 1, {1546, 1620, 1620}, {74, 0, 0} }, // M
    { 2, 0, 16, 58, 1, {1620, 1678, 1678}, {58, 0, 0} }, // N
    { 2, 4, 16, 30, 1, {1678, 1708, 1708}, {30, 0, 0} }, // O
    { 2, 12, 16, 36, 1, {1708, 1744, 1744}, {36, 0, 0} }, // P
    { 8, 8, 16, 34, 1, {1744, 1778, 1778}, {34, 0, 0} }, // Q
    { 2, 12, 16, 48, 1, {1778, 1826, 1826}, {48, 0, 0} }, // R
    { 2, 10, 16, 36, 1, {1826, 1862, 1862}, {36, 0, 0} }, // S
    { 4, 0, 16, 26, 1, {1862, 1888, 1888}, {26, 0, 0} }, // T
    { 2, 0, 16, 32, 1, {1888, 1920, 1920}, {32, 0, 0} }, // U
    { 2, 0, 16, 36, 1, {1920, 1956, 1956}, {36, 0, 0} }, // V
    { 2, 0, 16, 78, 1, {1956, 2034, 2034}, {78, 0, 0} }, // W
    { 2, 0, 16, 42, 1, {2034, 2076, 2076}, {42, 0, 0} }, // X
    { 4, 0, 16, 32, 1, {2076, 2108, 2108}, {32, 0, 0} }, // Y
    { 2, 0, 16, 36, 1, {2108, 2144, 2144}, {36, 0, 0} }, // Z
    { 10, 0, 16, 26, 1, {2144, 2170, 2170}, {26, 0, 0} }, // [
    { 2, 2, 16, 12, 1, {2170, 2182, 2182}, {12, 0, 0} }, // backslash
    { 4, 0, 16, 26, 1, {2182, 2208, 2208}, {26, 0, 0} }, // ]
    { 0, 0, 0, 0, 0, {2208, 2208, 2208}, {0, 0, 0} },
    { 0, 14, 16, 16, 1, {2208, 2224, 2224}, {16, 0, 0} }, // _
    { 0, 0, 0, 0, 0, {2224, 2224, 2224}, {0, 0, 0} },
    { 4, 4, 16, 32, 1, {2224, 2256, 2256}, {32, 0, 0} }, // a
    { 2, 0, 16, 42, 1, {2256, 2298, 2298}, {42, 0, 0} }, // b
    { 12, 6, 16, 26, 1, {2298, 2324, 2324}, {26, 0, 0} }, // c
    { 12, 0, 16, 44, 1, {2324, 2368, 2368}, {44, 0, 0} }, // d
    { 10, 12, 16, 36, 1, {2368, 2404, 2404}, {36, 0, 0} }, // e
    { 2, 6, 16, 40, 1, {2404, 2444, 2444}, {40, 0, 0} }, // f
    { 4, 14, 16, 46, 1, {2444, 2490, 2490}, {46, 0, 0} }, // g
    { 2, 0, 16, 46, 1, {2490, 2536, 2536}, {46, 0, 0} }, // h
    { 8, 0, 16, 20, 2, {2536, 2538, 2556}, {2, 18, 0} }, // i
    { 10, 0, 16, 22, 2, {2556, 2558, 2578}, {2, 20, 0} }, // j
    { 2, 0, 16, 38, 1, {2578, 2616, 2616}, {38, 0, 0} }, // k
    { 6, 0, 16, 22, 1, {2616, 2638, 2638}, {22, 0, 0} }, // l
    { 2, 12, 16, 40, 1, {2638, 2678, 2678}, {40, 0, 0} }, // m
    { 2, 4, 16, 42, 1, {2678, 2720, 2720}, {42, 0, 0} }, // n
    { 2, 6, 16, 30, 1, {2720, 2750, 2750}, {30, 0, 0} }, // o
    { 2, 4, 16, 46, 1, {2750, 2796, 2796}, {46, 0, 0} }, // p
    { 12, 4, 16, 46, 1, {2796, 2842, 2842}, {46, 0, 0} }, // q
    { 2, 4, 16, 30, 1, {2842, 2872, 2872}, {30, 0, 0} }, // r
    { 2, 12, 16, 32, 1, {2872, 2904, 2904}, {32, 0, 0} }, // s
    { 2, 4, 16, 34, 1, {2904, 2938, 2938}, {34, 0, 0} }, // t
    { 2, 4, 16, 34, 1, {2938, 2972, 2972}, {34, 0, 0} }, // u
    { 2, 4, 16, 20, 1, {2972, 2992, 2992}, {20, 0, 0} }, // v
    { 2, 4, 16, 34, 1, {2992, 3026, 3026}, {34, 0, 0} }, // w
    { 2, 4, 16, 30, 1, {3026, 3056, 3056}, {30, 0, 0} }, // x
    { 2, 4, 16, 48, 1, {3056, 3104, 3104}, {48, 0, 0} }, // y
    { 2, 4, 16, 36, 1, {3104, 3140, 3140}, {36, 0, 0} }, // z
    { 0, 0, 0, 0, 0, {3140, 3140, 3140}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {3140, 3140, 3140}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {3140, 3140, 3140}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {3140, 3140, 3140}, {0, 0, 0} },
    { 0, 0, 0, 0, 0, {3140, 3140, 3140}, {0, 0, 0} }
};

const uint8_t characterArray[] PROGMEM = {
    8, 12, 8, 0, 8, 2, 8, 4, 8, 6, // ! 
    4, 0, 4, 2, 4, 4, 10, 0, 10, 2, 10, 4, // " 
    2, 4, 4, 4, 4, 2, 4, 0, 4, 2, 4, 4, 6, 4, 8, 4, 10, 4, 10, 2, 10, 0, 10, 2, 10, 4, 12, 4, 10, 4, 10, 6, 10, 8, 8, 8, 6, 8, 4, 8, 4, 6, 4, 4, 4, 6, 4, 8, 2, 8, 4, 8, 4, 10, 4, 12, 4, 10, 4, 8, 6, 8, 8, 8, 10, 8, 12, 8, 10, 8, 10, 10, 10, 12, // # 
    4, 10, 6, 10, 8, 10, 8, 8, 8, 6, 8, 4, 8, 2, 8, 0, 8, 2, 6, 2, 4, 4, 6, 6, 8, 6, 10, 6, 12, 8, 10, 10, 8, 10, 8, 12, 8, 10, 10, 10, 12, 8, 10, 6, 8, 6, 6, 6, 4, 4, 6, 2, 8, 4, 6, 2, 8, 2, 10, 2, 12, 2, // $ 
    2, 12, 4, 10, 6, 8, 8, 6, 10, 4, 12, 2, 2, 2, 4, 2, 4, 4, 2, 4, 2, 2, 10, 10, 12, 10, 12, 12, 10, 12, 10, 10, // % 
    12, 8, 10, 10, 8, 8, 6, 6, 4, 6, 2, 4, 2, 2, 4, 0, 6, 0, 8, 2, 8, 4, 6, 6, 8, 4, 8, 2, 6, 0, 4, 0, 2, 2, 2, 4, 4, 6, 2, 8, 2, 10, 4, 12, 6, 12, 8, 12, 10, 10, 12, 12, // & 
    6, 4, 8, 2, 10, 0, // ' 
    10, 0, 8, 2, 6, 4, 6, 6, 6, 8, 8, 10, 10, 12, // ( 
    4, 0, 6, 2, 8, 4, 8, 6, 8, 8, 6, 10, 4, 12, // ) 
    4, 2, 6, 4, 8, 4, 8, 2, 8, 0, 8, 2, 8, 4, 10, 4, 10, 6, 8, 6, 8, 4, 8, 6, 6, 6, 6, 4, 6, 6, 4, 6, 6, 6, 6, 8, 8, 8, 8, 6, 8, 8, 10, 8, 10, 6, 12, 6, 10, 6, 10, 8, 12, 10, 10, 8, 8, 8, 8, 10, 8, 12, 8, 10, 8, 8, 6, 8, 4, 10, 6, 8, 6, 6, 8, 6, 10, 6, 10, 4, 12, 2, // * 
    4, 6, 6, 6, 8, 6, 8, 4, 8, 2, 8, 4, 8, 6, 10, 6, 12, 6, 10, 6, 8, 6, 8, 8, 8, 10, // + 
    6, 14, 8, 12, 8, 10, // , 
    2, 6, 4, 6, 6, 6, 8, 6, 10, 6, 12, 6, // - 
    6, 10, 8, 10, 8, 12, 6, 12, 6, 10, // . 
    2, 12, 4, 10, 6, 8, 8, 6, 10, 4, 12, 2, // / 
    2, 2, 2, 4, 2, 6, 2, 8, 4, 8, 6, 6, 8, 6, 10, 4, 12, 4, 12, 2, 10, 0, 8, 0, 6, 0, 4, 0, 2, 2, 4, 0, 6, 0, 8, 0, 10, 0, 12, 2, 12, 4, 12, 6, 12, 8, 12, 10, 10, 12, 8, 12, 6, 12, 4, 12, 2, 10, 2, 8, 2, 10, 4, 12, 6, 12, 8, 12, 10, 12, 12, 10, 12, 8, 12, 6, 10, 4, // 0 
    4, 4, 6, 2, 8, 2, 8, 0, 8, 2, 8, 4, 8, 6, 8, 8, 8, 10, 8, 12, 6, 12, 4, 12, 6, 12, 8, 12, 10, 12, 12, 12, 10, 12, 8, 12, 8, 10, 8, 8, 8, 6, 8, 4, 6, 2, // 1 
    2, 2, 4, 0, 6, 0, 8, 0, 10, 0, 12, 2, 12, 4, 10, 6, 8, 6, 6, 8, 4, 8, 2, 10, 2, 12, 4, 12, 6, 12, 8, 12, 10, 12, 12, 12, // 2 
    2, 2, 4, 0, 6, 0, 8, 0, 10, 0, 12, 2, 12, 4, 10, 6, 8, 6, 6, 6, 8, 6, 10, 6, 12, 8, 12, 10, 10, 12, 8, 12, 6, 12, 4, 12, 2, 10, // 3 
    2, 8, 4, 8, 4, 6, 6, 4, 8, 2, 10, 2, 10, 0, 10, 2, 10, 4, 10, 6, 10, 8, 8, 8, 6, 8, 4, 8, 6, 8, 8, 8, 10, 8, 12, 8, 10, 8, 10, 10, 10, 12, 10, 10, 10, 8, 10, 6, 10, 4, 8, 2, // 4 
    2, 10, 4, 12, 6, 12, 8, 12, 10, 10, 12, 8, 10, 6, 8, 4, 6, 4, 4, 4, 2, 4, 2, 2, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, // 5 
    10, 0, 8, 0, 6, 0, 4, 2, 2, 4, 2, 6, 4, 6, 6, 6, 8, 6, 10, 6, 12, 8, 12, 10, 10, 12, 8, 12, 6, 12, 4, 12, 2, 10, 2, 8, 2, 6, // 6 
    2, 2, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 12, 2, 10, 4, 8, 6, 6, 8, 6, 10, 6, 12, // 7 
    2, 2, 2, 4, 4, 6, 6, 6, 8, 6, 10, 6, 12, 4, 12, 2, 10, 0, 8, 0, 6, 0, 4, 0, 2, 2, 4, 0, 6, 0, 8, 0, 10, 0, 12, 2, 12, 4, 10, 6, 12, 8, 12, 10, 10, 12, 8, 12, 6, 12, 4, 12, 2, 10, 2, 8, 4, 6, // 8 
    4, 12, 6, 12, 8, 12, 10, 10, 12, 8, 12, 6, 12, 4, 12, 2, 10, 0, 8, 0, 6, 0, 4, 0, 2, 2, 2, 4, 4, 6, 6, 6, 8, 6, 10, 6, 12, 6, // 9 
    8, 4, 8, 10, // : 
    8, 4, 6, 14, 8, 12, 8, 10, // ; 
    2, 6, 4, 6, 4, 4, 6, 4, 6, 2, 8, 2, 8, 0, 10, 0, 12, 0, 10, 0, 8, 0, 8, 2, 6, 2, 6, 4, 4, 4, 4, 6, 4, 8, 6, 8, 6, 10, 8, 10, 8, 12, 10, 12, 12, 12, // < 
    2, 4, 4, 4, 6, 4, 8, 4, 10, 4, 12, 4, 2, 8, 4, 8, 6, 8, 8, 8, 10, 8, 12, 8, // = 
    2, 0, 4, 0, 6, 0, 6, 2, 8, 2, 8, 4, 10, 4, 10, 6, 12, 6, 10, 6, 10, 8, 8, 8, 8, 10, 6, 10, 6, 12, 4, 12, 2, 12, // > 
    6, 12, 2, 2, 4, 0, 6, 0, 8, 0, 10, 0, 12, 2, 12, 4, 10, 6, 8, 6, 6, 8, // ? 
    12, 12, 10, 12, 8, 12, 6, 12, 4, 10, 2, 8, 2, 6, 2, 4, 4, 2, 6, 0, 8, 0, 10, 0, 12, 2, 12, 4, 12, 6, 10, 6, 10, 8, 8, 8, 6, 6, 8, 4, 10, 6, // @ 
    2, 12, 2, 10, 2, 8, 2, 6, 2, 4, 4, 2, 6, 0, 8, 0, 10, 2, 12, 4, 12, 6, 10, 6, 8, 6, 6, 6, 4, 6, 2, 6, 4, 6, 6, 6, 8, 6, 10, 6, 12, 6, 12, 8, 12, 10, 12, 12, // A 
    2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 2, 12, 4, 10, 6, 8, 6, 6, 6, 4, 6, 4, 4, 4, 2, 4, 0, 4, 2, 4, 4, 4, 6, 4, 8, 4, 10, 4, 12, 2, 12, 4, 12, 6, 12, 8, 12, 10, 12, 12, 10, 12, 8, 10, 6, // B 
    12, 2, 10, 0, 8, 0, 6, 0, 4, 2, 2, 4, 2, 6, 2, 8, 4, 10, 6, 12, 8, 12, 10, 12, 12, 10, // C 
    2, 0, 4, 0, 6, 0, 8, 0, 10, 2, 12, 4, 12, 6, 12, 8, 10, 10, 8, 12, 6, 12, 4, 12, 4, 10, 4, 8, 4, 6, 4, 4, 4, 2, 4, 0, 4, 2, 4, 4, 4, 6, 4, 8, 4, 10, 4, 12, 2, 12, // D 
    8, 6, 6, 6, 4, 6, 2, 6, 2, 4, 2, 2, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 10, 0, 8, 0, 6, 0, 4, 0, 2, 0, 2, 2, 2, 4, 2, 6, 2, 8, 2, 10, 2, 12, 4, 12, 6, 12, 8, 12, 10, 12, 12, 12, // E 
    2, 12, 2, 10, 2, 8, 2, 6, 2, 4, 2, 2, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 10, 0, 8, 0, 6, 0, 4, 0, 2, 0, 2, 2, 2, 4, 2, 6, 4, 6, 6, 6, 8, 6, // F 
    8, 6, 10, 6, 12, 6, 12, 8, 12, 10, 10, 12, 8, 12, 6, 12, 4, 10, 2, 8, 2, 6, 2, 4, 4, 2, 6, 0, 8, 0, 10, 0, 12, 2, // G 
    2, 0, 2, 2, 2, 4, 2, 6, 4, 6, 6, 6, 8, 6, 10, 6, 12, 6, 12, 4, 12, 2, 12, 0, 12, 2, 12, 4, 12, 6, 12, 8, 12, 10, 12, 12, 12, 10, 12, 8, 12, 6, 10, 6, 8, 6, 6, 6, 4, 6, 2, 6, 2, 8, 2, 10, 2, 12, // H 
    6, 0, 8, 0, 10, 0, 8, 0, 8, 2, 8, 4, 8, 6, 8, 8, 8, 10, 8, 12, 6, 12, 8, 12, 10, 12, // I 
    2, 10, 4, 12, 6, 12, 8, 12, 10, 10, 10, 8, 10, 6, 10, 4, 10, 2, 10, 0, 8, 0, 10, 0, 12, 0, // J 
    2, 0, 2, 2, 2, 4, 2, 6, 4, 6, 6, 6, 8, 4, 10, 2, 12, 0, 10, 2, 8, 4, 6, 6, 8, 8, 10, 10, 12, 12, 10, 10, 8, 8, 6, 6, 4, 6, 2, 6, 2, 8, 2, 10, 2, 12, // K 
    2, 0, 2, 2, 2, 4, 2, 6, 2, 8, 2, 10, 2, 12, 4, 12, 6, 12, 8, 12, 10, 12, 12, 12, // L 
    2, 0, 2, 2, 4, 2, 6, 4, 8, 4, 8, 6, 6, 6, 6, 4, 6, 6, 8, 6, 8, 4, 10, 2, 12, 2, 12, 0, 12, 2, 12, 4, 12, 6, 12, 8, 12, 10, 12, 12, 12, 10, 12, 8, 12, 6, 12, 4, 10, 2, 12, 4, 12, 2, 10, 2, 8, 4, 6, 4, 4, 2, 2, 2, 2, 4, 2, 6, 2, 8, 2, 10, 2, 12, // M 
    2, 0, 2, 2, 4, 2, 6, 4, 8, 6, 10, 8, 12, 8, 12, 6, 12, 4, 12, 2, 12, 0, 12, 2, 12, 4, 12, 6, 12, 8, 12, 10, 12, 12, 12, 10, 12, 8, 10, 8, 8, 6, 6, 4, 4, 2, 2, 2, 2, 4, 2, 6, 2, 8, 2, 10, 2, 12, // N 
    2, 4, 2, 6, 2, 8, 4, 10, 6, 12, 8, 12, 10, 10, 12, 8, 12, 6, 12, 4, 10, 2, 8, 0, 6, 0, 4, 2, 2, 4, // O 
    2, 12, 2, 10, 2, 8, 2, 6, 2, 4, 2, 2, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 2, 12, 4, 10, 6, 8, 6, 6, 6, 4, 6, 2, 6, // P 
    8, 8, 10, 10, 12, 8, 12, 6, 12, 4, 10, 2, 8, 0, 6, 0, 4, 2, 2, 4, 2, 6, 2, 8, 4, 10, 6, 12, 8, 12, 10, 10, 12, 12, // Q 
    2, 12, 2, 10, 2, 8, 2, 6, 2, 4, 2, 2, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 2, 12, 4, 10, 6, 8, 6, 6, 6, 4, 6, 2, 6, 4, 6, 6, 6, 8, 6, 8, 8, 10, 10, 12, 12, // R 
    2, 10, 4, 12, 6, 12, 8, 12, 10, 12, 12, 10, 12, 8, 10, 6, 8, 6, 6, 6, 4, 6, 2, 4, 2, 2, 4, 0, 6, 0, 8, 0, 10, 0, 12, 2, // S 
    4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 10, 0, 8, 0, 8, 2, 8, 4, 8, 6, 8, 8, 8, 10, 8, 12, // T 
    2, 0, 2, 2, 2, 4, 2, 6, 2, 8, 2, 10, 4, 12, 6, 12, 8, 12, 10, 12, 12, 10, 12, 8, 12, 6, 12, 4, 12, 2, 12, 0, // U 
    2, 0, 2, 2, 2, 4, 4, 6, 4, 8, 6, 10, 8, 10, 8, 12, 6, 12, 6, 10, 6, 12, 8, 12, 8, 10, 10, 8, 10, 6, 12, 4, 12, 2, 12, 0, // V 
    2, 0, 2, 2, 2, 4, 2, 6, 2, 8, 2, 10, 4, 10, 6, 8, 6, 6, 8, 6, 8, 8, 6, 8, 8, 8, 10, 10, 12, 10, 12, 8, 12, 6, 12, 4, 12, 2, 12, 0, 12, 2, 12, 4, 12, 6, 12, 8, 10, 10, 12, 12, 12, 10, 12, 12, 10, 10, 12, 8, 12, 10, 10, 10, 8, 8, 8, 6, 6, 6, 6, 8, 4, 10, 2, 12, 2, 10, // W 
    2, 0, 2, 2, 4, 4, 6, 6, 8, 6, 10, 4, 12, 2, 12, 0, 12, 2, 10, 4, 8, 6, 10, 8, 12, 10, 12, 12, 12, 10, 10, 8, 8, 6, 6, 6, 4, 8, 2, 10, 2, 12, // X 
    4, 0, 4, 2, 4, 4, 6, 6, 8, 6, 10, 6, 12, 4, 12, 2, 12, 0, 12, 2, 12, 4, 10, 6, 8, 6, 8, 8, 8, 10, 8, 12, // Y 
    2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 12, 2, 10, 4, 8, 6, 6, 6, 4, 8, 2, 10, 2, 12, 4, 12, 6, 12, 8, 12, 10, 12, 12, 12, // Z 
    10, 0, 8, 0, 6, 0, 4, 0, 4, 2, 4, 4, 4, 6, 4, 8, 4, 10, 4, 12, 6, 12, 8, 12, 10, 12, // [ 
    2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12, 12, // backslash 
    4, 0, 6, 0, 8, 0, 10, 0, 10, 2, 10, 4, 10, 6, 10, 8, 10, 10, 10, 12, 8, 12, 6, 12, 4, 12, // ] 
    0, 14, 2, 14, 4, 14, 6, 14, 8, 14, 10, 14, 12, 14, 14, 14, // _ 
    4, 4, 6, 4, 8, 4, 10, 6, 10, 8, 8, 8, 6, 8, 4, 8, 2, 10, 4, 12, 6, 12, 8, 12, 10, 10, 10, 8, 10, 10, 12, 12, // a 
    2, 0, 2, 2, 2, 4, 2, 6, 4, 6, 6, 4, 8, 4, 10, 4, 12, 6, 12, 8, 12, 10, 10, 12, 8, 12, 6, 12, 4, 10, 2, 10, 2, 8, 2, 6, 2, 8, 2, 10, 2, 12, // b 
    12, 6, 10, 4, 8, 4, 6, 4, 4, 4, 2, 6, 2, 8, 2, 10, 4, 12, 6, 12, 8, 12, 10, 12, 12, 10, // c 
    12, 0, 12, 2, 12, 4, 12, 6, 10, 6, 8, 4, 6, 4, 4, 4, 2, 6, 2, 8, 2, 10, 4, 12, 6, 12, 8, 12, 10, 10, 12, 10, 12, 8, 12, 6, 12, 8, 12, 10, 12, 12, 10, 10, // d 
    10, 12, 8, 12, 6, 12, 4, 12, 2, 10, 2, 8, 2, 6, 4, 4, 6, 4, 8, 4, 10, 4, 12, 6, 12, 8, 10, 8, 8, 8, 6, 8, 4, 8, 2, 8, // e 
    2, 6, 4, 6, 6, 6, 6, 4, 6, 2, 8, 0, 10, 0, 12, 2, 10, 0, 8, 0, 6, 2, 6, 4, 6, 6, 8, 6, 10, 6, 8, 6, 6, 6, 6, 8, 6, 10, 6, 12, // f 
    4, 14, 6, 14, 8, 14, 10, 14, 12, 12, 12, 10, 12, 8, 12, 6, 12, 4, 12, 6, 10, 6, 10, 8, 12, 8, 10, 8, 8, 10, 6, 10, 4, 10, 2, 8, 2, 6, 4, 4, 6, 4, 8, 4, 10, 6, // g 
    2, 0, 2, 2, 2, 4, 2, 6, 4, 6, 6, 4, 8, 4, 10, 4, 12, 6, 12, 8, 12, 10, 12, 12, 12, 10, 12, 8, 12, 6, 10, 4, 8, 4, 6, 4, 4, 6, 2, 6, 2, 8, 2, 10, 2, 12, // h 
    8, 0, 6, 4, 8, 4, 8, 6, 8, 8, 8, 10, 8, 12, 6, 12, 8, 12, 10, 12, // i 
    10, 0, 2, 12, 4, 14, 6, 14, 8, 14, 10, 12, 10, 10, 10, 8, 10, 6, 10, 4, 8, 4, // j 
    2, 0, 2, 2, 2, 4, 2, 6, 2, 8, 2, 10, 4, 10, 6, 8, 8, 6, 10, 4, 8, 6, 6, 8, 8, 10, 10, 12, 8, 10, 6, 8, 4, 10, 2, 10, 2, 12, // k 
    6, 0, 8, 0, 8, 2, 8, 4, 8, 6, 8, 8, 8, 10, 8, 12, 6, 12, 8, 12, 10, 12, // l 
    2, 12, 2, 10, 2, 8, 2, 6, 2, 4, 4, 4, 6, 4, 8, 6, 8, 8, 8, 10, 8, 12, 8, 10, 8, 8, 8, 6, 10, 4, 12, 4, 14, 6, 14, 8, 14, 10, 14, 12, // m 
    2, 4, 2, 6, 4, 6, 6, 4, 8, 4, 10, 4, 12, 6, 12, 8, 12, 10, 12, 12, 12, 10, 12, 8, 12, 6, 10, 4, 8, 4, 6, 4, 4, 6, 2, 6, 2, 8, 2, 10, 2, 12, // n 
    2, 6, 2, 8, 2, 10, 4, 12, 6, 12, 8, 12, 10, 12, 12, 10, 12, 8, 12, 6, 10, 4, 8, 4, 6, 4, 4, 4, 2, 6, // o 
    2, 4, 2, 6, 4, 6, 4, 8, 2, 8, 2, 6, 2, 8, 2, 10, 2, 12, 2, 14, 2, 12, 2, 10, 2, 8, 4, 8, 6, 10, 8, 10, 10, 10, 12, 8, 12, 6, 10, 4, 8, 4, 6, 4, 4, 6, // p 
    12, 4, 12, 6, 10, 6, 10, 8, 12, 8, 12, 6, 12, 8, 12, 10, 12, 12, 12, 14, 12, 12, 12, 10, 12, 8, 10, 8, 8, 10, 6, 10, 4, 10, 2, 8, 2, 6, 4, 4, 6, 4, 8, 4, 10, 6, // q 
    2, 4, 2, 6, 4, 6, 6, 4, 8, 4, 10, 4, 12, 6, 10, 4, 8, 4, 6, 4, 4, 6, 2, 6, 2, 8, 2, 10, 2, 12, // r 
    2, 12, 4, 12, 6, 12, 8, 12, 10, 12, 12, 10, 10, 8, 8, 8, 6, 8, 4, 8, 2, 6, 4, 4, 6, 4, 8, 4, 10, 4, 12, 4, // s 
    2, 4, 4, 4, 6, 4, 6, 2, 6, 0, 6, 2, 6, 4, 8, 4, 10, 4, 8, 4, 6, 4, 6, 6, 6, 8, 6, 10, 8, 12, 10, 12, 12, 10, // t 
    2, 4, 2, 6, 2, 8, 2, 10, 4, 12, 6, 12, 8, 12, 10, 10, 12, 10, 12, 8, 12, 6, 12, 4, 12, 6, 12, 8, 12, 10, 12, 12, 10, 10, // u 
    2, 4, 2, 6, 2, 8, 4, 10, 6, 12, 8, 12, 10, 10, 12, 8, 12, 6, 12, 4, // v 
    2, 4, 2, 6, 2, 8, 2, 10, 4, 12, 6, 12, 8, 10, 8, 8, 8, 6, 8, 8, 8, 10, 10, 12, 12, 12, 14, 10, 14, 8, 14, 6, 14, 4, // w 
    2, 4, 4, 6, 6, 8, 8, 8, 10, 6, 12, 4, 10, 6, 8, 8, 10, 10, 12, 12, 10, 10, 8, 8, 6, 8, 4, 10, 2, 12, // x 
    2, 4, 2, 6, 2, 8, 4, 10, 6, 10, 8, 10, 10, 8, 12, 8, 12, 6, 12, 4, 12, 6, 12, 8, 12, 10, 12, 12, 10, 14, 8, 14, 6, 14, 4, 14, 6, 14, 8, 14, 10, 14, 12, 12, 12, 10, 10, 8, // y 
    2, 4, 4, 4, 6, 4, 8, 4, 10, 4, 12, 4, 10, 4, 10, 6, 8, 8, 6, 8, 4, 10, 4, 12, 2, 12, 4, 12, 6, 12, 8, 12, 10, 12, 12, 12, // z 
};