// (C) Copyright 2026- NOAA.
// This software is licensed under the terms of the Creative Commons
// Attribution-NonCommercial-ShareAlike Licence.
// See LICENSE file in the top-level directory for details.

#pragma once

#include <memory>
#include <ostream>
#include <string>

#include "eckit/config/LocalConfiguration.h"
#include "eckit/mpi/Comm.h"

#include "atlas/field.h"
#include "atlas/functionspace.h"

namespace eckit
{
  class Configuration;
}

namespace ijedi
{

  class GeometryBase
  {
  public:
    virtual ~GeometryBase() = default;

    static std::shared_ptr<GeometryBase> create(const eckit::Configuration &,
                                                const eckit::mpi::Comm &,
                                                eckit::Configuration &,
                                                atlas::FunctionSpace &,
                                                atlas::FieldSet &,
                                                int &);
    virtual void print(std::ostream &) const = 0;
  };

} // namespace ijedi
