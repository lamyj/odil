find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(ICU REQUIRED)

set(DCMTK_LIBRARIES dcmnet dcmdata oflog ofstd pthread z)
find_library(USE_WRAP wrap)
if(USE_WRAP)
    set(DCMTK_LIBRARIES ${DCMTK_LIBRARIES} wrap)
endif()

file(GLOB_RECURSE headers "*.h")
file(GLOB_RECURSE templates "*.txx")
file(GLOB_RECURSE files "*.cpp")
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS} ${ICU_INCLUDE_DIR})
add_definitions("-D HAVE_CONFIG_H")
add_definitions("-D DCMTKPP_MAJOR_VERSION=${dcmtkpp_MAJOR_VERSION}")

link_directories(${Boost_LIBRARY_DIRS})
add_library(dcmtkpp SHARED ${files})
install(TARGETS dcmtkpp LIBRARY DESTINATION lib)
install(FILES ${headers} ${templates} DESTINATION include/dcmtkpp)

target_link_libraries(dcmtkpp
    ${Boost_LIBRARIES} ${DCMTK_LIBRARIES} jsoncpp ${ICU_LIBRARIES} uuid)
set_target_properties(dcmtkpp PROPERTIES 
    VERSION ${dcmtkpp_VERSION}
    SOVERSION ${dcmtkpp_MAJOR_VERSION})

