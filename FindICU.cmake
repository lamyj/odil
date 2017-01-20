# - Try to find ICU
# Once done this will define
#  ICU_FOUND - System has ICU
#  ICU_INCLUDE_DIRS - The ICU include directories
#  ICU_LIBRARIES - The libraries needed to use ICU
#  ICU_DEFINITIONS - Compiler switches required for using ICU

find_package(PkgConfig)
pkg_check_modules(PC_ICU QUIET icu-uc)
set(ICU_DEFINITIONS ${PC_ICU_CFLAGS_OTHER})

find_path(ICU_INCLUDE_DIR "unicode/ucnv.h" HINTS ${PC_ICU_INCLUDE_DIRS})

# Get version
if(ICU_INCLUDE_DIR AND EXISTS "${ICU_INCLUDE_DIR}/unicode/uvernum.h")
	file(STRINGS "${ICU_INCLUDE_DIR}/unicode/uvernum.h" icu_header_str
	  REGEX "^#define[\t ]+U_ICU_VERSION[\t ]+\".*\".*")

	string(REGEX REPLACE "^#define[\t ]+U_ICU_VERSION[\t ]+\"([0-9]*).*"
	  "\\1" icu_version_string "${icu_header_str}")
	set(ICU_VERSION "${icu_version_string}" )
	unset(icu_header_str)
	unset(icu_version_string)
endif()

find_library(ICU_LIBRARY NAMES icuuc icuuc${ICU_VERSION} icuuc${ICU_VERSION}d HINTS ${PC_ICU_LIBRARY_DIRS} )

set(ICU_LIBRARIES ${ICU_LIBRARY} )
set(ICU_INCLUDE_DIRS ${ICU_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set ICU_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(ICU DEFAULT_MSG ICU_LIBRARY ICU_INCLUDE_DIR)

mark_as_advanced(ICU_INCLUDE_DIR ICU_LIBRARY)
