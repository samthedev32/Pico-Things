#define MORSE_LEN_DOT 1  // The length of a dot
#define MORSE_LEN_DASH 3 // The length of a dash

#define MORSE_LEN_PARTS 1  // The space between parts of the same letter
#define MORSE_LEN_LETTER 2 // The space between letters
#define MORSE_LEN_WORD 4   // The space between words

#define MORSE_LEN_MS 100 // The length of one unit (in ms)

const char *morse_letters[] = {
    ".-",   // A
    "-...", // B
    "-.-.", // C
    "-..",  // D
    ".",    // E
    "..-.", // F
    "--.",  // G
    "....", // H
    "..",   // I
    ".---", // J
    "-.-",  // K
    ".-..", // L
    "--",   // M
    "-.",   // N
    "---",  // O
    ".--.", // P
    "--.-", // Q
    ".-.",  // R
    "...",  // S
    "-",    // T
    "..-",  // U
    "...-", // V
    ".--",  // W
    "-..-", // X
    "-.--", // Y
    "--.."  // Z
};

const char *morse_numbers[] = {
    "-----", // 0
    ".----", // 1
    "..---", // 2
    "...--", // 3
    "....-", // 4
    ".....", // 5
    "-....", // 6
    "--...", // 7
    "---..", // 8
    "----."  // 9
};