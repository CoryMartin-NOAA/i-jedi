#pragma once

#include <cstdint>
#include "eckit/config/Configuration.h"

namespace ijedi
{
    typedef intptr_t F90io_fv3_restart;
    extern "C"
    {
        void ijedi_io_fv3_restart_create_f90(F90io_fv3_restart &, const eckit::Configuration &,
                                             const eckit::Configuration &);
        void ijedi_io_fv3_restart_delete_f90(F90io_fv3_restart &);
        void ijedi_io_fv3_restart_read_f90(const F90io_fv3_restart, const int, const int *,
                                           const char **, double **);
    }  // extern "C"
}  // namespace ijedi
