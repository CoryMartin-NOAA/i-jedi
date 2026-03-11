// (C) Copyright 2026- NOAA.
// This software is licensed under the terms of the Creative Commons
// Attribution-NonCommercial-ShareAlike Licence.
// See LICENSE file in the top-level directory for details.

#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "eckit/mpi/Comm.h"

#include "atlas/field.h"
#include "atlas/functionspace.h"

#include "atlas/grid.h"
#include "atlas/grid/detail/grid/GridFactory.h"
#include "atlas/grid/Vertical.h"
#include "atlas/mesh/Mesh.h"
#include "atlas/mesh/Nodes.h"
#include "atlas/meshgenerator.h"
#include "atlas/functionspace/StructuredColumns.h"

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

    explicit Geometry(const eckit::Configuration &,
                      const eckit::mpi::Comm &);
    Geometry(const Geometry &);
    ~Geometry();

    bool levelsAreTopDown() const { return true; }
    std::vector<double> verticalCoord(std::string &) const;
    std::vector<size_t> variableSizes(const oops::Variables &) const;

    const eckit::mpi::Comm &getComm() const { return comm_; }
    const atlas::StructuredGrid &getGrid() const { return grid_; }
    const atlas::grid::Partitioner partitioner() const { return partitioner_; }
    const atlas::Mesh &getMesh() const { return mesh_; }
    const atlas::FunctionSpace &functionSpace() const { return functionSpace_; }
    const atlas::FieldSet &fields() const { return fields_; }
    const atlas::Vertical &getVerticalCoord() const { return vcoord_; }

    atlas::FunctionSpace &functionSpace() { return functionSpace_; }
    atlas::FieldSet &fields() { return fields_; }

  private:
    Geometry &operator=(const Geometry &);
    void print(std::ostream &) const;
    const eckit::mpi::Comm &comm_;
    std::shared_ptr<FieldsMetadata> fieldsMeta_;

    atlas::StructuredGrid grid_;
    atlas::grid::Partitioner partitioner_;
    atlas::grid::Distribution distribution_;
    atlas::Mesh mesh_;
    atlas::FunctionSpace functionSpace_;
    atlas::FieldSet fields_;
    int numLevels_;
    std::string grid_type_;
    int halo_size_;
    std::vector<double> ak_, bk_;
    atlas::Vertical vcoord_;
    std::shared_ptr<GeometryBase> geometryImpl_;
  };
  // -----------------------------------------------------------------------------

} // namespace ijedi
