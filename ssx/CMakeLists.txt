set(ssqlsxlat_src
  genv2.cpp
  parsev2.cpp
  main.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(ssqlsxlat ${ssqlsxlat_src})
target_link_libraries(ssqlsxlat mysqlpp_shared)
