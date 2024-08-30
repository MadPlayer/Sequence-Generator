cmake_minimum_required(VERSION 3.20 FATAL_ERROR)


project(clang-tidy-plugins LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

option(BUILD_WARNINGS "Build with project's warnings setting" ON)
option(BUILD_WARNING_AS_ERROR "Build with warning as error" ON)
if(BUILD_WARNINGS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        add_compile_options(-Wall)
    endif()
endif()
if(BUILD_WARNING_AS_ERROR)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        add_compile_options(-Werror)
    endif()
endif()


enable_testing()
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)


add_subdirectory(src)
