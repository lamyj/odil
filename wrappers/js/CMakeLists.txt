find_package(Boost REQUIRED COMPONENTS system)

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/icu/source/common")
    file(
        DOWNLOAD http://download.icu-project.org/files/icu4c/58.2/icu4c-58_2-src.zip
        ${CMAKE_CURRENT_BINARY_DIR}/icu4c-58_2-src.zip SHOW_PROGRESS)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar x icu4c-58_2-src.zip
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/jsoncpp-1.8.0/dist/jsoncpp.cpp")
    file(
        DOWNLOAD https://github.com/open-source-parsers/jsoncpp/archive/1.8.0.zip 
        ${CMAKE_CURRENT_BINARY_DIR}/jsoncpp-1.8.0.zip SHOW_PROGRESS)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar x jsoncpp-1.8.0.zip
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    execute_process(
        COMMAND python amalgamate.py 
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/jsoncpp-1.8.0)
endif()

if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/boost")
    execute_process( COMMAND ln -s ${Boost_INCLUDE_DIRS}/boost ${CMAKE_CURRENT_BINARY_DIR})
endif()

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
    "${CMAKE_SOURCE_DIR}/src/odil/base64.cpp" 
    "${CMAKE_SOURCE_DIR}/src/odil/DataSet.cpp"
    "${CMAKE_SOURCE_DIR}/src/odil/Element.cpp" 
    "${CMAKE_SOURCE_DIR}/src/odil/ElementsDictionary.cpp" 
    "${CMAKE_SOURCE_DIR}/src/odil/Exception.cpp" 
    "${CMAKE_SOURCE_DIR}/src/odil/json_converter.cpp" 
    "${CMAKE_SOURCE_DIR}/src/odil/Reader.cpp" 
    "${CMAKE_SOURCE_DIR}/src/odil/registry.cpp" 
    "${CMAKE_SOURCE_DIR}/src/odil/Tag.cpp" 
    "${CMAKE_SOURCE_DIR}/src/odil/uid.cpp" 
    "${CMAKE_SOURCE_DIR}/src/odil/UIDsDictionary.cpp" 
    "${CMAKE_SOURCE_DIR}/src/odil/unicode.cpp" 
    "${CMAKE_SOURCE_DIR}/src/odil/Value.cpp" 
    "${CMAKE_SOURCE_DIR}/src/odil/VR.cpp" 
    "${CMAKE_SOURCE_DIR}/src/odil/VRFinder.cpp"
    "${CMAKE_SOURCE_DIR}/src/odil/webservices/HTTPRequest.cpp"
    "${CMAKE_SOURCE_DIR}/src/odil/webservices/HTTPResponse.cpp"
    "${CMAKE_SOURCE_DIR}/src/odil/webservices/ItemWithParameters.cpp"
    "${CMAKE_SOURCE_DIR}/src/odil/webservices/Message.cpp"
    "${CMAKE_SOURCE_DIR}/src/odil/webservices/multipart_related.cpp"
    "${CMAKE_SOURCE_DIR}/src/odil/webservices/Selector.cpp"
    "${CMAKE_SOURCE_DIR}/src/odil/webservices/URL.cpp"
    "${CMAKE_SOURCE_DIR}/src/odil/webservices/WADORSRequest.cpp"
    "${CMAKE_SOURCE_DIR}/src/odil/webservices/WADORSResponse.cpp")

file(GLOB_RECURSE files "*cpp") 

set(CMAKE_C_COMPILER emcc)
set(CMAKE_CXX_COMPILER em++)
set(CMAKE_AR emar)
set(CMAKE_RANLIB emranlib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind -s ALLOW_MEMORY_GROWTH=1")

set(CMAKE_C_CREATE_STATIC_LIBRARY "<CMAKE_AR> rc <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_CREATE_STATIC_LIBRARY "<CMAKE_AR> rc <TARGET> <LINK_FLAGS> <OBJECTS>")

add_definitions(
    -D ODIL_MAJOR_VERSION=${odil_MAJOR_VERSION}
    -D U_COMMON_IMPLEMENTATION -D U_DISABLE_RENAMING=1
)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/icu/source/common
    ${CMAKE_CURRENT_BINARY_DIR}/jsoncpp-1.8.0/dist/
    ${CMAKE_SOURCE_DIR}/src)

add_executable(odil_js ${icu_files} ${json_cpp_files} ${odil_files} ${files})

set_target_properties(odil_js PROPERTIES OUTPUT_NAME odil)
set_target_properties(odil_js PROPERTIES SUFFIX ".js")
