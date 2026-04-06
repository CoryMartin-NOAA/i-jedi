# Build the test executable
# -------------------------
add_subdirectory(mains)

# Automatically discover and add tests organized by tier
# -------------------------------------------------------
# All tests are built; use ctest -R tier<N> to run specific tiers
# Note: CONFIGURE_DEPENDS tells CMake to recheck for new/removed test files
# `export IJEDI_MPI_ARGS="--map-by :OVERSUBSCRIBE"` to allow MPI oversubscription (useful for CI/local testing)
set(IJEDI_MPI_ARGS $ENV{IJEDI_MPI_ARGS})

if(IJEDI_MPI_ARGS)
    separate_arguments(IJEDI_MPI_ARGS)
endif()

foreach(TIER RANGE 1 3)
    # Find all YAML files for this tier
    file(GLOB TIER_YAML_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/testinput/tier${TIER}_*.yaml")

    # Print YAML FILES
    list(LENGTH TIER_YAML_FILES NUM_FILES)
    message(STATUS "Found ${NUM_FILES} YAML files for tier ${TIER}:")

    foreach(YAML_FILE ${TIER_YAML_FILES})
        # Get the filename without directory and extension
        get_filename_component(TEST_NAME ${YAML_FILE} NAME_WE)

        # Extract components: tier<N>_<type>_<name>
        string(REPLACE "_" ";" NAME_PARTS ${TEST_NAME})
        list(LENGTH NAME_PARTS NUM_PARTS)

        # Extract executalbe name from third element of NAME_PARTS. Executalb is first element when split by -
        list(GET NAME_PARTS 2 EXECUTABLE_NAME)
        string(REPLACE "-" ";" EXECUTABLE_PARTS ${EXECUTABLE_NAME})
        list(GET EXECUTABLE_PARTS 0 EXECUTABLE_BASE)

        # Ensure we have exactly 3 parts (tier, type, name)
        if(${NUM_PARTS} EQUAL 3)
            # Get relative path for ARGS
            file(RELATIVE_PATH YAML_REL_PATH ${CMAKE_CURRENT_BINARY_DIR} ${YAML_FILE})

            # Add the test
            add_test(NAME ijedi_${TEST_NAME}
                COMMAND ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} 6 ${IJEDI_MPI_ARGS}
                $<TARGET_FILE:ijedi_test.x> ${EXECUTABLE_BASE} ${YAML_REL_PATH})

            message(STATUS "  Added tier ${TIER} test: ijedi_${TEST_NAME}")
        else()
            # Fail with useful message
            message(FATAL_ERROR "Test file ${YAML_FILE} does not follow naming convention tier<N>_<type>_<name>.yaml")
        endif()
    endforeach()
endforeach()

# Link the directory 'data' to the test directory of the build
# ------------------------------------------------------------
file(CREATE_LINK
    "${CMAKE_CURRENT_SOURCE_DIR}/data"
    "${CMAKE_CURRENT_BINARY_DIR}/data"
    SYMBOLIC
)
