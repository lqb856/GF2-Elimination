cmake_minimum_required(VERSION 3.10)
project(GF2_Elim)

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

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(third_party/googletest)

# # 添加項目的執行文件
# add_executable(first_bit_test "src/core/context.h" "test/context_test.cpp")

# # 添加 Google Test 相關庫文件到你的執行文件
# target_link_libraries(first_bit_test gtest gtest_main)

# # 添加測試目標
enable_testing()
# add_test(NAME first_bit COMMAND first_bit_test)
