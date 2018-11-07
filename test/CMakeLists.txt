add_library(catch catch/catch.cpp)

target_include_directories(catch PUBLIC ${PROJECT_SOURCE_DIR}/test)

set(IRATE_TESTS enumerate zip range)

foreach(test ${IRATE_TESTS})
    add_executable(${test} ${test}.cpp)
    target_link_libraries(${test} irate catch)
    target_compile_options(${test} PRIVATE -Wall -Wextra -Wpedantic -Wshadow)
    add_test(${test} ${test})
endforeach()
