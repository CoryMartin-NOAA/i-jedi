// (C) Copyright 2026- NOAA.
// This software is licensed under the terms of the Creative Commons
// Attribution-NonCommercial-ShareAlike Licence.
// See LICENSE file in the top-level directory for details.

#include "eckit/config/Configuration.h"
#include "eckit/config/LocalConfiguration.h"

#include "atlas/grid.h"
#include "atlas/mesh.h"
#include "atlas/meshgenerator.h"
#include "atlas/functionspace.h"

#include "ijedi/Geometry/fv3/GeometryFV3.h"
#include "ijedi/Geometry/fv3/GeometryFV3.interface.h"
#include "ijedi/Geometry/fv3/GeometryFV3Parameters.h"

namespace ijedi
{

  GeometryFV3::GeometryFV3(const eckit::Configuration &geomConfig, const eckit::mpi::Comm &comm,
                           eckit::Configuration &geomVariables) {
    // Deserialize the parameters
    GeometryParameters params;
    params.deserialize(geomConfig);

    // Call the initialize phase, done only once.
    static bool initialized = false;
    if (!initialized) {
      f_fv3_geom_initialize((*params.fmsInit.value()).toConfiguration(), &comm);
      initialized = true;
    }

    // Call the setup routine
    f_fv3_geom_create(geomConfig, geomVariables);
  }

  void GeometryFV3::print(std::ostream &os) const
  {
  }

}  // namespace ijedi
