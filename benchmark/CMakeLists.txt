
find_package(benchmark CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)

add_executable(zip_bench zip.cpp)

target_link_libraries(zip_bench
    benchmark::benchmark
    range-v3
    irate)
