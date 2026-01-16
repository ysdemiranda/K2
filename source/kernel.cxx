#include "../api/kernel.hxx"
#include "../api/clock.hxx"
#include "../api/schedule.hxx"

#include "kernel.hxx"
#include "clock.hxx"
#include "schedule.hxx"

namespace K2 {

    Kernel::Kernel(uint64_t (*time_fnptr)()) {
        _kstruct = new _kstruct_t();
        _kstruct->clock = new Clock(time_fnptr);
        _kstruct->schedule = new Schedule();
    }

    Kernel::~Kernel() {
        delete(_kstruct->clock);
        delete(_kstruct->schedule);
        delete(_kstruct);
    }

    Kernel::Clock* Kernel::GetClock() {
        return _kstruct->clock;
    }

    Kernel::Schedule* Kernel::GetSchedule() {
        return _kstruct->schedule;
    }

    void Kernel::Cycle() {
        _kstruct->clock->_clock->tick();
        _kstruct->schedule->_sched->run(
            _kstruct->clock->_clock->delta
        );
    }
}