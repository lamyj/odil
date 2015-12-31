# - Try to find DCMTK
# Once done this will define
#  DCMTK_FOUND - System has DCMTK
#  DCMTK_INCLUDE_DIRS - The DCMTK include directories
#  DCMTK_LIBRARY_DIRS - The DCMTK link directories
#  DCMTK_LIBRARIES - The libraries needed to use DCMTK
#  DCMTK_DEFINITIONS - Compiler switches required for using DCMTK

set(DCMTK_DEFINITIONS "-D HAVE_CONFIG_H")

find_path(DCMTK_INCLUDE_DIR "dcmtk/dcmdata/dctk.h")
find_library(DCMTK_LIBRARY NAMES dcmdata)

set(DCMTK_INCLUDE_DIRS ${DCMTK_INCLUDE_DIR})

set(DCMTK_LIBRARIES ${DCMTK_LIBRARY} dcmnet dcmdata oflog ofstd pthread z)
find_library(USE_WRAP wrap)
if(USE_WRAP)
    set(DCMTK_LIBRARIES ${DCMTK_LIBRARIES} wrap)
endif()

get_filename_component(DCMTK_LIBRARY_DIRS "${DCMTK_LIBRARY}" DIRECTORY)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set DCMTK_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(
    DCMTK DEFAULT_MSG DCMTK_INCLUDE_DIR DCMTK_LIBRARY)

mark_as_advanced(DCMTK_INCLUDE_DIR DCMTK_LIBRARY)
