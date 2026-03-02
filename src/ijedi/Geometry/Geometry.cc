// (C) Copyright 2026- NOAA.
// This software is licensed under the terms of the Creative Commons
// Attribution-NonCommercial-ShareAlike Licence.
// See LICENSE file in the top-level directory for details.

#include <string>
#include <numeric>

#include "eckit/config/Configuration.h"
#include "eckit/exception/Exceptions.h"

#include "oops/util/Logger.h"

#include "ijedi/Geometry/Geometry.h"
#include "ijedi/Geometry/base/GeometryBase.h"

// -----------------------------------------------------------------------------
namespace ijedi {
// -----------------------------------------------------------------------------
  const int HALO_SIZE = 1;
// -----------------------------------------------------------------------------
  Geometry::Geometry(const eckit::Configuration & conf,
                     const eckit::mpi::Comm & comm)
    : comm_(comm) {
    eckit::LocalConfiguration atlas_config = conf.getSubConfiguration("atlas");
    halo_size_ = atlas_config.getInt("halo", HALO_SIZE);

    geometryImpl_ = GeometryBase::create(conf, comm_);
    grid_ = geometryImpl_->getGrid();

    // Finally, print a summary of the geometry
    this->print(oops::Log::info());
  }
// -----------------------------------------------------------------------------
  Geometry::Geometry(const Geometry & other)
    : comm_(other.comm_),
      geometryImpl_(other.geometryImpl_) {

    grid_ = other.grid_;
  }
// -----------------------------------------------------------------------------
  Geometry::~Geometry() {
  }
// -----------------------------------------------------------------------------
  void Geometry::print(std::ostream & os) const {
    if (geometryImpl_) {
      geometryImpl_->print(os);
      return;
    }

    os << "Geometry:" << std::endl;
    os << "  Grid Name: " << grid_.name() << std::endl;
    os << "  Number of Points: " << grid_.size() << std::endl;
  }
// -----------------------------------------------------------------------------
  void Geometry::latlon(std::vector<double> & lats,
                        std::vector<double> & lons,
                        const bool halo) const {
    // get the number of total grid points (including halo)
    int gridSizeWithHalo = functionSpace_.size();
    auto vLonlat = atlas::array::make_view<double, 2>(functionSpace_.lonlat());

    // count the number of owned non-ghost points
    auto vGhost = atlas::array::make_view<int, 1>(functionSpace_.ghost());
    int gridSizeNoHalo = 0;
    for (size_t i = 0; i < gridSizeWithHalo; i++) {
      if (vGhost(i) == 0) gridSizeNoHalo++;
    }

    // allocate arrays
    int gridSize = (halo) ? gridSizeWithHalo : gridSizeNoHalo;
    lons.resize(gridSize);
    lats.resize(gridSize);

    // fill
    int idx = 0;
    for (size_t i=0; i < gridSizeWithHalo; i++) {
      if (!halo && vGhost(i)) continue;
      double lon = vLonlat(i, 0);
      double lat = vLonlat(i, 1);
      lats[idx] = lat;
      lons[idx++] = lon;
    }
    ASSERT(idx == gridSize);
  }
// -----------------------------------------------------------------------------
}  // namespace ijedi
