#pragma once
#include <iostream>

uintptr_t string2Offset(const char* c) {
    int base = 16;
    static_assert(sizeof(uintptr_t) == sizeof(unsigned long)
        || sizeof(uintptr_t) == sizeof(unsigned long long),
        "Please add string to handle conversion for this architecture.");

    // Now choose the correct function ...
    if (sizeof(uintptr_t) == sizeof(unsigned long)) {
        return strtoul(c, nullptr, base);
    }

    // All other options exhausted, sizeof(uintptr_t) == sizeof(unsigned long long))
    return strtoull(c, nullptr, base);
}