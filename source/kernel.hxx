#ifndef K2_KERNEL_HXX
#define K2_KERNEL_HXX

#include "../api/kernel.hxx"

namespace K2 {
    struct Kernel::_kstruct_t {
        Clock* clock;
        Schedule* schedule;
    };
}

#endif