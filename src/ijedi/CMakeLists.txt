include_directories(${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND ijedi_src_files
  Traits.h
)

list(APPEND ijedi_src_files

  # Geometry
  Geometry/Geometry.cc
  Geometry/Geometry.h
  Geometry/base/GeometryBase.cc
  Geometry/base/GeometryBase.h
  Geometry/mpas/GeometryMPAS.cc
  Geometry/mpas/GeometryMPAS.h
  Geometry/mom6/GeometryMOM6.cc
  Geometry/mom6/GeometryMOM6.h

  # Fields

  # State

  # Increment

  # IO
)

# fv3 pieces if FMS is found
if(FMS_FOUND)
  list(APPEND ijedi_src_files
    Geometry/fv3/GeometryFV3.cc
    Geometry/fv3/GeometryFV3.h
    Geometry/fv3/ijedi_fv3_arrays.F90
    Geometry/fv3/ijedi_fv3_control.F90
    Geometry/fv3/ijedi_fv3_eta.F90
    Geometry/fv3/ijedi_fv3_geom_mod.f90
    Geometry/fv3/ijedi_fv3_grid_tools.F90
    Geometry/fv3/ijedi_fv3_grid_utils.F90
    Geometry/fv3/ijedi_fv3_mp_mod.F90
    Geometry/fv3/ijedi_fv3_sorted_index.F90
  )
endif()

ecbuild_add_library(TARGET ${PROJECT_NAME}
  SOURCES ${ijedi_src_files}
  INSTALL_HEADERS LISTED
  LINKER_LANGUAGE CXX
)

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

target_link_libraries(${PROJECT_NAME} PUBLIC NetCDF::NetCDF_C NetCDF::NetCDF_CXX)

# target_link_libraries( ${PROJECT_NAME} PUBLIC MPI::MPI_Fortran MPI::MPI_CXX )
target_link_libraries(${PROJECT_NAME} PUBLIC eckit)
target_link_libraries(${PROJECT_NAME} PUBLIC fckit)
target_link_libraries(${PROJECT_NAME} PUBLIC atlas atlas_f)
target_link_libraries(${PROJECT_NAME} PUBLIC oops)

if(FMS_FOUND)
  target_link_libraries(${PROJECT_NAME} PUBLIC FMS)
endif()

# target_link_libraries( ${PROJECT_NAME} PUBLIC ufo )
if(OpenMP_Fortran_FOUND)
  target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_Fortran)
endif()

if(OpenMP_CXX_FOUND)
  target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
endif()
