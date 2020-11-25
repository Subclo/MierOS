#include <common/print.h>
#include <common/port.h>

using namespace mieros::kernel::common;

uint16_t* VGA_MEM = (uint16_t*)0xb8000;

uint16_t cursorOffset;

void updateCursorPos() {
    outb(0x3D4, 0x0F);
    outb(0x3D5, cursorOffset & 0xFF);
    outb(0x3D4, 0x0E);
    outb(0x3D5, (cursorOffset >> 8) & 0xFF);
}

void mieros::kernel::common::print(char c) {
    VGA_MEM[cursorOffset] = 0x0700 | c;
    cursorOffset++;
    updateCursorPos();
}

void mieros::kernel::common::print(char* c) {
    int i = 0;
    while(c[i] != 0) {
        if(c[i] == '\n') {
            cursorOffset = cursorOffset - (cursorOffset % SCREEN_WIDTH) + SCREEN_WIDTH;
            i++;
            continue;
        }
        VGA_MEM[cursorOffset] = 0x0700 | c[i];
        cursorOffset++;
        i++;
    }
    updateCursorPos();
}

void mieros::kernel::common::print(int n) {
    char buffer[50];
    int i = 0;

    bool isNeg = n<0;

    unsigned int n1 = isNeg ? -n : n;

    while(n1!=0)
    {
        buffer[i++] = n1%10+'0';
        n1=n1/10;
    }

    if(isNeg)
        buffer[i++] = '-';

    buffer[i] = '\0';

    for(int t = 0; t < i/2; t++)
    {
        buffer[t] ^= buffer[i-t-1];
        buffer[i-t-1] ^= buffer[t];
        buffer[t] ^= buffer[i-t-1];
    }

    if(n == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
    }

    mieros::kernel::common::print(buffer);
}

void mieros::kernel::common::print(uint32_t n) {
    char buffer[50];
    int i = 0;

    while(n!=0) {
        buffer[i++] = n%10+'0';
        n=n/10;
    }

    buffer[i] = '\0';

    for(int t = 0; t < i/2; t++) {
        buffer[t] ^= buffer[i-t-1];
        buffer[i-t-1] ^= buffer[t];
        buffer[t] ^= buffer[i-t-1];
    }

    if(n == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
    }

    mieros::kernel::common::print(buffer);
}

void mieros::kernel::common::print(void* ptr) {
    mieros::kernel::common::print((uint32_t)ptr);
}

char* hexLookup = "0123456789ABCDEF";
void printHexChar(uint8_t half) {
    char c = hexLookup[half & 0x0F];
    VGA_MEM[cursorOffset] = 0x0700 | c;
    cursorOffset++;
}

void mieros::kernel::common::printHex(void* ptr) {
    mieros::kernel::common::printHex((uint32_t)ptr);
}

void mieros::kernel::common::printHex(uint32_t i) {
    printHexChar(i >> 28);
    printHexChar(i >> 24);
    printHexChar(i >> 20);
    printHexChar(i >> 16);
    printHexChar(i >> 12);
    printHexChar(i >> 8);
    printHexChar(i >> 4);
    printHexChar(i >> 0);
    updateCursorPos();
}
void mieros::kernel::common::printHex(uint16_t i) {
    printHexChar(i >> 12);
    printHexChar(i >> 8);
    printHexChar(i >> 4);
    printHexChar(i >> 0);
    updateCursorPos();
}
void mieros::kernel::common::printHex(uint8_t i) {
    printHexChar(i >> 4);
    printHexChar(i >> 0);
    updateCursorPos();
}

void mieros::kernel::common::clear() {
    for(int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++) {
        VGA_MEM[i] = 0x0700;
    }
}