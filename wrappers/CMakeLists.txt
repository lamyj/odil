find_package(Boost REQUIRED COMPONENTS python)
find_package(JsonCpp REQUIRED)
find_package(PythonInterp 2.7 REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)

if(BUILD_PYTHON_WRAPPERS)
    if(NOT "${PYTHONLIBS_VERSION_STRING}" STREQUAL "${PYTHON_VERSION_STRING}")
        message(
            WARNING
            "Python version mismatch:  libraries are \"${PYTHONLIBS_VERSION_STRING}\", interpreter is \"${PYTHON_VERSION_STRING}\"")
    endif()

    if(BUILD_SHARED_LIBS)
        add_definitions(-D BOOST_ALL_DYN_LINK)
    endif()

    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../src ${Boost_INCLUDE_DIRS}
        ${JsonCpp_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})

    file(GLOB_RECURSE files "*.cpp")
    list(SORT files)
    python_add_module(pyodil SHARED ${files})
    set_target_properties(
        pyodil PROPERTIES OUTPUT_NAME odil FOLDER "Wrappers")
    if(APPLE)
        set_target_properties(pyodil PROPERTIES SUFFIX ".so")
    endif()

    target_link_libraries(
        pyodil ${Boost_LIBRARIES} ${JsonCpp_LIBRARIES} libodil ${PYTHON_LIBRARIES})

    execute_process(
        COMMAND ${PYTHON_EXECUTABLE}
          -c "from distutils import sysconfig; print( sysconfig.get_python_lib( plat_specific=True, prefix='${CMAKE_INSTALL_PREFIX}' ) )"
        OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
        OUTPUT_STRIP_TRAILING_WHITESPACE)

    install(TARGETS pyodil DESTINATION ${PYTHON_SITE_PACKAGES})
endif()

if(BUILD_EMSCRIPTEN_WRAPPERS)
    file(
        DOWNLOAD https://github.com/open-source-parsers/jsoncpp/archive/1.8.0.zip 
        ${CMAKE_CURRENT_BINARY_DIR}/jsoncpp-1.8.0.zip)
    file(
        GLOB files
        "js/*cpp" "../src/odil/base64.cpp" "../src/odil/DataSet.cpp"
        "../src/odil/Element.cpp" "../src/odil/ElementsDictionary.cpp" 
        "../src/odil/Exception.cpp" "../src/odil/json_converter.cpp" 
        "../src/odil/Reader.cpp" "../src/odil/registry.cpp" "../src/odil/Tag.cpp" 
        "../src/odil/uid.cpp" "../src/odil/UIDsDictionary.cpp" 
        "../src/odil/Value.cpp" "../src/odil/VR.cpp" "../src/odil/VRFinder.cpp")
    
    add_custom_command(
        OUTPUT odil.js
        COMMAND 
            unzip -n jsoncpp-1.8.0.zip && 
            cd jsoncpp-1.8.0 && python amalgamate.py && cd .. && 
            emcc 
                --bind -o odil.js -O2
                -s ALLOW_MEMORY_GROWTH=1
                -s DISABLE_EXCEPTION_CATCHING=0
                -I ../../src/ -I jsoncpp-1.8.0/dist/ -I /usr/local/include/ 
                -D ODIL_MAJOR_VERSION=0
                ${files}
                "${CMAKE_CURRENT_BINARY_DIR}/jsoncpp-1.7.2/dist/jsoncpp.cpp"
        MAIN_DEPENDENCY js/odil.cpp
        DEPENDS ${files}
    )
    add_custom_target(OdilJS ALL echo DEPENDS odil.js)
endif()
