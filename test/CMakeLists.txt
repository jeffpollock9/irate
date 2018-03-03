set(IRATE_TESTS enumerate zip)

foreach(test ${IRATE_TESTS})
    add_executable(${test} ${test}.cpp)
    target_link_libraries(${test} irate)
    add_test(${test} ${test})
endforeach()
