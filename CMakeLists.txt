cmake_minimum_required(VERSION 3.1)

SET(PROJECT_NAME_STR LiturgicCalendar)
project(${PROJECT_NAME_STR} C CXX)

set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -pthread")

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

include_directories(${COMMON_INCLUDES})

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/include/sqlite/sqlite3.c)

add_executable(${PROJECT_NAME_STR} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME_STR} dl)