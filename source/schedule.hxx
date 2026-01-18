#ifndef K2_SCHEDULE_HXX
#define K2_SCHEDULE_UXX

#include "../api/kernel.hxx"
#include "../api/schedule.hxx"

#include <list>
#include <map>

namespace K2
{
struct Kernel::Schedule::_sched_t
{
    std::map<uint64_t, Kernel::Task *> tasks;
    std::list<uint64_t> trash;
    std::list<Kernel::Task *> fresh;
    uint64_t idctr = 1;
    bool run(uint64_t);
};
} // namespace K2

#endif