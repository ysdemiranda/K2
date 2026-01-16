#ifndef K2_API_CLOCK_HXX
#define K2_API_CLOCK_HXX

#include "kernel.hxx"

namespace K2 {
    class Kernel::Clock {
        friend Kernel;
        private:
            struct _clock_t;
            _clock_t* _clock;
            Clock(uint64_t (*)());
            ~Clock();
            
        public:
            /// @brief Get current time from hardware
            /// @return 64 bit unsigned integer current time in nanoseconds
            uint64_t CurrentTime();

            /// @brief Get time of kernel creation
            /// @return 64 bit unsigned integer time point of kernel creation
            uint64_t BootTime();

            /// @brief Get time of cycle start
            /// @return 64 bit unsigned integer time point of cycle start
            uint64_t CycleTime();

            /// @brief Get past time since kernel creation
            /// @return 64 bit unsigned integer nanoseconds since kernel creation
            uint64_t Uptime();

            /// @brief Get current iteration count
            /// @return 64 bit unsigned integer current cycle iteration 
            uint64_t Iteration();

            /// @brief Get delta time between current cycle and past cycle
            /// @return 64 bit unsigned integer time between this and last cycle
            uint64_t DeltaTime();
    };
}

#endif