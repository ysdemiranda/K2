#ifndef K2_API_TASK_HXX
#define K2_API_TASK_HXX

#include "kernel.hxx"

namespace K2 {
    class Kernel::Task {
        friend Schedule;
        public:
            /// @brief Constructor for the Task class. \
            /// @brief Do not override, instead put subclass construction in the Initialize() override
            Task();

            /// @brief Task destructor. \
            /// @brief Do not override, instead put subclass destruction in the Clean() override
            ~Task();

        private:
            /// @brief Internal task structure
            struct _task_t;

            /// @brief Internal structure access
            _task_t* _task;
            
        protected:
            /// @brief Overrideable initialization function. It is recommended \
            /// @brief to call constructors and initialize variables here. This function \
            /// @brief is called only the first time after it is introduced to the schedule
            virtual void Initialize() {}

            /// @brief Overrideable payload function. This function is called \
            /// @brief every time the schedule handles this Task and determines it is active
            virtual void Payload() {}

            /// @brief Overrideable cleanup function. It is recommended to call \
            /// @brief destructors and deinitialize variables here. \
            /// @brief Clean() is only called once when execution is ended
            virtual void Clean() {}

        public:
            /// @brief Delay calling the Payload() function by given amount of time.
            /// @param ns time to wait in nanoseconds
            void DelayNanoseconds(uint64_t);

            /// @brief Delay calling the Payload() function by given cycle count
            /// @param iter cycles to wait
            void DelayIterations(uint64_t);
            
            /// @brief Puts the task in an idle state without removing it from the schedule
            void Sleep();

            /// @brief Resumes the task from an idle state
            void Awake();

            /// @brief Ends the task, priming it to be removed from the schedule
            void End();

            /// @brief Retrieves the kernel-issued ID of the Task or 0 if the task was not \
            /// @brief introduced to the kernel
            /// @return ID of task, 0 if none issued or revoked
            uint64_t GetID();

            /// @brief Check if the task is primed for running its payload this or next cycle
            /// @return true if this task will run this or next cycle, false if not
            bool IsActive();

            /// @brief Check if the task has been introduced to the kernel and has not ended
            /// @return true if this task is on the schedule, false if not
            bool IsAlive();
            
    };
}

#endif