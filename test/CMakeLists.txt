set(test_sources
    tcp.cpp
    string.cpp
    sqlstream.cpp
    query_copy.cpp
    qstream.cpp
    qssqls.cpp
    null_comparison.cpp
    manip.cpp
    inttypes.cpp
    insertpolicy.cpp
    datetime.cpp
    cpool.cpp
    array_index.cpp
    wnp.cpp
    uds.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_BINARY_DIR}/lib)

foreach(test_source_file IN ITEMS ${test_sources})
    string(REPLACE ".cpp" "" test_target ${test_source_file})
    string(PREPEND test_target "test_")
    add_executable(${test_target} ${test_source_file})
    target_link_libraries(${test_target} mysqlpp_shared)
    add_test(NAME ${test_target} COMMAND ${test_target})
endforeach()

# Special handling for the ssqls2 test which requires and additional file from ssx directory
add_executable(test_ssqls2 ssqls2.cpp ../ssx/parsev2.cpp)
target_link_libraries(test_ssqls2 mysqlpp_shared)
add_test(NAME test_ssqls2 COMMAND test_ssqls2)
