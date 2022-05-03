cmake_minimum_required(VERSION 3.5)
project(lib_lxb_wrapper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(
    src
)

add_library(lexbor_wrapper 
    src/document.cpp
    src/node.cpp
    src/base.cpp
    src/collection.cpp
    src/body_element.cpp
    src/element.cpp
    src/attribute.cpp
    src/utils.cpp
    src/hash.cpp
    src/tag.cpp
    src/exception.cpp
    src/encoding.cpp
)
target_link_libraries(lexbor_wrapper lexbor)


include(CTest)
enable_testing()
add_subdirectory(examples)
