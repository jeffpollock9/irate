add_library(catch catch/catch.cpp)

set(IRATE_TESTS enumerate zip range)

foreach(test ${IRATE_TESTS})
    add_executable(${test} ${test}.cpp)
    target_link_libraries(${test} irate catch)
    add_test(${test} ${test})
endforeach()
