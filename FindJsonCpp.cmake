# - Try to find JsonCpp
# Once done this will define
#  JsonCpp_FOUND - System has JsonCpp
#  JsonCpp_INCLUDE_DIRS - The JsonCpp include directories
#  JsonCpp_LIBRARIES - The libraries needed to use JsonCpp
#  JsonCpp_DEFINITIONS - Compiler switches required for using JsonCpp

find_package(PkgConfig)
pkg_check_modules(PC_JsonCpp QUIET jsoncpp)
set(JsonCpp_DEFINITIONS ${PC_JsonCpp_CFLAGS_OTHER})

find_path(JsonCpp_INCLUDE_DIR "json/json.h" HINTS ${PC_JsonCpp_INCLUDE_DIRS})
find_library(JsonCpp_LIBRARY NAMES jsoncpp HINTS ${PC_JsonCpp_LIBRARY_DIRS} )

set(JsonCpp_LIBRARIES ${JsonCpp_LIBRARY} )
set(JsonCpp_INCLUDE_DIRS ${JsonCpp_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set JsonCpp_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(
    JsonCpp DEFAULT_MSG JsonCpp_LIBRARY JsonCpp_INCLUDE_DIR)

mark_as_advanced(JsonCpp_INCLUDE_DIR JsonCpp_LIBRARY)

if(JsonCpp_FOUND AND NOT TARGET JsonCpp::JsonCpp)
    add_library(JsonCpp::JsonCpp INTERFACE IMPORTED)
    set_target_properties(JsonCpp::JsonCpp PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${JsonCpp_INCLUDE_DIR}"
        INTERFACE_LINK_LIBRARIES "${JsonCpp_LIBRARIES}"
    )
endif()
