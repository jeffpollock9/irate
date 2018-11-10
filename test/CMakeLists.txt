include(add_basic_warnings)

add_library(catch catch/catch.cpp)

target_include_directories(catch PUBLIC ${PROJECT_SOURCE_DIR}/test)

set(IRATE_TESTS enumerate zip range product)

foreach(test ${IRATE_TESTS})
    set(name "${test}_test")
    add_executable(${name} ${test}.cpp)
    target_link_libraries(${name} irate catch)
    add_basic_warnings(${name})
    add_test(${test} ${name})
endforeach()
