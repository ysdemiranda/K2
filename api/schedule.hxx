#ifndef K2_API_SCHEDULE_HXX
#define K2_API_SCHEDULE_HXX

#include "kernel.hxx"

namespace K2 {
    class Kernel::Schedule {
        friend Kernel;
        private:
            struct _sched_t;
            _sched_t* _sched;
            Schedule();
            ~Schedule();
            
        public:
            /// @brief Loads a task into the kernel schedule
            /// @param taskptr pointer to task to load
            /// @return generated task ID or 0 if task could not be loaded
            uint64_t Load(Task*);

            /// @brief Forcibly removes a task from the schedule, does not guarantee a call to Clean()
            /// @param task_id ID of task to remove
            void Remove(uint64_t);

            /// @brief Finds pointer to task instance
            /// @param task_id ID of task to find
            /// @return a pointer to the Task instance referenced by given ID or nullptr if it is not loaded
            Task* Find(uint64_t);

            /// @brief Number of task instances loaded in the kernel schedule
            /// @return Loaded task count
            uint64_t Count();
    };
}

#endif