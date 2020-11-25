#ifndef __MIEROS__KERNEL__COMMON__PORT_H
#define __MIEROS__KERNEL__COMMON__PORT_H
#include <common/types.h>

namespace mieros::kernel::common {
    inline void outb(uint16_t addr, uint8_t data) { asm volatile("outb %0, %1" : : "a"(data), "d"(addr)); }
    inline void outw(uint16_t addr, uint16_t data) { asm volatile("outw %0, %1" : : "a"(data), "d"(addr)); }
    inline void outl(uint16_t addr, uint32_t data) { asm volatile("outl %0, %1" : : "a"(data), "d"(addr)); }
}

#endif