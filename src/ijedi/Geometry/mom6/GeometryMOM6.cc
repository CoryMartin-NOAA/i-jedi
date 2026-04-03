#include "eckit/config/Configuration.h"
#include "eckit/config/LocalConfiguration.h"

#include "ijedi/Geometry/mom6/GeometryMOM6.h"

namespace ijedi
{

  GeometryMOM6::GeometryMOM6(const eckit::Configuration &geomConfig,
                             const eckit::mpi::Comm &comm,
                             eckit::Configuration &geomVariables,
                             atlas::FunctionSpace &functionSpace,
                             atlas::FieldSet &fieldSet,
                             int &numberLevels) {}

  void GeometryMOM6::print(std::ostream &os) const {}
} // namespace ijedi
