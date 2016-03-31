find_package(Boost REQUIRED COMPONENTS python)
find_package(PythonLibs 2.7 REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../src ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB_RECURSE files "*.cpp")
python_add_module(_odil SHARED ${files})
if(APPLE)
    set_target_properties(_odil PROPERTIES SUFFIX ".so")
endif()

target_link_libraries(_odil ${Boost_LIBRARIES} odil ${PYTHON_LIBRARIES})
