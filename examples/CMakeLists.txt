set(example_sources
    transaction.cpp
    tquery4.cpp
    tquery3.cpp
    tquery2.cpp
    tquery1.cpp
    store_if.cpp
    ssqls6.cpp
    ssqls5.cpp
    ssqls4.cpp
    ssqls3.cpp
    ssqls2.cpp
    ssqls1.cpp
    simple3.cpp
    simple2.cpp
    simple1.cpp
    resetdb.cpp
    multiquery.cpp
    load_jpeg.cpp
    for_each.cpp
    fieldinf.cpp
    deadlock.cpp
    dbinfo.cpp
    cpool.cpp
    cgi_jpeg.cpp
)

set(additional_source_files
  printdata.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_BINARY_DIR}/lib)

foreach(example_source_file IN ITEMS ${example_sources})
    string(REPLACE ".cpp" "" example_target ${example_source_file})
    add_executable(${example_target} ${example_source_file} ${additional_source_files})
    target_link_libraries(${example_target} mysqlpp_shared)
endforeach()
