find_package(Boost REQUIRED COMPONENTS python)
find_package(JsonCpp REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../src ${Boost_INCLUDE_DIRS}
    ${JsonCpp_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB_RECURSE files "*.cpp")
python_add_module(pyodil SHARED ${files})
set_target_properties(
    pyodil PROPERTIES OUTPUT_NAME odil)
if(APPLE)
    set_target_properties(pyodil PROPERTIES SUFFIX ".so")
endif()

target_link_libraries(
    pyodil ${Boost_LIBRARIES} ${JsonCpp_LIBRARIES} libodil ${PYTHON_LIBRARIES})
