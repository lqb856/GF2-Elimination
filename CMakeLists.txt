cmake_minimum_required(VERSION 3.10)
project(GF2_Elim)

find_package(OpenMP)
# set compiler flags, see http://stackoverflow.com/questions/7724569/debug-vs-release-in-cmake
if(OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS            "-fopenmp -Ofast -fno-signed-zeros -fno-trapping-math -Wall -Wno-format-extra-args -Wextra -Wformat-nonliteral -Wformat-security -Wformat=2 -Wextra -Wno-implicit-fallthrough -pedantic")
else()
    message(WARNING "Configuring without OpenMP!")
    set(CMAKE_CXX_FLAGS            "-Ofast -fno-signed-zeros -fno-trapping-math -Wall -Wno-format-extra-args -Wextra -Wformat-nonliteral -Wformat-security -Wformat=2 -Wextra -Wno-implicit-fallthrough -pedantic")
endif()

# enable c++ 11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# take respectives flags for debug & release process 
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-std=c++17 -g -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-std=c++17 -g -O2")

# default build type : Debug
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# # 添加 src 目录
# file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true 
#     src/core/*.h 
#     src/core/*.cpp
#     src/utils/*.h 
#     src/utils/*.cpp
# )
# # 打印 SRC_FILES 变量内容
# message(STATUS "Source files: ${SOURCES}")


add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(third_party/googletest)

# turn on gtest
enable_testing()
