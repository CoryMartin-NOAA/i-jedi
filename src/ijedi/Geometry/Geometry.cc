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

// -------------------------------------------------------------------------------------------------
namespace ijedi
{
  // -----------------------------------------------------------------------------------------------
  const int HALO_SIZE = 1;
  // -----------------------------------------------------------------------------------------------
  Geometry::Geometry(const eckit::Configuration &geomConf, const eckit::mpi::Comm &comm)
      : comm_(comm), geomVariables_(std::make_shared<eckit::LocalConfiguration>())
  {
    // Trace
    oops::Log::trace() << "Geometry constructor starting" << std::endl;

    // Create the geometry implementation (which will set numLevels_)
    geometryImpl_ = GeometryBase::create(geomConf, comm_, *geomVariables_, *functionSpace_,
                                         *fieldSet_, numberLevels_);

    // Construct the fields metadata object using numLevels from the base class
    fieldsMeta_.reset(new FieldsMetadata(numberLevels_));

    // Trace
    oops::Log::trace() << "Geometry constructor starting" << std::endl;
  }
  // -----------------------------------------------------------------------------------------------
  Geometry::Geometry(const Geometry &other)
      : comm_(other.comm_),
        geomVariables_(other.geomVariables_),
        numberLevels_(other.numberLevels_)
  {
    // Copy field metadata
    fieldsMeta_ = std::make_shared<FieldsMetadata>(*other.fieldsMeta_);
    // Copy function space
    functionSpace_ = std::make_shared<atlas::FunctionSpace>(*other.functionSpace_);
    // Copy field set
    fieldSet_ = std::make_shared<atlas::FieldSet>(*other.fieldSet_);
    // Create the geometry implementation (which will set numLevels_)
  }
  // -----------------------------------------------------------------------------------------------
  Geometry::~Geometry()
  {
  }
  // -----------------------------------------------------------------------------------------------
  void Geometry::print(std::ostream &os) const
  {
    geometryImpl_->print(os);
  }

  // -----------------------------------------------------------------------------------------------

  std::vector<double> Geometry::verticalCoord(std::string &vcUnits) const
  {
    // Not implemented, abort
    std::stringstream errorMsg;
    errorMsg << "Geometry::verticalCoord is not implemented" << std::endl;
    ABORT(errorMsg.str());

    std::vector<double> vc(numberLevels_);
    return vc;
  }

  // -----------------------------------------------------------------------------------------------

  std::vector<size_t> Geometry::variableSizes(const oops::Variables &vars) const
  {
    // Array of level heights
    std::vector<size_t> varSizes;
    // Loop through arrays and search metadata map for the levels
    // for (size_t it = 0; it < vars.size(); it++)
    //{
    //  varSizes.push_back(fieldsMeta_->getLevels(vars[it].name()));
    //}
    return varSizes;
  }

  // -----------------------------------------------------------------------------------------------

} // namespace ijedi
