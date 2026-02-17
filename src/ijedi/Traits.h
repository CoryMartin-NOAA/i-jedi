#pragma once

#include <string>

#include "ijedi/Geometry/Geometry.h"

namespace ijedi {

struct Traits {
  static std::string name() {return "ijedi";}
  static std::string nameCovar() {return "ijediError";}

  typedef ijedi::Geometry           Geometry;
};

}  // namespace ijedi

