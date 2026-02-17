#include <string>
#include <numeric>

#include "eckit/config/Configuration.h"
#include "eckit/exception/Exceptions.h"

#include "oops/util/Logger.h"

#include "ijedi/Geometry/Geometry.h"

// -----------------------------------------------------------------------------
namespace ijedi {
// -----------------------------------------------------------------------------
  const int HALO_SIZE = 1;
// -----------------------------------------------------------------------------
  Geometry::Geometry(const eckit::Configuration & conf,
                     const eckit::mpi::Comm & comm)
    : comm_(comm) {
    const eckit::Configuration * configc = &conf;

    eckit::LocalConfiguration atlas_config = conf.getSubConfiguration("atlas");
    halo_size_ = atlas_config.getInt("halo", HALO_SIZE);

    // Initialize eckit communicator for atlas
    eckit::mpi::setCommDefault(comm_.name().c_str());

    // Create the grid
    grid_ = atlas::Grid(atlas_config);

    // Finally, print a summary of the geometry
    this->print(oops::Log::info());
  }
// -----------------------------------------------------------------------------
  Geometry::Geometry(const Geometry & other)
    : comm_(other.comm_) {

    grid_ = other.grid_;
  }
// -----------------------------------------------------------------------------
  Geometry::~Geometry() {
  }
// -----------------------------------------------------------------------------
  void Geometry::print(std::ostream & os) const {
    os << "Geometry:" << std::endl;
    os << "  Grid Name: " << grid_.name() << std::endl;
    os << "  Number of Points: " << grid_.size() << std::endl;
    os << "  Grid nx, ny: " << grid_.nxmax() << ", " << grid_.ny() << std::endl;
    os << "  Grid y: " << grid_.y() << std::endl;
    os << "  Grid Projection Units: " << grid_.projection().units()
       << std::endl;
    os << "  Domain: " << grid_.domain() << std::endl;
    os << "  Periodic: " << grid_.periodic() << std::endl;
    os << "  Spec: " << grid_.spec() << std::endl;
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
