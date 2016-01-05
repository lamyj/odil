# - Try to find DCMTK
# Once done this will define
#  DCMTK_FOUND - System has DCMTK
#  DCMTK_INCLUDE_DIRS - The DCMTK include directories
#  DCMTK_LIBRARY_DIRS - The DCMTK link directories
#  DCMTK_LIBRARIES - The libraries needed to use DCMTK
#  DCMTK_DEFINITIONS - Compiler switches required for using DCMTK

set(DCMTK_DEFINITIONS "-D HAVE_CONFIG_H")

find_path(DCMTK_INCLUDE_DIR "dcmtk/dcmdata/dctk.h")
find_library(DCMTK_LIBRARY dcmdata)

set(DCMTK_INCLUDE_DIRS ${DCMTK_INCLUDE_DIR})

set(DCMTK_LIBRARIES ${DCMTK_LIBRARY} dcmnet dcmdata oflog ofstd)
foreach(library pthread wrap z)
    find_library(${library}_LIBRARY ${library})
    if(${library}_LIBRARY)
        set(DCMTK_LIBRARIES ${DCMTK_LIBRARIES} ${${library}_LIBRARY})
    endif()
endforeach()

get_filename_component(DCMTK_LIBRARY_DIRS "${DCMTK_LIBRARY}" PATH)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set DCMTK_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(
    DCMTK DEFAULT_MSG DCMTK_INCLUDE_DIR DCMTK_LIBRARY)

mark_as_advanced(DCMTK_INCLUDE_DIR DCMTK_LIBRARY)
