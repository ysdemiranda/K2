#include "schedule.hxx"
#include "task.hxx"

inline static uint64_t _min(uint64_t a, uint64_t b)
{
    return (a < b ? a : b);
}

namespace K2
{
Kernel::Schedule::Schedule()
{
    _sched = new _sched_t();
}

Kernel::Schedule::~Schedule()
{
    delete (_sched);
}

void Kernel::Schedule::_sched_t::run(uint64_t cdelta)
{
    if( !occupied ) return;
    for (uint64_t i = 0; i < K2_SCHEDULE_SLOTS; i++)
    {
        _slot_t* slot = slots + i;
        if( !slot->OCCUPIED || slot->task == nullptr) continue;

        Task::_task_t* t = slot->task->_task;
        t->delta += cdelta;

        switch(t->state)
        {
            case Task::_task_t::NEW:
                t->state = Task::_task_t::RUN;
                slot->task->Initialize();
                break;
            case Task::_task_t::RUN:
                slot->task->Payload();
                slot->task->_task->delta = 0;
                break;
            case Task::_task_t::DELAY_T:
                t->wait -= _min(cdelta, t->wait);
                if (!t->wait)
                {
                    t->state = Task::_task_t::RUN;
                }
                break;
            case Task::_task_t::DELAY_C:
                t->wait -= _min(1, t->wait);
                if (!t->wait)
                {
                    t->state = Task::_task_t::RUN;
                }
                break;
            case Task::_task_t::SLEEP:
                break;
            case Task::_task_t::END:
                slot->task->Clean();
                t->id = 0;
                t->delta = 0;
                t->wait = 0;
                t->state = Task::_task_t::NEW;
                slot->OCCUPIED = 0;
                slot->task = nullptr;
                occupied--;
                break;
            default:
                break;
        }
    }
}

uint64_t Kernel::Schedule::Load(Task *t)
{
    if (t == nullptr || t->_task->id)
        return 0;

    if (_sched->occupied == K2_SCHEDULE_SLOTS)
        return 0;

    uint64_t new_id = _sched->idctr++;
    t->_task->id = new_id;

    for(uint64_t i = 0; i < K2_SCHEDULE_SLOTS; i++)
    {
        _slot_t* slot = _sched->slots + i;
        slot->OCCUPIED = 1;
        slot->task = t;
        _sched->occupied++;
        break;
    }

    return new_id;

}

uint64_t Kernel::Schedule::Count()
{
    return _sched->occupied;
}

uint64_t Kernel::Schedule::Slots()
{
    return K2_SCHEDULE_SLOTS;
}

} // namespace K2
