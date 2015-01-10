cmake_minimum_required(VERSION 2.8.4)

set(APPNAME simplegame)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/${APPNAME}")

# sources
include_directories("${PROJECT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB SOURCE_FILES *.cpp ../app.cpp)

# build examples
add_executable(${APPNAME} ${SOURCE_FILES})

# link
target_link_libraries(${APPNAME} ${GLSG_LIBRARY_NAME})

# copy resources
add_custom_command(TARGET ${APPNAME}
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:${APPNAME}>/data)
