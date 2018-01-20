find_package(Boost REQUIRED COMPONENTS date_time filesystem system)
find_package(ICU REQUIRED)
find_package(JsonCpp REQUIRED)
find_package(Log4Cpp REQUIRED)
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

# Regroup files by folder
GroupFiles(Header_Files)
GroupFiles(Source_Files)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS} ${DCMTK_INCLUDE_DIRS}
${ICU_INCLUDE_DIRS} ${Log4Cpp_INCLUDE_DIRS} ${JsonCpp_INCLUDE_DIRS})

add_definitions(
    ${DCMTK_DEFINITIONS}
    -D BOOST_ASIO_SEPARATE_COMPILATION
    -D ODIL_MAJOR_VERSION=${odil_MAJOR_VERSION}
)
if(BUILD_SHARED_LIBS)
    add_definitions(-D BOOST_ALL_DYN_LINK)
endif()

link_directories(${Boost_LIBRARY_DIRS} ${DCMTK_LIBRARY_DIRS})

add_library(libodil ${Source_Files} ${Header_Files} ${templates})
set_target_properties(libodil PROPERTIES OUTPUT_NAME odil)

target_link_libraries(libodil
    ${Boost_LIBRARIES} ${DCMTK_LIBRARIES} ${ICU_LIBRARIES} ${JsonCpp_LIBRARIES}
    ${Log4Cpp_LIBRARIES})

if(WIN32)
    add_definitions(-DBUILDING_ODIL)
    target_link_libraries(libodil netapi32)
endif()

set_target_properties(libodil PROPERTIES
    VERSION ${odil_VERSION}
    SOVERSION ${odil_MAJOR_VERSION})
if(APPLE)
    set_target_properties(
        libodil PROPERTIES INSTALL_NAME_DIR ${CMAKE_INSTALL_PREFIX}/lib)
endif()

install(
    DIRECTORY odil/ DESTINATION include/odil
    FILES_MATCHING PATTERN "*.h" PATTERN "*.txx")
install(
    TARGETS libodil
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
