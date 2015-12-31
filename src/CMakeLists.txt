find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(DCMTK REQUIRED)
find_package(ICU REQUIRED)
find_package(JsonCpp REQUIRED)

file(GLOB_RECURSE headers "*.h")
file(GLOB_RECURSE templates "*.txx")
file(GLOB_RECURSE files "*.cpp")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS} ${DCMTK_INCLUDE_DIRS}
    ${ICU_INCLUDE_DIRS} ${JsonCpp_INCLUDE_DIRS})
add_definitions(
    ${DCMTK_DEFINITIONS}
    -D BOOST_ASIO_SEPARATE_COMPILATION
    -D DCMTKPP_MAJOR_VERSION=${dcmtkpp_MAJOR_VERSION}
)
link_directories(${Boost_LIBRARY_DIRS} ${DCMTK_LIBRARY_DIRS})

add_library(dcmtkpp SHARED ${files} ${headers} ${templates})

target_link_libraries(dcmtkpp
    ${Boost_LIBRARIES} ${DCMTK_LIBRARIES} ${ICU_LIBRARIES} ${JsonCpp_LIBRARIES}
    uuid)
set_target_properties(dcmtkpp PROPERTIES
    VERSION ${dcmtkpp_VERSION}
    SOVERSION ${dcmtkpp_MAJOR_VERSION})

install(FILES ${headers} ${templates} DESTINATION include/dcmtkpp)
install(
    TARGETS dcmtkpp
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)


