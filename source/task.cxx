#include "../api/task.hxx"
#include "task.hxx"

namespace K2 {
    Kernel::Task::Task() {
        _task = new _task_t();
    }

    Kernel::Task::~Task() {
        delete(_task);
    }

    bool Kernel::Task::_task_t::awake() {
        return (state > NEW && state < SLEEP);
    }

    uint64_t Kernel::Task::GetID() {
        return _task->id;
    }

    bool Kernel::Task::IsActive() {
        return (_task->state == _task_t::RUN);
    }

    bool Kernel::Task::IsAlive() {
        return (_task->state > _task_t::NEW && _task->state < _task_t::END);
    }

    void Kernel::Task::DelayNanoseconds(uint64_t ns) {
        if(_task->awake()) {
            _task->state = _task_t::DELAY_T;
            _task->wait = ns;
        }
    }

    void Kernel::Task::DelayIterations(uint64_t i) {
        if(_task->awake()) {
            _task->state = _task_t::DELAY_C;
            _task->wait = i;
        }
    }

    void Kernel::Task::Sleep() {
        if(_task->awake()) {
            _task->state = _task_t::SLEEP;
        }
    }

    void Kernel::Task::Awake() {
        if(_task->state == _task_t::SLEEP) {
            _task->state = _task_t::RUN;
        }
    }

    void Kernel::Task::End() {
        if(_task->state < _task_t::END) {
            _task->state = _task_t::END;
        }
    }
}