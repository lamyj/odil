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

if(COMPILER_SUPPORTS_CXX11)
    set(EMCC_FLAGS "${EMCC_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(EMCC_FLAGS "${EMCC_FLAGS} -std=c++0x")
endif()

if(BUILD_EMSCRIPTEN_WRAPPERS)
    file(
        DOWNLOAD http://download.icu-project.org/files/icu4c/58.2/icu4c-58_2-src.zip
        ${CMAKE_CURRENT_BINARY_DIR}/icu4c-58_2-src.zip
    )
    file(
        DOWNLOAD https://github.com/open-source-parsers/jsoncpp/archive/1.8.0.zip 
        ${CMAKE_CURRENT_BINARY_DIR}/jsoncpp-1.8.0.zip)
    # TODO: unzip both, amalgamate jsoncpp
    
    set(icu_files
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/bytestream.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/charstr.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/cmemory.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/putil.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/stringpiece.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucln_cmn.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucmndata.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv2022.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnvbocu.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnvhz.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnvisci.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnvlat1.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnvmbcs.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnvscsu.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv_bld.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv_cb.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv_ct.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv_cnv.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv_err.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv_ext.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv_io.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv_lmb.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv_u7.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv_u8.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv_u16.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv_u32.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/udata.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/udatamem.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/uhash.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/uinvchar.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/umapfile.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/umath.c"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/umutex.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/unistr.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/unistr_cnv.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/uobject.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ustr_cnv.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ustring.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ustrtrns.cpp")
    
    set(json_cpp_files 
        "${CMAKE_CURRENT_BINARY_DIR}/jsoncpp-1.8.0/dist/jsoncpp.cpp")
    
    set(odil_files 
        "../src/odil/base64.cpp" "../src/odil/DataSet.cpp"
        "../src/odil/Element.cpp" "../src/odil/ElementsDictionary.cpp" 
        "../src/odil/Exception.cpp" "../src/odil/json_converter.cpp" 
        "../src/odil/Reader.cpp" "../src/odil/registry.cpp" "../src/odil/Tag.cpp" 
        "../src/odil/uid.cpp" "../src/odil/UIDsDictionary.cpp" 
        "../src/odil/unicode.cpp" "../src/odil/Value.cpp" "../src/odil/VR.cpp" 
        "../src/odil/VRFinder.cpp")
    
    file(GLOB files "js/*cpp") 
    
    set(CMAKE_C_COMPILER emcc)
    set(CMAKE_CXX_COMPILER em++)
    set(CMAKE_AR emar)
    set(CMAKE_RANLIB emranlib)
    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind")
    
    set(CMAKE_C_CREATE_STATIC_LIBRARY "<CMAKE_AR> rc <TARGET> <LINK_FLAGS> <OBJECTS>")
    set(CMAKE_CXX_CREATE_STATIC_LIBRARY "<CMAKE_AR> rc <TARGET> <LINK_FLAGS> <OBJECTS>")

    add_definitions(
        -D ODIL_MAJOR_VERSION=${odil_MAJOR_VERSION}
        -D U_COMMON_IMPLEMENTATION -D U_DISABLE_RENAMING=1
    )
    
    include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}/icu/source/common
        ${CMAKE_CURRENT_BINARY_DIR}/jsoncpp-1.8.0/dist/
        ${CMAKE_SOURCE_DIR}/src)

    add_executable(odil_js ${icu_files} ${json_cpp_files} ${odil_files} ${files})
    
    message("--------- ${icu_files} ${json_cpp_files} ${odil_files} ${files}")
    
    set_target_properties(odil_js PROPERTIES OUTPUT_NAME odil)
    set_target_properties(odil_js PROPERTIES SUFFIX ".js")
    
    # add_custom_command(
    #     OUTPUT odil.js
    #     COMMAND 
    #         unzip -n icu4c-58_2-src.zip &&
    #         unzip -n jsoncpp-1.8.0.zip && 
    #         cd jsoncpp-1.8.0 && python amalgamate.py && cd .. && 
    #         em++ 
    #             ${EMCC_FLAGS}
    #             --bind -o odil.js -O0
    #             -s ALLOW_MEMORY_GROWTH=1
    #             -s DISABLE_EXCEPTION_CATCHING=0
    #             -I ../../src/ -I icu/source/common -I jsoncpp-1.8.0/dist/ -I /usr/local/include/ 
    #             -D ODIL_MAJOR_VERSION=0
    #             ${files}
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/bytestream.cpp"
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/charstr.cpp"
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/cmemory.c"
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv.c"
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv_bld.cpp"
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ucnv_io.cpp"
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/udata.cpp"
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/udatamem.c"
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/uhash.c"
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/umutex.cpp"
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/unistr.cpp"
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/unistr_cnv.cpp"
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/uobject.cpp"
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ustr_cnv.cpp"
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ustring.cpp"
    #             # "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common/ustrtrns.cpp"
    #             "${CMAKE_CURRENT_BINARY_DIR}/jsoncpp-1.8.0/dist/jsoncpp.cpp"
    #     MAIN_DEPENDENCY js/odil.cpp
    #     DEPENDS ${files}
    # )
    # add_custom_target(OdilJS ALL echo DEPENDS odil.js)
endif()
