#ifndef K2_SCHEDULE_HXX
#define K2_SCHEDULE_HXX

#include "../api/kernel.hxx"
#include "../api/schedule.hxx"

namespace K2
{
struct _slot_t;

struct Kernel::Schedule::_sched_t
{
    _slot_t *slots = nullptr;
    uint32_t num_slots = 0;
    uint32_t occupied = 0;
    uint64_t idctr = 1;
    void run(uint64_t, uint64_t);
};
} // namespace K2

#endif
