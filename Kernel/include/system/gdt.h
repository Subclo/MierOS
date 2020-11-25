#ifndef __MIEROS__KERNEL__SYSTEM__GDT_H
#define __MIEROS__KERNEL__SYSTEM__GDT_H
#include <common/types.h>

using namespace mieros::kernel;

namespace mieros::kernel::system {
    #define KERNEL_CODE_SEGMENT 0x08
    #define KERNEL_DATA_SEGMENT 0x10
    #define USER_CODE_SEGMENT 0x18
    #define USER_DATA_SEGMENT 0x20
    #define TASK_REGISTER_SEGMENT 0x28

    void init_gdt();

    void load_gdt();
}

#endif