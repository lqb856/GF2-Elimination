set(BINARY ${CMAKE_PROJECT_NAME}_test)
 
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *_test.h *_test.cpp)
set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gtest_main)

add_test(NAME ${BINARY} COMMAND ${BINARY})

