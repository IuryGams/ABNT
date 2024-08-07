cmake_minimum_required(VERSION 3.21)

PROJECT(
    ABNT_PROJECT
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB FILES_CPP source/*.cpp)

add_library(
    ${PROJECT_NAME}lib

    ${FILES_CPP}
)

add_executable(
    ${PROJECT_NAME}

    ./main.cpp
)

target_include_directories(
    ${PROJECT_NAME}lib

    PUBLIC
        ./include
)

target_compile_features(
    ${PROJECT_NAME}lib

    PUBLIC
        cxx_std_20
)

target_link_libraries(
    ${PROJECT_NAME}

    PRIVATE
        ${PROJECT_NAME}lib
)
