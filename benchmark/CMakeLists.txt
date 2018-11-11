include(add_basic_warnings)

find_package(benchmark CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)

set(IRATE_BENCHMARKS zip product)

foreach(benchmark ${IRATE_BENCHMARKS})
    set(name "${benchmark}_benchmark")
    add_executable(${name} ${benchmark}.cpp)
    target_link_libraries(${name} irate benchmark::benchmark range-v3)
    add_basic_warnings(${name})
endforeach()
