cmake_minimum_required(VERSION 2.8.4)

set(APPNAME simplegame)

if (APPLE)
    set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/${APPNAME}.app/Contents/MacOS")
    execute_process(COMMAND "../bundle.sh" ${APPNAME} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
else (APPLE)
    set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/${APPNAME}")
endif(APPLE)

# sources
include_directories("${PROJECT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB SOURCE_FILES *.cpp ../app.cpp)

# build examples
add_executable(${APPNAME} ${SOURCE_FILES})

# link
target_link_libraries(${APPNAME} ${GLSG_LIBRARY_NAME})

# mac packaging needed?
if (APPLE)
    add_custom_command(TARGET ${APPNAME}
                       POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/data ${PROJECT_SOURCE_DIR}/build/${APPNAME}.app/Contents/Resources/data)
else (APPLE)
    add_custom_command(TARGET ${APPNAME}
                           POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:${APPNAME}>/data)
endif (APPLE)

