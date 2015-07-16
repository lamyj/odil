find_path(ICU_INCLUDE_DIR "unicode/ucnv.h")
# icucore is for OS X
find_library(ICU_LIBRARIES NAMES icuuc icucore)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ICU DEFAULT_MSG
    ICU_INCLUDE_DIR ICU_LIBRARIES)
