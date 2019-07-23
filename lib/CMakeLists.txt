set(mysqlpp_src
    connection.cpp
    cmdline.cpp
    beemutex.cpp
    manip.cpp
    field_types.cpp
    field_names.cpp
    dbdriver.cpp
    datetime.cpp
    cpool.cpp
    sqlstream.cpp
    sql_buffer.cpp
    scopedconnection.cpp
    row.cpp
    result.cpp
    query.cpp
    qparms.cpp
    options.cpp
    null.cpp
    mystring.cpp
    mysql++.cpp
    myset.cpp
    utility.cpp
    uds_connection.cpp
    type_info.cpp
    transaction.cpp
    tcp_connection.cpp
    stadapter.cpp
    ssqls2.cpp
    wnp_connection.cpp
    vallist.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/querydef.h
    ${CMAKE_CURRENT_BINARY_DIR}/ssqls.h
)

add_custom_command(
    OUTPUT querydef.h
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/querydef.pl -f ${FIELD_LIMIT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(
    OUTPUT ssqls.h
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/ssqls.pl -f ${FIELD_LIMIT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

configure_file(mysql++.h.in mysql++.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(mysqlpp_shared SHARED ${mysqlpp_src})
add_library(mysqlpp_static STATIC ${mysqlpp_src})

set_target_properties(mysqlpp_shared PROPERTIES VERSION ${MYSQLPP_VERSION_MAJOR}.${MYSQLPP_VERSION_MINOR}.${MYSQLPP_VERSION_BUGFIX} SOVERSION ${MYSQLPP_VERSION_MAJOR})
set_target_properties(mysqlpp_shared PROPERTIES OUTPUT_NAME mysqlpp)
set_target_properties(mysqlpp_static PROPERTIES OUTPUT_NAME mysqlpp)

target_link_libraries(mysqlpp_shared
    ${CMAKE_THREAD_LIBS_INIT}
    ${MySQL_LIBRARIES}
)
