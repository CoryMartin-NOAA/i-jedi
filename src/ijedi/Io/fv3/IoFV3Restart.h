#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "atlas/field.h"
#include "eckit/config/LocalConfiguration.h"
#include "oops/util/ObjectCounter.h"

#include "ijedi/Geometry/Geometry.h"
#include "ijedi/Io/IoBase.h"
#include "ijedi/Io/fv3/IoFV3.h"
#include "ijedi/Io/fv3/IoFV3Restart.interface.h"

namespace ijedi
{
    class IoFV3Restart : public IoBase, private util::ObjectCounter<IoFV3Restart>
    {
     public:
        static const std::string classname() { return "ijedi::IoFV3Restart"; }

        typedef IoFV3Parameters Parameters_;

        IoFV3Restart(const Geometry &, const Parameters_ &);
        ~IoFV3Restart();
        void read(atlas::FieldSet &, const eckit::LocalConfiguration &,
                  const eckit::LocalConfiguration &) const override;
        void write(const atlas::FieldSet &, const eckit::LocalConfiguration &,
                   const eckit::LocalConfiguration &) const override;

     private:
        void print(std::ostream &) const override;

        Parameters_ parameters_;
        const Geometry &geom_;
        F90io_fv3_restart keySelf_;
    };
}  // namespace ijedi
