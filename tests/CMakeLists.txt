cmake_minimum_required(VERSION 2.8.4)

set(APPNAME tests)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/${APPNAME}")
SET(CXXTESTGEN /usr/local/bin/cxxtestgen)

# sources
include_directories("${PROJECT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(${CXXTEST_INCLUDE_DIR})

enable_testing()

CXXTEST_ADD_TEST(test1 test1.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test1.h)
CXXTEST_ADD_TEST(test2 test2.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test2.h)

target_link_libraries(test1 ${GLSG_LIBRARY_NAME})
target_link_libraries(test2 ${GLSG_LIBRARY_NAME})
