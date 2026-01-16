#ifndef K2_API_LIBRARY_HXX
#define K2_API_LIBRARY_HXX

#include <stdint.h>

namespace K2 {

    /// @brief Tiny structure holding version information on the K2 library used
    union version_t {
        unsigned serial : 32;
        struct {
            unsigned patch : 8;
            unsigned minor : 8;
            unsigned major : 16;
        };
    };

    /// @brief Get the K2 platform name
    /// @return character string pointer with platform name
    const char* Platform();

    /// @brief Get the K2 version info
    /// @return K2::version_t structure with version info
    const version_t Version();
}

#endif
