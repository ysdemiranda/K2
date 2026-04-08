#ifndef K2_API_SCHEDULE_HXX
#define K2_API_SCHEDULE_HXX

#include "kernel.hxx"

namespace K2
{
class Kernel::Schedule
{
    friend Kernel;

  private:
    struct _sched_t;
    _sched_t *_sched;
    Schedule(uint64_t);
    ~Schedule();

  public:
    /// @brief Loads a task into the kernel schedule
    /// @param taskptr pointer to task to load
    /// @return generated task ID or 0 if task could not be loaded
    uint64_t Load(Task *);

    /// @brief Number of task instances loaded in the kernel schedule
    /// @return Loaded task count
    uint64_t Count();

    /// @brief Maximum amount of tasks, eg. slot count
    /// @return Total slot count
    uint64_t Slots();
};
} // namespace K2

#endif