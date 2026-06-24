#pragma once

#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "oops/util/DateTime.h"
#include "oops/util/parameters/OptionalParameter.h"
#include "oops/util/parameters/Parameter.h"
#include "oops/util/parameters/Parameters.h"
#include "oops/util/parameters/RequiredParameter.h"

#include "ijedi/Io/IoBase.h"

namespace ijedi
{

    // -------------------------------------------------------------------------------------------------

    class IoFV3Parameters : public IoParametersBase
    {
        OOPS_CONCRETE_PARAMETERS(IoFV3Parameters, IoParametersBase)

     public:
        // Names of files to be read/written to
        oops::Parameter<std::string> source{"source", "history or restart", "history", this};

        // Atmosphere file name
        oops::OptionalParameter<std::string> atm_file{"atm_file",
                                                      "atmosphere file name",
                                                      this};

        // Surface file name
        oops::OptionalParameter<std::string> sfc_file{"sfc_file",
                                                      "surface file name",
                                                      this};

        // Path prepended to all files
        oops::Parameter<std::string> datapath{"datapath", "path to location of files to be read",
                                              "./", this};

        oops::OptionalParameter<std::string> filename_core{"filename_core",
                                   "FV3 core restart filename",
                                   this};
        oops::OptionalParameter<std::string> filename_trcr{"filename_trcr",
                                   "FV3 tracer restart filename",
                                   this};
        oops::OptionalParameter<std::string> filename_sfcd{"filename_sfcd",
                                   "FV3 surface data restart filename",
                                   this};
        oops::OptionalParameter<std::string> filename_sfcw{"filename_sfcw",
                                   "FV3 surface wind restart filename",
                                   this};
        oops::OptionalParameter<std::string> filename_cplr{"filename_cplr",
                                   "FV3 coupler restart filename",
                                   this};
        oops::OptionalParameter<std::string> filename_spec{"filename_spec",
                                   "FV3 spectral restart filename",
                                   this};
        oops::OptionalParameter<std::string> filename_phys{"filename_phys",
                                   "FV3 physics restart filename",
                                   this};
        oops::OptionalParameter<std::string> filename_orog{"filename_orog",
                                   "FV3 orography restart filename",
                                   this};
        oops::OptionalParameter<std::string> filename_cold{"filename_cold",
                                   "FV3 cold-start restart filename",
                                   this};

        // Option to clobber existing files
        oops::OptionalParameter<std::vector<bool>> clobber{"clobber existing files",
                                                           "clobber existing files", this};

        // Whether the tile is a dimension in the file
        oops::OptionalParameter<std::vector<bool>> tiledim{"tile is a dimension",
                                                           "tile is a dimension", this};

        // Name of the X Dimension in the file
        oops::OptionalParameter<std::vector<std::string>> xdim{"x dimension name",
                                                               "x dimension name",
                                                               this};

        // Name of the Y Dimension in the file
        oops::OptionalParameter<std::vector<std::string>> ydim{"y dimension name",
                                                               "y dimension name",
                                                               this};

        // Name of the Z Full Dimension in the file
        oops::OptionalParameter<std::vector<std::string>> zfdim{"z full dimension name",
                                                                "z full dimension name",
                                                                this};

        // Name of the Z Half Dimension in the file
        oops::OptionalParameter<std::vector<std::string>> zhdim{"z half dimension name",
                                                                "z half dimension name",
                                                                this};

        // Set date/time on read
        oops::OptionalParameter<bool> setDateTime{"set datetime on read",
                                                  "set datetime on read", this};

        // Optional list of fields to write out
        oops::OptionalParameter<std::vector<std::string>>
            fieldsToWrite{"fields to write",
                          "names of the fields to write",
                           this};

        // Floating point precision in bytes for NetCDF write
        oops::OptionalParameter<int> floatPrecision{"float precision in bytes",
                                                    "number of bytes of floating point precision",
                                                    this};

        // Compute pressure at the edges from pressure at the surface (instead of reading it)
        oops::OptionalParameter<bool> computeP{"compute edge pressure from surface pressure",
                                               "compute edge pressure from surface pressure",
                                               this};

        // Maximum allowable difference in the Geometry lat/lon compared to the file lat/lon
        // In practice users should expect differences order 1e-12 or smaller if everything
        // is in double precision. In practice models may produce files at lower precision.
        // Differences smaller than 1e-6 should be sufficient to assess that the geometry of
        // the model producing the file being read is the same at the one in fv3-jedi.
        oops::Parameter<double> maxDiff{"max allowable geometry difference",
                                        "max allowable geometry difference", 1e-6, this};
    };

    // -------------------------------------------------------------------------------------------------
    class IoFV3 : public IoBase, private util::ObjectCounter<IoFV3>
    {
     public:
        static const std::string classname() { return "ijedi::IoFV3"; }

        typedef IoFV3Parameters Parameters_;

        IoFV3(const Geometry &, const Parameters_ &);
        ~IoFV3();
        void read(atlas::FieldSet &, const eckit::LocalConfiguration &,
                  const eckit::LocalConfiguration &) const override;
        void write(const atlas::FieldSet &, const eckit::LocalConfiguration &,
                   const eckit::LocalConfiguration &) const override;

     private:
        void print(std::ostream &) const override;

        // Helper methods for reading different file formats
        void readHistoryFiles(atlas::FieldSet &, const eckit::LocalConfiguration &,
                              const eckit::LocalConfiguration &) const;
        void readRestartFiles(atlas::FieldSet &, const eckit::LocalConfiguration &,
                      const eckit::LocalConfiguration &) const;
        void checkNetCDF(int status, const std::string &operation) const;

        // Store parameters and geometry reference
        Parameters_ parameters_;
        const Geometry &geom_;
    };

    // -------------------------------------------------------------------------------------------------

}  // namespace ijedi
