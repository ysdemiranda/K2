#include "../api/kernel.hxx"
#include "../api/clock.hxx"
#include "../api/schedule.hxx"

#include "clock.hxx"
#include "kernel.hxx"
#include "schedule.hxx"

namespace K2
{

Kernel::Kernel(uint64_t (*time_fnptr)(), uint64_t slots)
{
    _kernel = new _kernel_t();
    _kernel->clock = new Clock(time_fnptr);
    _kernel->schedule = new Schedule(slots);
}

Kernel::~Kernel()
{
    delete (_kernel->clock);
    delete (_kernel->schedule);
    delete (_kernel);
}

Kernel::Clock *Kernel::GetClock()
{
    return _kernel->clock;
}

Kernel::Schedule *Kernel::GetSchedule()
{
    return _kernel->schedule;
}

void Kernel::Cycle()
{
    _kernel->clock->_clock->tick();
    _kernel->schedule->_sched->run(_kernel->clock->_clock->delta, _kernel->clock->_clock->cycle);
}
} // namespace K2