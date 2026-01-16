#ifndef K2_SCHEDULE_HXX
#define K2_SCHEDULE_UXX

#include "../api/kernel.hxx"
#include "../api/schedule.hxx"

#include <map>
#include <list>

namespace K2 {
    struct Kernel::Schedule::_sched_t {
        std::map<uint64_t, Kernel::Task*> tasks;
        std::list<uint64_t> trash;
        uint64_t idctr = 1;
        bool run(uint64_t);
    };
}

#endif