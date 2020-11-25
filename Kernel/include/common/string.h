#ifndef __MIEROS__KERNEL__COMMON__STRING_H
#define __MIEROS__KERNEL__COMMON__STRING_H
#include <common/types.h>

namespace mieros::kernel::common {
    void memcpy(const void* src, void* dst, size_t length);
    void memset(void* dst, uint8_t val, size_t count);
    void* memfind(const void* start, size_t range, const void* toFind, size_t lengthToFind);
}

#endif