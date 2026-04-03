#include "eckit/config/Configuration.h"
#include "eckit/config/LocalConfiguration.h"

#include "ijedi/Geometry/mpas/GeometryMPAS.h"

namespace ijedi
{

  GeometryMPAS::GeometryMPAS(const eckit::Configuration &geomConfig,
                             const eckit::mpi::Comm &comm,
                             eckit::Configuration &geomVariables,
                             atlas::FunctionSpace &functionSpace,
                             atlas::FieldSet &fieldSet,
                             int &numberLevels) {}

  void GeometryMPAS::print(std::ostream &os) const {}

} // namespace ijedi
