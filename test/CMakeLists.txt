# 获取以 test 结尾的测试文件列表
file(GLOB TEST_SOURCES "*_test.cpp")

# 为每个测试文件生成可执行文件并添加测试用例
foreach(TEST_SOURCE ${TEST_SOURCES})
    # 提取文件名作为测试名称
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    # 生成可执行文件并链接 src 目录下的源文件
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_compile_options(${TEST_NAME} PUBLIC -pthread -mpopcnt -O2 -Wall -march=native -mavx512f -mavx2 -msse2 -fopenmp)
    target_link_libraries(${TEST_NAME} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gtest_main OpenMP::OpenMP_CXX)
    # 添加测试用例
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach(TEST_SOURCE)

# add_executable(MyTests ${TEST_SOURCES})
# target_compile_options(MyTests PUBLIC -pthread -mpopcnt -O2 -Wall -march=native)
# target_link_libraries(MyTests PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gtest_main)
# # 添加测试用例
# add_test(NAME $MyTests COMMAND MyTests)

