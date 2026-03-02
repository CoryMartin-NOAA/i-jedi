// (C) Copyright 2026- NOAA.
// This software is licensed under the terms of the Creative Commons
// Attribution-NonCommercial-ShareAlike Licence.
// See LICENSE file in the top-level directory for details.

#include <algorithm>
#include <memory>
#include <string>

#include "eckit/config/Configuration.h"
#include "eckit/config/LocalConfiguration.h"
#include "eckit/exception/Exceptions.h"

#include "ijedi/Geometry/base/GeometryBase.h"
#include "ijedi/Geometry/fv3/GeometryFV3.h"
#include "ijedi/Geometry/mpas/GeometryMPAS.h"
#include "ijedi/Geometry/mom6/GeometryMOM6.h"

namespace ijedi {

namespace {

std::string getGeometryType(const eckit::Configuration & conf) {
  std::string type = "fv3";
  if (conf.has("geometry_type")) {
    type = conf.getString("geometry_type");
  } else if (conf.has("type")) {
    type = conf.getString("type");
  } else if (conf.has("atlas")) {
    const eckit::LocalConfiguration atlasConf = conf.getSubConfiguration("atlas");
    if (atlasConf.has("geometry_type")) {
      type = atlasConf.getString("geometry_type");
    } else if (atlasConf.has("type")) {
      type = atlasConf.getString("type");
    }
  }

  std::transform(type.begin(), type.end(), type.begin(),
                 [](unsigned char value) { return std::tolower(value); });
  return type;
}

}  // namespace

std::shared_ptr<GeometryBase> GeometryBase::create(const eckit::Configuration & conf,
                                                   const eckit::mpi::Comm & comm) {
  const std::string type = getGeometryType(conf);

  if (type == "fv3") {
    return std::make_shared<GeometryFV3>(conf, comm);
  }
  if (type == "mpas") {
    return std::make_shared<GeometryMPAS>(conf, comm);
  }
  if (type == "mom6") {
    return std::make_shared<GeometryMOM6>(conf, comm);
  }

  throw eckit::BadValue("Unsupported geometry type: " + type,
                        Here());
}

}  // namespace ijedi
