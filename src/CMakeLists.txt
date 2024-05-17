set(BINARY ${CMAKE_PROJECT_NAME})
set(BINARY_LIB ${CMAKE_PROJECT_NAME}_lib)
 
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES})
# add_executable(${BINARY}_run ${SOURCES})
# 为了让单元测试的时候src下的代码能被作为静态链接库使用

add_library(${BINARY_LIB} STATIC ${SOURCES})
target_include_directories(${BINARY_LIB} PUBLIC 
                            "./core/"
                            "./utils")
target_compile_options(${BINARY_LIB} PUBLIC -pthread -mpopcnt -O2 -Wall -march=native)

