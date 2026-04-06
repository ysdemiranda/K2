#ifndef K2_SCHEDULE_HXX
#define K2_SCHEDULE_HXX

#include "../api/kernel.hxx"
#include "../api/schedule.hxx"

#include "config.hxx"

namespace K2
{
    struct _slot_t
    {
        union {
            uint64_t state = 0;
            struct {
                unsigned OCCUPIED : 1;
                unsigned : 63;
            };
        };
        K2::Kernel::Task* task = nullptr;
    };
    
    struct Kernel::Schedule::_sched_t
    {
        _slot_t slots[K2_SCHEDULE_SLOTS];
        uint64_t occupied = 0;
        uint64_t idctr = 1;
        void run(uint64_t);
    };
} // namespace K2

#endif
