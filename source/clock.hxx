#ifndef K2_CLOCK_HXX
#define K2_CLOCK_HXX

#include "../api/clock.hxx"

namespace K2 {   
    struct Kernel::Clock::_clock_t {
        uint64_t (*real)();
        uint64_t boot = 0;
        uint64_t cycle = 0;
        uint64_t uptime = 0;
        uint64_t iter = 0;
        uint64_t delta = 0;

        bool tick();
    };
}

#endif