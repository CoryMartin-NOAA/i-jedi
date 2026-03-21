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
#include "ijedi/Geometry/fv3/GeometryParameters.h"

namespace ijedi
{

  GeometryFV3::GeometryFV3(const eckit::Configuration &conf, const eckit::mpi::Comm &comm,
                           const eckit::Configuration &geomVariables)
  {
    // Deserialize the parameters
    GeometryParameters params;
    params.deserialize(config);

    // Call the initialize phase, done only once.
    static bool initialized = false;
    if (!initialized)
    {
      fv3jedi_geom_initialize_f90((*params.fmsInit.value()).toConfiguration(), &comm_);
      initialized = true;
    }
  }

  void GeometryFV3::print(std::ostream &os) const
  {
    os << "FV3 Geometry:" << std::endl;
    os << "  Resolution (npx x npy): " << npx_ << " x " << npy_ << std::endl;
    os << "  Number of levels (npz): " << npz_ << std::endl;
    os << "  Tile number: " << tileNum_ << std::endl;
    os << "  Number of fields: " << fields_.size() << std::endl;
  }

  eckit::LocalConfiguration GeometryFV3::gridSpecific() const
  {
    eckit::LocalConfiguration conf;
    conf.set("grid_type", "fv3");
    conf.set("npx", npx_);
    conf.set("npy", npy_);
    conf.set("npz", npz_);
    conf.set("tile_num", tileNum_);
    return conf;
  }

} // namespace ijedi
