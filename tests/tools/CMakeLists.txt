find_package(DCMTK REQUIRED)
find_package(ZLIB REQUIRED)

file(GLOB headers *.h)
file(GLOB files "*.cc")

if(USE_BUILTIN_DCMTK_GETSCU)
    add_executable(dcmtk_getscu ${files} ${headers})
    target_link_libraries(dcmtk_getscu DCMTK::DCMTK ZLIB::ZLIB)
    set_target_properties(dcmtk_getscu PROPERTIES OUTPUT_NAME getscu)
endif()
