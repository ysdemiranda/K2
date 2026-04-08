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
    _kstruct = new _kstruct_t();
    _kstruct->clock = new Clock(time_fnptr);
    _kstruct->schedule = new Schedule(slots);
}

Kernel::~Kernel()
{
    delete (_kstruct->clock);
    delete (_kstruct->schedule);
    delete (_kstruct);
}

Kernel::Clock *Kernel::GetClock()
{
    return _kstruct->clock;
}

Kernel::Schedule *Kernel::GetSchedule()
{
    return _kstruct->schedule;
}

void Kernel::Cycle()
{
    _kstruct->clock->_clock->tick();
    _kstruct->schedule->_sched->run(_kstruct->clock->_clock->delta, _kstruct->clock->_clock->cycle);
}
} // namespace K2