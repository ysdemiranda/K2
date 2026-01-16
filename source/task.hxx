#ifndef K2_TASK_HXX
#define K2_TASK_HXX

#include "../api/task.hxx"

namespace K2 {
    struct Kernel::Task::_task_t {
        enum : uint8_t {
            NEW, RUN, DELAY_T, DELAY_C, SLEEP, END
        } state = NEW;

        uint64_t id = 0;
        uint64_t wait = 0;

        bool awake();
    };
}

#endif