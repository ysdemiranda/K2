#ifndef K2_API_KERNEL_HXX
#define K2_API_KERNEL_HXX

#include <stdint.h>

namespace K2 {

    // Container for the K2 kernel structure
    class Kernel {
        public:
            /// @brief Constructs a K2::Kernel object
            /// @param time_ns_fnptr pointer to a function that returns the current time in nanoseconds
            Kernel(uint64_t (*)());

            /// @brief Destroys the K2::Kernel object
            ~Kernel();

        private:         
            /// @brief Clock Subsystem API specification   
            class Clock;

            /// @brief Schedule Subsystem API specification
            class Schedule;

            /// @brief Internal kernel structure specification
            struct _kstruct_t;

            /// @brief Internal kernel structure access
            _kstruct_t* _kstruct;
            
        public:
            /// @brief Kernel injectable Task class specification
            class Task;

        public:
            /// @brief Access the Clock API
            /// @return pointer to Clock subsystem API
            Clock* GetClock();

            /// @brief Access the Schedule API
            /// @return pointer to Schedule subsystem API
            Schedule* GetSchedule();

            /// @brief Cycle the kernel, updating the Clock and Schedule\
            /// @brief subsystems and running loaded tasks
            void Cycle();
    };
}

#endif