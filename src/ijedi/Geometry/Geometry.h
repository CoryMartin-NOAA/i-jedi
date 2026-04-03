#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "eckit/mpi/Comm.h"

#include "atlas/field.h"
#include "atlas/functionspace.h"

#include "oops/util/ObjectCounter.h"
#include "oops/util/Printable.h"

#include "ijedi/Geometry/base/GeometryBase.h"

#include "ijedi/FieldMetadata/FieldsMetadata.h"

// Forward declarations
namespace eckit
{
  class Configuration;
}

namespace oops
{
  class Variables;
}

namespace ijedi
{

  // -----------------------------------------------------------------------------
  // Geometry handles geometry.

  class Geometry : public util::Printable,
                   private util::ObjectCounter<Geometry>
  {
  public:
    static const std::string classname() { return "ijedi::Geometry"; }

    Geometry(const eckit::Configuration &, const eckit::mpi::Comm &);
    Geometry(const Geometry &);
    ~Geometry();

    bool levelsAreTopDown() const { return true; }
    std::vector<double> verticalCoord(std::string &) const;
    std::vector<size_t> variableSizes(const oops::Variables &) const;

    const eckit::mpi::Comm &getComm() const { return comm_; }

    const atlas::FunctionSpace &functionSpace() const { return *functionSpace_; }
    const atlas::FieldSet &fields() const { return *fieldSet_; }
    atlas::FunctionSpace &functionSpace() { return *functionSpace_; }
    atlas::FieldSet &fields() { return *fieldSet_; }
    const int &numLevels() const { return numberLevels_; }

    // Function to access field metadata
    // const FieldMetadata getFieldMetadata() const { return *fieldsMeta_; };

    // Function to return the geometry variables
    const eckit::Configuration &geomVariables() const { return *geomVariables_; }

  private:
    Geometry &operator=(const Geometry &);
    void print(std::ostream &) const;
    const eckit::mpi::Comm &comm_;
    std::shared_ptr<FieldsMetadata> fieldsMeta_;
    std::shared_ptr<GeometryBase> geometryImpl_;
    std::shared_ptr<eckit::Configuration> geomVariables_;
    std::shared_ptr<atlas::FunctionSpace> functionSpace_;
    std::shared_ptr<atlas::FieldSet> fieldSet_;
    int numberLevels_;
    std::string type_;
  };
  // -----------------------------------------------------------------------------

} // namespace ijedi
