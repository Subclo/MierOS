#include <common/types.h>
#include <common/print.h>
#include <system/gdt.h>
#include <common/string.h>

using namespace mieros::kernel::common;
using namespace mieros::kernel::system;

extern "C" void kmain(uint32_t multiboot_struct, uint32_t magic) {
    print("MierOS -- made by Patryk\n");

    init_gdt();

    char* rsdpID = "RSD PTR ";
    void* ptr = memfind((void*)0x80000, 0x20000, rsdpID, 8);
    if(ptr == 0) ptr = memfind((void*)0xE0000, 0x20000, rsdpID, 8);
    printHex(ptr);

    while(true) {
        asm volatile("hlt");
    }
}