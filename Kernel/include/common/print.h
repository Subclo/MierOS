#ifndef __MIEROS__KERNEL__COMMON__PRINT_H
#define __MIEROS__KERNEL__COMMON__PRINT_H
#include <common/types.h>

namespace mieros::kernel::common {
    #define SCREEN_WIDTH 80
    #define SCREEN_HEIGHT 28

    void print(char c);
    void print(char* c);
    void print(uint32_t i);
    void print(int i);
    void print(void* ptr);

    void printHex(uint32_t i);
    void printHex(uint16_t i);
    void printHex(uint8_t i);
    void printHex(void* ptr);

    void clear();
}

#endif