find_package(Boost REQUIRED COMPONENTS date_time exception filesystem log system)
find_package(ICU REQUIRED COMPONENTS uc)
find_package(JsonCpp REQUIRED)
if(WITH_DCMTK)
    find_package(DCMTK REQUIRED)
endif()

file(GLOB_RECURSE Header_Files "*.h")
file(GLOB_RECURSE Source_Files "*.cpp")
file(GLOB_RECURSE templates "*.txx")
list(SORT Header_Files)
list(SORT Source_Files)
list(SORT templates)

if(NOT WITH_DCMTK)
    set(pattern "${CMAKE_CURRENT_SOURCE_DIR}/odil/dcmtk/[^;]+[;$]")
    string(REGEX REPLACE ${pattern} "" Header_Files "${Header_Files}")
    string(REGEX REPLACE ${pattern} "" Source_Files "${Source_Files}")
    string(REGEX REPLACE ${pattern} "" templates "${templates}")
endif()

add_library(libodil ${Source_Files} ${Header_Files} ${templates})

target_compile_definitions(
    libodil 
    PUBLIC
        BOOST_ASIO_SEPARATE_COMPILATION ${DCMTK_DEFINITIONS}
        ODIL_VERSION_MAJOR=${Odil_VERSION_MAJOR}
        $<$<BOOL:BUILD_SHARED_LIBS>:BOOST_ALL_DYN_LINK>
        $<$<PLATFORM_ID:Windows>:BOOST_UUID_FORCE_AUTO_LINK>
    PRIVATE 
        $<$<PLATFORM_ID:Windows>:BUILDING_ODIL>)

target_include_directories(
    libodil 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/> $<INSTALL_INTERFACE:>
        "$<$<BOOL:${WITH_DCMTK}>:${DCMTK_INCLUDE_DIRS}>")

target_link_libraries(
    libodil 
    PUBLIC
        Boost::date_time Boost::exception Boost::filesystem Boost::log 
        "$<$<BOOL:${WITH_DCMTK}>:${DCMTK_LIBRARIES}>"
        ICU::uc JsonCpp::JsonCpp
        $<$<PLATFORM_ID:Windows>:netapi32>
        # WARNING Need to link with bcrypt explicitely, 
        # cf. https://github.com/boostorg/uuid/issues/68#issuecomment-430173245
        # Not sure why iphlpapi is not linked.
        "$<$<BOOL:${VCPKG_TOOLCHAIN}>:bcrypt;iphlpapi>")

if(APPLE)
    # WARNING: Boost::log may add -licudata  -licui18n  -licuu, which cause 
    # problems with macOS/brew
    get_filename_component(ICU_FOUND_DIRECTORY "${ICU_UC_LIBRARY}" DIRECTORY)
    if(NOT "${ICU_FOUND_DIRECTORY}" STREQUAL "")
        target_link_libraries(libodil PUBLIC "-L${ICU_FOUND_DIRECTORY}")
    endif()
endif()

set_target_properties(
    libodil PROPERTIES 
    PUBLIC_HEADER "${Header_Files};${templates}"
    OUTPUT_NAME odil 
    VERSION ${Odil_VERSION} 
    SOVERSION ${Odil_VERSION_MAJOR}
    $<$<PLATFORM_ID:Darwin>:INSTALL_NAME_DIR ${CMAKE_INSTALL_PREFIX}/lib>)

install(
    TARGETS libodil
    EXPORT OdilTargets
    ARCHIVE DESTINATION bin LIBRARY DESTINATION lib RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/odil
    INCLUDES DESTINATION include)
