set(ssqlsxlat_src
  genv2.cpp
  parsev2.cpp
  main.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_BINARY_DIR}/lib)

set(DOXYGEN_SSX_INPUT ${CMAKE_SOURCE_DIR}/ssx)
configure_file(Doxyfile.in Doxyfile @ONLY)

add_executable(ssqlsxlat ${ssqlsxlat_src})
target_link_libraries(ssqlsxlat mysqlpp_shared)
