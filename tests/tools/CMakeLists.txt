find_package(DCMTK REQUIRED)

add_definitions(${DCMTK_DEFINITIONS})
include_directories(${DCMTK_INCLUDE_DIRS})
link_directories(${DCMTK_LIBRARY_DIRS})

file(GLOB headers *.h)
file(GLOB files "*.cc")

add_executable(dcmtk_getscu ${files} ${headers})
target_link_libraries(dcmtk_getscu ${DCMTK_LIBRARIES})
set_target_properties(dcmtk_getscu PROPERTIES OUTPUT_NAME getscu)
