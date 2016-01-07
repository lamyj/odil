find_package(DCMTK REQUIRED)

add_definitions(${DCMTK_DEFINITIONS})
include_directories(${DCMTK_INCLUDE_DIRS})
link_directories(${DCMTK_LIBRARY_DIRS})

file(GLOB headers *.h)
file(GLOB files "*.cc")

add_executable(getscu ${files} ${headers})
target_link_libraries(getscu ${DCMTK_LIBRARIES})
