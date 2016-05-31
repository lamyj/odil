# - Try to find Log4Cpp
# Once done this will define
#  Log4Cpp_FOUND - System has Log4Cpp
#  Log4Cpp_INCLUDE_DIRS - The Log4Cpp include directories
#  Log4Cpp_LIBRARIES - The libraries needed to use Log4Cpp
#  Log4Cpp_DEFINITIONS - Compiler switches required for using Log4Cpp

find_package(PkgConfig)
pkg_check_modules(PC_Log4Cpp QUIET log4cpp)
set(Log4Cpp_DEFINITIONS ${PC_Log4Cpp_CFLAGS_OTHER})

find_path(Log4Cpp_INCLUDE_DIR "unicode/ucnv.h" HINTS ${PC_Log4Cpp_INCLUDE_DIRS})
find_library(Log4Cpp_LIBRARY NAMES log4cpp HINTS ${PC_Log4Cpp_LIBRARY_DIRS} )

set(Log4Cpp_LIBRARIES ${Log4Cpp_LIBRARY} )
set(Log4Cpp_INCLUDE_DIRS ${Log4Cpp_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set Log4Cpp_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(
    Log4Cpp DEFAULT_MSG Log4Cpp_LIBRARY Log4Cpp_INCLUDE_DIR)

mark_as_advanced(Log4Cpp_INCLUDE_DIR Log4Cpp_LIBRARY)
