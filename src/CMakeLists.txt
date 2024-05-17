# set(BINARY ${CMAKE_PROJECT_NAME})
set(BINARY_LIB ${CMAKE_PROJECT_NAME}_lib)
 
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES})

add_library(${BINARY_LIB} STATIC ${SOURCES})
target_include_directories(${BINARY_LIB} PUBLIC 
                            "./core/"
                            "./utils")
target_compile_options(${BINARY_LIB} PUBLIC -pthread -mpopcnt -O2 -Wall -march=native)

