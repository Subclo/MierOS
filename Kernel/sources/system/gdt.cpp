#include <system/gdt.h>
#include <common/print.h>

using namespace mieros::kernel::system;
using namespace mieros::kernel::common;

struct GDTEntry {
    uint16_t limit_0_15;
    uint16_t base_0_15;
    uint8_t base_16_23;
    uint8_t access;
    uint8_t limit_flags;
    uint8_t base_24_31;
}__attribute__((packed));

struct GDTR {
    uint16_t size;
    uint32_t offset;
}__attribute__((packed));

GDTEntry gdt[6];
GDTR gdtr;

void mieros::kernel::system::init_gdt() {
    //Null Descriptor
    gdt[0].limit_0_15 = 0;
    gdt[0].base_0_15 = 0;
    gdt[0].base_16_23 = 0;
    gdt[0].access = 0;
    gdt[0].limit_flags = 0;
    gdt[0].base_24_31 = 0;

    //Kernel Code Descriptor
    gdt[1].limit_0_15 = 0xFFFF;
    gdt[1].base_0_15 = 0;
    gdt[1].base_16_23 = 0;
    gdt[1].access = 0b10011010;
    gdt[1].limit_flags = 0b11001111;
    gdt[1].base_24_31 = 0;

    //Kernel Data Descriptor
    gdt[2].limit_0_15 = 0xFFFF;
    gdt[2].base_0_15 = 0;
    gdt[2].base_16_23 = 0;
    gdt[2].access = 0b10010010;
    gdt[2].limit_flags = 0b11001111;
    gdt[2].base_24_31 = 0;

    //User Code Descriptor
    gdt[3].limit_0_15 = 0xFFFF;
    gdt[3].base_0_15 = 0;
    gdt[3].base_16_23 = 0;
    gdt[3].access = 0b11111010;
    gdt[3].limit_flags = 0b11001111;
    gdt[3].base_24_31 = 0;

    //User Data Descriptor
    gdt[4].limit_0_15 = 0xFFFF;
    gdt[4].base_0_15 = 0;
    gdt[4].base_16_23 = 0;
    gdt[4].access = 0b11110010;
    gdt[4].limit_flags = 0b11001111;
    gdt[4].base_24_31 = 0;

    gdtr.offset = (uint32_t)&gdt;
    gdtr.size = sizeof(GDTEntry)*5;

    load_gdt();
}