#pragma once

#include <ostream>

#include "eckit/mpi/Comm.h"

#include "atlas/grid.h"

#include "ijedi/Geometry/base/GeometryBase.h"

namespace eckit
{
  class Configuration;
}

namespace ijedi
{

  class GeometryFV3 : public GeometryBase
  {
  public:
    GeometryFV3(const eckit::Configuration &, const eckit::mpi::Comm &,
                eckit::Configuration &, atlas::FunctionSpace &, atlas::FieldSet &, int &);
    void print(std::ostream &) const override;

  private:
    std::string printMessage_;
  };

} // namespace ijedi
