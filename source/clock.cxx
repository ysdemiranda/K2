#include "clock.hxx"

namespace K2 {
    Kernel::Clock::Clock(uint64_t (*time_fnptr)()) {
        _clock = new _clock_t();
        _clock->boot = time_fnptr();
        _clock->real = time_fnptr;
    }

    Kernel::Clock::~Clock() {
        delete(_clock);
    }

    bool Kernel::Clock::_clock_t::tick() {
        if(real() <= cycle) return false;
        uint64_t last = cycle;
        cycle = real();
        delta = cycle - last;
        uptime += delta;
        iter++;
        return true;
    }

    uint64_t Kernel::Clock::CurrentTime() {
        return _clock->real();
    }

    uint64_t Kernel::Clock::BootTime() {
        return _clock->boot;
    }

    uint64_t Kernel::Clock::CycleTime() {
        return _clock->cycle;
    }

    uint64_t Kernel::Clock::Uptime() {
        return _clock->uptime;
    }

    uint64_t Kernel::Clock::Iteration() {
        return _clock->iter;
    }

    uint64_t Kernel::Clock::DeltaTime() {
        return _clock->delta;
    }
}