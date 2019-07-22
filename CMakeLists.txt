cmake_minimum_required(VERSION 3.12)
project(mysqlpp)

set(MYSQLPP_VERSION_MAJOR 3)
set(MYSQLPP_VERSION_MINOR 2)
set(MYSQLPP_VERSION_BUGFIX 1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

option(MYSQLPP_OLD_CLASS_NAMES "Enables MySQL old class names")

set(FIELD_LIMIT 25 CACHE STRING "set max template query and SSQLS field count")

find_package(MySQL REQUIRED)
find_package (Threads)

include_directories(${MySQL_INCLUDE_DIR})
enable_testing()

include(CheckFunctionExists)
include(CheckIncludeFileCXX)
include(CheckLibraryExists)

check_function_exists(localtime_r HAVE_LOCALTIME_R)
check_function_exists(getopt HAVE_POSIX_GETOPT)

check_include_file(unistd.h HAVE_UNISTD_H)
check_include_file(synch.h HAVE_SYNCH_H)
check_include_file(libiberty.h HAVE_LIBIBERTY_GETOPT)

check_include_file_cxx(ext/slist HAVE_EXT_SLIST)
check_include_file_cxx(slist HAVE_GLOBAL_SLIST)

check_library_exists(${MySQL_LIBRARIES} mysql_ssl_set "" HAVE_MYSQL_SSL_SET)

if(CMAKE_THREAD_LIBS_INIT)
  set(HAVE_THREADS TRUE)
endif()

if(CMAKE_USE_PTHREADS_INIT)
  set(HAVE_PTHREAD TRUE)
endif()

configure_file(config.h.in config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(lib)
add_subdirectory(test)
