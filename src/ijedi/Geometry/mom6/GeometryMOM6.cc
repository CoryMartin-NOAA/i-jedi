// (C) Copyright 2026- NOAA.
// This software is licensed under the terms of the Creative Commons
// Attribution-NonCommercial-ShareAlike Licence.
// See LICENSE file in the top-level directory for details.

#include "eckit/config/Configuration.h"
#include "eckit/config/LocalConfiguration.h"

#include "ijedi/Geometry/mom6/GeometryMOM6.h"

namespace ijedi
{

  GeometryMOM6::GeometryMOM6(const eckit::Configuration &geomConfig,
                             const eckit::mpi::Comm &comm,
                             eckit::Configuration &geomVariables) {}

  void GeometryMOM6::print(std::ostream &os) const {}
} // namespace ijedi
