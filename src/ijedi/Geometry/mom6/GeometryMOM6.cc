// (C) Copyright 2026- NOAA.
// This software is licensed under the terms of the Creative Commons
// Attribution-NonCommercial-ShareAlike Licence.
// See LICENSE file in the top-level directory for details.

#include "eckit/config/Configuration.h"
#include "eckit/config/LocalConfiguration.h"

#include "ijedi/Geometry/mom6/GeometryMOM6.h"

namespace ijedi {

GeometryMOM6::GeometryMOM6(const eckit::Configuration & conf,
                           const eckit::mpi::Comm & comm) {
  eckit::mpi::setCommDefault(comm.name().c_str());
  const eckit::LocalConfiguration atlasConfig = conf.getSubConfiguration("atlas");
  grid_ = atlas::Grid(atlasConfig);
}

void GeometryMOM6::print(std::ostream & os) const {
  os << "Geometry type: mom6" << std::endl;
  os << "  Grid Name: " << grid_.name() << std::endl;
  os << "  Number of Points: " << grid_.size() << std::endl;
}

}  // namespace ijedi
