#include <common/string.h>

void mieros::kernel::common::memcpy(const void* src, void* dst, size_t length) {
    uint8_t* _src = (uint8_t*)src;
    uint8_t* _dst = (uint8_t*)dst;
    for(int i = 0; i < length; i++) _dst[i] = _src[i];
}

void mieros::kernel::common::memset(void* dst, uint8_t val, size_t count) {
    uint8_t* _dst = (uint8_t*)dst;
    for(int i = 0; i < count; i++) _dst[i] = val;
}

void* mieros::kernel::common::memfind(const void* start, size_t range, const void* toFind, size_t lengthToFind) {
    uint8_t* _chunk = (uint8_t*)start;
    uint8_t* _toFind = (uint8_t*)toFind;
    void* foundPtr = 0;
    for(int i = 0; i < range; i++) {
        bool found = true;
        for(int j = 0; j < lengthToFind; j++) {
            if(_chunk[j+i] != _toFind[j]) {
                found = false;
                break;
            }
        }
        if(found) {
            foundPtr = _chunk+i;
            break;
        }
    }
    return foundPtr;
}