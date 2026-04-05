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

bool Kernel::Schedule::_sched_t::run(uint64_t cdelta)
{
    std::list<uint64_t> trash;

    for (auto it : tasks)
    {
        Task *t = it.second;
        if (t != nullptr && t->_task->id)
        {
            t->_task->delta += cdelta;

            switch (t->_task->state)
            {
            case Task::_task_t::NEW:
                t->_task->state = Task::_task_t::RUN;
                t->Initialize();
                break;
            case Task::_task_t::RUN:
                t->Payload();
                t->_task->delta = 0;
                break;
            case Task::_task_t::DELAY_T:
                t->_task->wait -= _min(cdelta, t->_task->wait);
                if (!t->_task->wait)
                {
                    t->_task->state = Task::_task_t::RUN;
                }
                break;
            case Task::_task_t::DELAY_C:
                t->_task->wait -= _min(1, t->_task->wait);
                if (!t->_task->wait)
                {
                    t->_task->state = Task::_task_t::RUN;
                }
                break;
            case Task::_task_t::SLEEP:
                break;
            case Task::_task_t::END:
                t->Clean();
                t->_task->id = 0;
                t->_task->delta = 0;
                t->_task->wait = 0;
                t->_task->state = Task::_task_t::NEW;
                trash.push_back(it.first);
                break;
            default:
                break;
            }
        }
    }

    for (auto it : trash)
    {
        tasks.erase(it);
    }
    trash.clear();

    for (auto it : fresh)
    {
        tasks[it->GetID()] = it;
    }
    fresh.clear();

    return true;
}

uint64_t Kernel::Schedule::Load(Task *t)
{
    if (t == nullptr || t->_task->id)
        return 0;
    uint64_t new_id = _sched->idctr++;
    t->_task->id = new_id;
    _sched->fresh.push_back(t);
    return new_id;
}

uint64_t Kernel::Schedule::Count()
{
    return _sched->tasks.size() + _sched->fresh.size();
}

} // namespace K2
