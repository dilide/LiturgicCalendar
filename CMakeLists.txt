cmake_minimum_required(VERSION 3.14)
project(LiturgicCalendar LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread")

add_library(calendar_core STATIC
    src/Calendar.cpp
    src/Date.cpp
    src/LiturgicDay.cpp
    src/LiturgicYear.cpp
    src/MultiLang.cpp
    include/sqlite/sqlite3.c
)
target_include_directories(calendar_core PUBLIC include)
target_link_libraries(calendar_core PUBLIC ${CMAKE_DL_LIBS})

add_executable(LiturgicCalendar src/main.cpp)
target_link_libraries(LiturgicCalendar PRIVATE calendar_core)

find_package(GTest 1.14 CONFIG QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    set(BUILD_GMOCK OFF CACHE BOOL "Build Google Mock")
    set(INSTALL_GTEST OFF CACHE BOOL "Install Google Test")
    FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571 # v1.14.0
    )
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(liturgy_calendar_test test/liturgy_calendar_test.cpp)
target_link_libraries(liturgy_calendar_test PRIVATE calendar_core GTest::gtest_main)

# Export tests replace files in their working directory.
set(test_work_dir "${CMAKE_CURRENT_BINARY_DIR}/test-output")
configure_file(lang.ini "${test_work_dir}/lang.ini" COPYONLY)
enable_testing()
add_test(NAME liturgy_calendar_test COMMAND liturgy_calendar_test)
set_tests_properties(liturgy_calendar_test PROPERTIES WORKING_DIRECTORY "${test_work_dir}")

add_custom_target(check ALL
    COMMAND "${CMAKE_CTEST_COMMAND}" --output-on-failure -C "$<CONFIG>"
    DEPENDS liturgy_calendar_test
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    VERBATIM
)
