// (C) Copyright 2026- NOAA.
// This software is licensed under the terms of the Creative Commons
// Attribution-NonCommercial-ShareAlike Licence.
// See LICENSE file in the top-level directory for details.

#pragma once

#include "atlas/field.h"
#include "atlas/functionspace.h"

#include "eckit/mpi/Comm.h"

// Forward declarations
namespace eckit
{
    class Configuration;
}

namespace util
{
    class DateTime;
    class Duration;
}

namespace ijedi
{
    extern "C"
    {
        void f_fv3_geom_initialize(const eckit::LocalConfiguration &, const eckit::mpi::Comm *);
        void f_fv3_geom_create(const eckit::Configuration &, const eckit::Configuration &,
                               const eckit::mpi::Comm *);
    } // extern "C"
} // namespace ijedi
