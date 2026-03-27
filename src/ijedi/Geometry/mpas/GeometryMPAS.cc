// (C) Copyright 2026- NOAA.
// This software is licensed under the terms of the Creative Commons
// Attribution-NonCommercial-ShareAlike Licence.
// See LICENSE file in the top-level directory for details.

#include "eckit/config/Configuration.h"
#include "eckit/config/LocalConfiguration.h"

#include "ijedi/Geometry/mpas/GeometryMPAS.h"

namespace ijedi
{

  GeometryMPAS::GeometryMPAS(const eckit::Configuration &geomConfig,
                             const eckit::mpi::Comm &comm,
                             eckit::Configuration &geomVariables) {}

  void GeometryMPAS::print(std::ostream &os) const {}

}  // namespace ijedi
