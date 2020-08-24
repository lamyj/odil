find_package(Boost REQUIRED)
find_package(DCMTK REQUIRED)
find_package(JsonCpp REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/src ${Boost_INCLUDE_DIRS} ${DCMTK_INCLUDE_DIRS}
    ${JsonCpp_INCLUDE_DIRS})

add_definitions(
    ${DCMTK_DEFINITIONS}
    -D ODIL_MAJOR_VERSION=${Odil_VERSION_MAJOR}
)
if(BUILD_SHARED_LIBS)
    add_definitions(-D BOOST_ALL_DYN_LINK)
endif()

link_directories(${Boost_LIBRARY_DIRS} ${DCMTK_LIBRARY_DIRS})

file(GLOB_RECURSE examples *.cpp)

foreach(example_file ${examples})
    get_filename_component(example ${example_file} NAME_WE)
    add_executable(${example} ${example_file})
    target_link_libraries(${example} libodil)
    if(INSTALL_EXAMPLES)
        install(TARGETS ${example} RUNTIME DESTINATION bin)
    endif()
    set_target_properties(${example} PROPERTIES FOLDER "Examples")
endforeach()
