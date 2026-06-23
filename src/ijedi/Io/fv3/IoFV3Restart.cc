#include "ijedi/Io/fv3/IoFV3Restart.h"

#include <ostream>
#include <string>
#include <vector>

#include "atlas/array.h"
#include "atlas/field.h"
#include "eckit/config/LocalConfiguration.h"
#include "eckit/exception/Exceptions.h"
#include "oops/util/Logger.h"
#include "oops/util/Timer.h"

#include "ijedi/Geometry/Geometry.h"

namespace ijedi
{
    // -------------------------------------------------------------------------------------------------
    static IoMaker<IoFV3Restart> makerIoFV3Restart_("fv3 restart");
    // -------------------------------------------------------------------------------------------------
    IoFV3Restart::IoFV3Restart(const Geometry &geom, const Parameters_ &params)
        : IoBase(geom, params.toConfiguration()), parameters_(params), geom_(geom)
    {
        util::Timer timer(classname(), "IoFV3Restart");
        oops::Log::trace() << classname() << " constructor starting" << std::endl;

        ijedi_io_fv3_restart_create_f90(keySelf_, params.toConfiguration(), geom.toConfiguration());

        oops::Log::trace() << classname() << " constructor done" << std::endl;
    }
    // -------------------------------------------------------------------------------------------------
    IoFV3Restart::~IoFV3Restart()
    {
        util::Timer timer(classname(), "~IoFV3Restart");
        oops::Log::trace() << classname() << " destructor starting" << std::endl;

        ijedi_io_fv3_restart_delete_f90(keySelf_);

        oops::Log::trace() << classname() << " destructor done" << std::endl;
    }
    // -------------------------------------------------------------------------------------------------
    void IoFV3Restart::read(atlas::FieldSet &fieldSet, const eckit::LocalConfiguration &fileionames,
                            const eckit::LocalConfiguration &fileioscaling) const
    {
        util::Timer timer(classname(), "read state");
        oops::Log::trace() << classname() << " read state starting" << std::endl;

        const std::vector<std::string> jediNames = fileionames.keys();
        const int numFields = jediNames.size();

        std::vector<int> levels(numFields);
        std::vector<std::string> ncVarNamesStr(numFields);
        std::vector<const char*> ncVarNames(numFields);
        std::vector<double*> dataPtrs(numFields);

        for (int i = 0; i < numFields; ++i) {
            const std::string &jediName = jediNames[i];
            atlas::Field &field = fieldSet.field(jediName);
            levels[i] = field.levels();
            ncVarNamesStr[i] = fileionames.getString(jediName);
            ncVarNames[i] = ncVarNamesStr[i].c_str();

            auto view = atlas::array::make_view<double, 2>(field);
            dataPtrs[i] = view.data();
        }

        ijedi_io_fv3_restart_read_f90(keySelf_, numFields, levels.data(), ncVarNames.data(), dataPtrs.data());

        // Apply scaling if provided
        for (int i = 0; i < numFields; ++i) {
            const std::string &jediName = jediNames[i];
            if (fileioscaling.has(jediName)) {
                const double scale = fileioscaling.getDouble(jediName);
                atlas::Field &field = fieldSet.field(jediName);
                auto view = atlas::array::make_view<double, 2>(field);
                for (atlas::idx_t jnode = 0; jnode < field.shape(0); ++jnode) {
                    for (int jlev = 0; jlev < field.levels(); ++jlev) {
                        view(jnode, jlev) *= scale;
                    }
                }
            }
        }

        oops::Log::trace() << classname() << " read state done" << std::endl;
    }
    // -------------------------------------------------------------------------------------------------
    void IoFV3Restart::write(const atlas::FieldSet &x, const eckit::LocalConfiguration &fileionames,
                             const eckit::LocalConfiguration &fileioscaling) const
    {
        throw eckit::Exception("Writing restart files not yet implemented in IoFV3Restart");
    }
    // -------------------------------------------------------------------------------------------------
    void IoFV3Restart::print(std::ostream &os) const
    {
        os << classname() << " IO for FV3 Restart files using FMS";
    }
    // -------------------------------------------------------------------------------------------------
}  // namespace ijedi
